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
//Variable.h

#ifndef VARIABLE_H
#define VARIABLE_H

#include "OpndoConNombre.h"


class ExprAlgebra;

class Variable : public OpndoConNombre
  {
    bool asignada;
  public:
    Variable(void) : OpndoConNombre(), asignada(false) {}
    Variable(const std::string &nmb): OpndoConNombre(nmb), asignada(false) {}
    Variable(const Variable &otra): OpndoConNombre(otra), asignada(otra.asignada) {}
    Variable &operator=(const Variable &otra)
      {
        OpndoConNombre::operator =(otra);
        asignada= otra.asignada;
        return *this;
      }
    inline virtual bool Evaluable(void) const
      { return asignada; }
    inline virtual void Asigna(const double &d)
      {
        asignada= true;
        valor= d;
      }
    inline virtual void AsignaExpr(const double &d) {}
    inline void DesAsigna(void)
      { asignada= false; }
    virtual const Operando &Opera(const Operando *, const Operando *) const;
    virtual Rama Diferencia(const Variable &v,const Rama &) const;
    virtual void GetVariables(ConjVariables &cv) const;
  };

#endif
