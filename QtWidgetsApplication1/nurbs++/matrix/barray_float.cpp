/*=============================================================================
        File: barray_float.cpp
     Purpose:       
    Revision: $Id: barray_float.cpp,v 1.2 2002/05/13 21:07:45 philosophil Exp $
  Created by: Philippe Lavoie          (3 Oct, 1996)
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
#ifndef barray_float_h__
#define barray_float_h__



#include "barray.h"

namespace PLib {

#ifdef NO_IMPLICIT_TEMPLATES

  template class BasicArray<float> ;
  template void resizeBasicArray<float>(BasicArray<float>&,int) ;
  template int operator!=(const BasicArray<float>&,const BasicArray<float>&); 
  template int operator==(const BasicArray<float>&,const BasicArray<float>&); 
  template istream& operator>>(istream& is, BasicArray<float>& ary);
  template ostream& operator<<(ostream& os, const BasicArray<float>& ary);


#endif

}

#endif // barray_float_h__