/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkFEMLoadElementBase.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/

/** disable debug warnings in MS compiler */
#ifdef _MSC_VER
#pragma warning(disable: 4786)
#endif

#include "itkFEMLoadElementBase.h"
#include "itkFEMUtility.h"

namespace itk {
namespace fem {




/**
 * Read the LoadElement object from input stream
 */
void LoadElement::Read( std::istream& f, void* info )
{

  int n;
  /**
   * Convert the info pointer to a usable objects
   */
  Element::ArrayType::ConstPointer elements=static_cast<ReadInfoType*>(info)->m_el;


  /** first call the parent's read function */
  Superclass::Read(f,info);

  /**
   * read and set pointers to element that we're applying the load to
   */

  /** first we read number of pointers in a list */
  SkipWhiteSpace(f); f>>n; if(!f) goto out;
  if (n<=0)
  {
    /** if this is <= 0, the load applies on all elements in a system */
    el.clear();
  }
  else 
  {
    /**
     * otherwise we read all the element numbers.
     * there should be n of them
     */
    for(int i=0;i<n;i++) {
      int m;
      SkipWhiteSpace(f); f>>m; if(!f) goto out;
      Element::ConstPointer e;
      if ( !(e=elements->Find(m)) )
        throw std::runtime_error("Global element number not found!");
      el.push_back(e);
    }

  }
  
  
out:

  if( !f ) throw std::runtime_error("Error reading load!");

}




/**
 * Write the LoadElement to the output stream
 */
void LoadElement::Write( std::ostream& f, int ofid ) const {

  /**
   * first call the parent's write function
   * this is an abstract class, so the ofid should already be set
   */
  Superclass::Write(f,ofid);

  /** Write the list of element global numbers */
  if (!el.empty()) {
    f<<"\t"<<(el.size()); f<<"\t% # of elements on which the load acts"<<"\n";
    f<<"\t";
    for(ElementPointersVectorType::const_iterator i=el.begin(); i!=el.end(); i++) {
      f<<((*i)->GN)<<" ";
    }
    f<<"\t% GNs of elements"<<"\n";
  }
  else {
    f<<"\t-1\t% Load acts on all elements"<<"\n";
  }

  /** check for errors */
  if (!f) { throw std::runtime_error("Error writing load!"); }
}

FEM_CLASS_REGISTER(LoadElement)




}} // end namespace itk::fem
