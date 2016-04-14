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
//ActionsFamiliesMap.h
//Contenedor de familias de acciones.

#ifndef MAPFAMILIASACC_H
#define MAPFAMILIASACC_H

#include "xc_utils/src/base/EntConNmb.h"
#include <map>


namespace cmb_acc {

class ActionsFamily;
class LoadCombinationVector;
class PsiCoeffsMap;
class Action;
class ActionRValue;
class ActionContainer;

//! @ingroup CMBACC
//
//! @brief Contenedor de familias de acciones.
class ActionsFamiliesMap: public EntConNmb
  {
  public:
    typedef std::map<std::string,ActionsFamily *> map_familias;
    typedef map_familias::iterator iterator;
    typedef map_familias::const_iterator const_iterator;

  private:
    map_familias familias; //!< Conjunto de familias.

    bool existe(const std::string &nmb) const;
    ActionsFamily *crea_familia_acc(const std::string &nmb);
    ActionsFamily *busca_familia_acc(const std::string &nmb);
    const ActionsFamily *busca_familia_acc(const std::string &nmb) const;
    void clear(void);
    ActionsFamiliesMap(const ActionsFamiliesMap &otro);
    ActionsFamiliesMap &operator=(const ActionsFamiliesMap &otro);
  protected:
    friend class ActionContainer;
  public:
    ActionsFamiliesMap(const std::string &nmb);
    ActionRValue &inserta(const std::string &,const Action &,const std::string &nmb_coefs_psi="");
    LoadCombinationVector GetLoadCombinations(const bool &elu,const bool &sit_accidental) const;
    size_t getNumActions(void) const;
    const PsiCoeffsMap *getPtrPsiCoeffs(void) const;
    bool Vacia(void) const;
    virtual ~ActionsFamiliesMap(void);
  };
} // fin namespace cmb_acc

#endif