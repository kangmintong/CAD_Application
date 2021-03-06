/*=============================================================================
        File: vector.cpp
     Purpose:
    Revision: $Id: vector_hpoint.cpp,v 1.2 2002/05/13 21:07:45 philosophil Exp $
  Created by:    Philippe Lavoie          (3 Oct, 1996)
 Modified by: 

 Copyright notice:
          Copyright (C) 1996-1998 Philippe Lavoie
 
	  This library is free software; you can redistribute it and/or
	  modify it under the terms of the GNU Library General Public
	  License as published by the Free Software Foundation; either
	  version 2 of the License, or (at your option) any later version.
 
	  This library is distributed in the hope that it will be useful,
	  but WITHOUT ANY WARRANTY; without even the implied warranty of
	  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	  Library General Public License for more details.
 
	  You should have received a copy of the GNU Library General Public
	  License along with this library; if not, write to the Free
	  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
=============================================================================*/
#ifndef vector_hpoint_h__
#define vector_hpoint_h__



#include "vector.h"

namespace PLib {

#ifdef NO_IMPLICIT_TEMPLATES

  // HPoint3D instantation
  
  template class Vector<HPoint3Df> ;
  
  template Vector<HPoint3Df> operator+(const Vector<HPoint3Df>&, const Vector<HPoint3Df>&);
  template Vector<HPoint3Df> operator-(const Vector<HPoint3Df>&, const Vector<HPoint3Df>&);
  template HPoint3Df operator*(const Vector<HPoint3Df>&,const Vector<HPoint3Df>&);
  template Vector<HPoint3Df> operator*(const Vector<HPoint3Df>& v, const double d);
  template Vector<HPoint3Df> operator*(const Vector<HPoint3Df>& v, const Complex d);
  template int operator==(const Vector<HPoint3Df>&,const Vector<HPoint3Df>&);
  template int operator!=(const Vector<HPoint3Df>&,const Vector<HPoint3Df>&);
  
  
  template class Vector<HPoint3Dd> ;
  
  template Vector<HPoint3Dd> operator+(const Vector<HPoint3Dd>&, const Vector<HPoint3Dd>&);
  template Vector<HPoint3Dd> operator-(const Vector<HPoint3Dd>&, const Vector<HPoint3Dd>&);
  template HPoint3Dd operator*(const Vector<HPoint3Dd>&,const Vector<HPoint3Dd>&);
  template Vector<HPoint3Dd> operator*(const Vector<HPoint3Dd>& v, const double d);
  template Vector<HPoint3Dd> operator*(const Vector<HPoint3Dd>& v, const Complex d);
  template int operator==(const Vector<HPoint3Dd>&,const Vector<HPoint3Dd>&);
  template int operator!=(const Vector<HPoint3Dd>&,const Vector<HPoint3Dd>&);
 
  // HPoint2D instantation
  
  template class Vector<HPoint2Df> ;
  
  template Vector<HPoint2Df> operator+(const Vector<HPoint2Df>&, const Vector<HPoint2Df>&);
  template Vector<HPoint2Df> operator-(const Vector<HPoint2Df>&, const Vector<HPoint2Df>&);
  template HPoint2Df operator*(const Vector<HPoint2Df>&,const Vector<HPoint2Df>&);
  template Vector<HPoint2Df> operator*(const Vector<HPoint2Df>& v, const double d);
  template Vector<HPoint2Df> operator*(const Vector<HPoint2Df>& v, const Complex d);
  template int operator==(const Vector<HPoint2Df>&,const Vector<HPoint2Df>&);
  template int operator!=(const Vector<HPoint2Df>&,const Vector<HPoint2Df>&);
  
  
  template class Vector<HPoint2Dd> ;
  
  template Vector<HPoint2Dd> operator+(const Vector<HPoint2Dd>&, const Vector<HPoint2Dd>&);
  template Vector<HPoint2Dd> operator-(const Vector<HPoint2Dd>&, const Vector<HPoint2Dd>&);
  template HPoint2Dd operator*(const Vector<HPoint2Dd>&,const Vector<HPoint2Dd>&);
  template Vector<HPoint2Dd> operator*(const Vector<HPoint2Dd>& v, const double d);
  template Vector<HPoint2Dd> operator*(const Vector<HPoint2Dd>& v, const Complex d);
  template int operator==(const Vector<HPoint2Dd>&,const Vector<HPoint2Dd>&);
  template int operator!=(const Vector<HPoint2Dd>&,const Vector<HPoint2Dd>&);
  
  
#endif

}

#endif // vector_hpoint_h__