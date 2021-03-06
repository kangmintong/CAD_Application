/*=============================================================================
        File: cvector.cpp
     Purpose:
    Revision: $Id: cvector.cpp,v 1.2 2002/05/13 21:07:45 philosophil Exp $
  Created by: Philippe Lavoie          (3 Oct, 1996)
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
#ifndef cvector_h__
#define cvector_h__



#include "matrix_global.h"
#include "cvector.h"

namespace PLib {

#ifdef NO_IMPLICIT_TEMPLATES

// Template instantation for g++


// Integer instantation

template class CVector<int> ;

// Byte instantation

template class CVector<char> ;

// Double instantation

template class CVector<double> ;

// Complex instantation

template class CVector<Complex_hjy> ;


// Ubyte instantation

template class CVector<unsigned char> ;


#endif

}

#endif // cvector_h__