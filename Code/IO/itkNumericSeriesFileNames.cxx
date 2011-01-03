/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef _itkNumericSeriesFileNames_h
#define _itkNumericSeriesFileNames_h

#ifdef _MSC_VER
#pragma warning ( disable : 4786 )
#endif

#include <vector>
#include <string>

#include "itkNumericSeriesFileNames.h"
#include <stdio.h>

namespace itk
{
NumericSeriesFileNames
::NumericSeriesFileNames():
  m_StartIndex(1), m_EndIndex(1), m_IncrementIndex(1), m_SeriesFormat("%d")
{}

const std::vector< std::string > &
NumericSeriesFileNames
::GetFileNames()
{
  // validate the indices
  if ( m_StartIndex > m_EndIndex )
    {
    itkExceptionMacro (<< "StartIndex " << m_StartIndex << " is greater than EndIndex " << m_EndIndex);
    }
  if ( m_IncrementIndex == 0 )
    {
    itkExceptionMacro (<< "IncrementIndex is zero.");
    }

  // clear the file names vector
  m_FileNames.clear();

  char temp[4096];
  for ( SizeValueType i = m_StartIndex; i <= m_EndIndex; i += m_IncrementIndex )
    {
    sprintf (temp, m_SeriesFormat.c_str(), i);
    std::string fileName(temp);
    m_FileNames.push_back(fileName);
    }
  return m_FileNames;
}

void
NumericSeriesFileNames
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "StartIndex: " << m_StartIndex << std::endl;
  os << indent << "EndIndex: " << m_EndIndex << std::endl;
  os << indent << "IncrementIndex: " << m_IncrementIndex << std::endl;
  os << indent << "SeriesFormat: " << m_SeriesFormat << std::endl;

  for ( unsigned int i = 0; i < m_FileNames.size(); i++ )
    {
    os << indent << "Filenames[" << i << "]: " << m_FileNames[i] << std::endl;
    }
}
} //namespace ITK

#endif
