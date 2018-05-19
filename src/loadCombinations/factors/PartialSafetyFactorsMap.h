//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  Este software es libre: usted puede redistribuirlo y/o modificarlo 
//  bajo los términos de la Licencia Pública General GNU publicada 
//  por la Fundación para el Software Libre, ya sea la versión 3 
//  de la Licencia, o (a su elección) cualquier versión posterior.
//
//  Este software se distribuye con la esperanza de que sea útil, pero 
//  SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita 
//  MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO. 
//  Consulte los detalles de la Licencia Pública General GNU para obtener 
//  una información más detallada. 
//
// Debería haber recibido una copia de la Licencia Pública General GNU 
// junto a este programa. 
// En caso contrario, consulte <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//PartialSafetyFactorsMap.h
//Contenedor de coeficientes de simultaneidad de acciones.

#ifndef PARTIALSAFETYFACTORSMAP_H
#define PARTIALSAFETYFACTORSMAP_H

#include "xc_utils/src/nucleo/EntCmd.h"
#include "PartialSafetyFactors.h"
#include "FactorsMap.h"


namespace cmb_acc {

//! @ingroup CMBACC
//
//! @brief Contenedor de coeficientes de simultaneidad de acciones.
class PartialSafetyFactorsMap: public FactorsMap<PartialSafetyFactors>
  {
  private:
    friend class ActionContainer;
  public:
    PartialSafetyFactorsMap(void);
  };
} // fin namespace cmb_acc

#endif