//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  XC utils is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  (at your option) any later version.
//
//  This software is distributed in the hope that it will be useful, but 
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.  
//
// You should have received a copy of the GNU General Public License 
// along with this program.
// If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//Tridiag.h
//Procedimiento para la soluciOn de un sistema de ecuaciones tridiagonal.
//Que el mEtodo devuelva como resultado regular= 1 sOlo quiere decir
//que no puede calcular la solucion no que no exista. Por tanto en
//estos casos deberA intentarse encontrar la soluciOn mediante un mEtodo
//general (gauss,...)

#ifndef TRIDIAG_H
#define TRIDIAG_H

#include <cmath>
#include "xc_utils/src/matrices/matridZ.h"
#include "xc_utils/src/utils/misc_utils/matem.h"
#include "gj_aux.h"

template <class treal>
void fil(const size_t &i,
         matridZ<treal> &a,
         ZMatrix<treal> &b,
         int &regular)
  {
    a(i,i)-= a(i,i-1)*a(i-1,i);
    regular= (gj_abs(a(i,i))>zero);
    if(regular)
      {
        a(i,i+1)/=a(i,i);
        b(i)= (b(i)-a(i,i-1)*b(i-1))/a(i,i);
      }
  }

template<class treal>
ZMatrix<treal> calcularx(matridZ<treal> &a,ZMatrix<treal> &b)
  {
    size_t n= a.getNumberOfRows();
    ZMatrix<treal> x(n,1,0.0);
    x(n)= b(n);
    for(size_t k=n-1;k>=1;k--) x(k)=b(k)-x(k+1)*a(k,k+1);
    return x;
  }

template <class treal>
ZMatrix<treal> tridiag(matridZ<treal> &a,ZMatrix<treal> &b,int &regular)
  {
    size_t i,n= a.getNumberOfRows();
    i=0; regular=1;
    while(regular && (i<n))
      { i++; fil(i,a,b,regular); }
    ZMatrix<treal> x;
    if(regular) x= calcularx(a,b);
    return x;
  }
#endif
