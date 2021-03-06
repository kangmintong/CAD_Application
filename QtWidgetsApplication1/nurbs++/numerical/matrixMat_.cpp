/*=============================================================================
        File: matrixMat.cpp
     Purpose:
    Revision: $Id: matrixMat_.cpp,v 1.2 2002/05/13 21:07:45 philosophil Exp $
  Created by: Philippe Lavoie          (22 Oct, 1997)
 Modified by: 

 Copyright notice:
          Copyright (C) 1996-1997 Philippe Lavoie
 
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
#ifndef matrixMat__h__
#define matrixMat__h__



#include "matrixMat.cpp"

namespace PLib {


#ifdef NO_IMPLICIT_TEMPLATES
  template class LUMatrix<double> ;
  template class LUMatrix<float> ;

  template class SVDMatrix<double> ;
  template class SVDMatrix<float> ;

  template int solve(const Matrix<float>&A, const Matrix<float>&B, Matrix<float>&X);
  template int solve(const Matrix<double>&A, const Matrix<double>&B, Matrix<double>&X);

  template Matrix<float> inverse(const Matrix<float>&) ;
  template Matrix<double> inverse(const Matrix<double>&) ;
  
#endif  

}

#endif // matrixMat__h__