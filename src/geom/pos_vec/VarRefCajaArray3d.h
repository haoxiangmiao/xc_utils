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
//VarRefCajaArray3d.h 

#ifndef VARREFCAJAARRAY3D_H
#define VARREFCAJAARRAY3D_H

#include "BaseRefCajaArray3d.h"


//! @ingroup GEOM
//
//! @brief Reference to a "sub-array".
template <class ARRAY_3D>
class VarRefCajaArray3d: public BaseRefCajaArray3d
  {
    ARRAY_3D &ttz;
  public:
    typedef typename ARRAY_3D::const_reference const_reference;
    typedef typename ARRAY_3D::reference reference;

    explicit VarRefCajaArray3d(ARRAY_3D &m,const size_t &iLayer=1,const size_t &f= 1,const size_t &c= 1);
    VarRefCajaArray3d(ARRAY_3D &m,const Array3dRange &rango);
    VarRefCajaArray3d(ARRAY_3D &t,const size_t &iLayer,const RangoIndice &row_range,const RangoIndice &column_range);
    VarRefCajaArray3d(ARRAY_3D &t,const RangoIndice &layer_range,const size_t &iRow,const RangoIndice &column_range);
    VarRefCajaArray3d(ARRAY_3D &t,const RangoIndice &layer_range,const RangoIndice &row_range,const size_t &col);
    VarRefCajaArray3d(ARRAY_3D &t,const size_t &iLayer,const size_t &iRow,const RangoIndice &column_range);
    VarRefCajaArray3d(ARRAY_3D &t,const size_t iLayer,const RangoIndice &row_range,const size_t &col);
    VarRefCajaArray3d(ARRAY_3D &t,const RangoIndice &layer_range,const size_t &iRow,const size_t &col);
    inline virtual ~VarRefCajaArray3d(void) {}
    inline virtual const_reference operator()(size_t iLayer=1,size_t iRow=1,size_t col=1) const
      { return ttz(iLayer+offset_cp, iRow+offset_f,col+offset_c); }
    inline virtual reference operator()(size_t iLayer=1,size_t iRow=1,size_t col=1)
      { return ttz(iLayer+offset_cp, iRow+offset_f,col+offset_c); }
  };

template<class ARRAY_3D>
VarRefCajaArray3d<ARRAY_3D>::VarRefCajaArray3d(ARRAY_3D &t,const size_t &iLayer,const size_t &f,const size_t &c)
  : BaseRefCajaArray3d(iLayer,f,c,t.getNumberOfLayers(),t.getNumberOfRows(),t.getNumberOfColumns()),ttz(t) {}

template<class ARRAY_3D>
VarRefCajaArray3d<ARRAY_3D>::VarRefCajaArray3d(ARRAY_3D &t,const Array3dRange &rango)
  : BaseRefCajaArray3d(clip(rango,t)),ttz(t) {}

template<class ARRAY_3D>
VarRefCajaArray3d<ARRAY_3D>::VarRefCajaArray3d(ARRAY_3D &t,const size_t &iLayer,const RangoIndice &row_range,const RangoIndice &column_range)
  : BaseRefCajaArray3d(iLayer,clip(row_range,t.getNumberOfRows()),clip(column_range,t.getNumberOfColumns())),ttz(t) 
  {
    if(iLayer>ttz.getNumberOfLayers())
      std::clog << "Aviso; layer index: " << iLayer << " out of range in array with ranges: " << Array3dRange(ttz) << std::endl;
  }

template<class ARRAY_3D>
VarRefCajaArray3d<ARRAY_3D>::VarRefCajaArray3d(ARRAY_3D &t,const RangoIndice &layer_range,const size_t &iRow,const RangoIndice &column_range)
  : BaseRefCajaArray3d(clip(layer_range,t.getNumberOfLayers()),iRow,clip(column_range,t.getNumberOfColumns())),ttz(t)
  {
    if(iRow>ttz.getNumberOfRows())
      std::clog << "Aviso; row index: " << iRow
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
  }

template<class ARRAY_3D>
VarRefCajaArray3d<ARRAY_3D>::VarRefCajaArray3d(ARRAY_3D &t,const RangoIndice &layer_range,const RangoIndice &row_range,const size_t &col)
  : BaseRefCajaArray3d(clip(layer_range,t.getNumberOfLayers()),clip(row_range,t.getNumberOfRows()),col),ttz(t)
  {
    if(col>ttz.getNumberOfColumns())
      std::clog << "Aviso; column index: " << col
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
  }

template<class ARRAY_3D>
VarRefCajaArray3d<ARRAY_3D>::VarRefCajaArray3d(ARRAY_3D &t,const size_t &iLayer,const size_t &iRow,const RangoIndice &column_range)
  : BaseRefCajaArray3d(iLayer,iRow,clip(column_range,t.getNumberOfColumns())),ttz(t)
  {
    if(iLayer>ttz.getNumberOfLayers())
      std::clog << "Aviso; layer index: " << iLayer
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
    if(iRow>ttz.getNumberOfRows())
      std::clog << "Aviso; row index: " << iRow
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
  }

template<class ARRAY_3D>
VarRefCajaArray3d<ARRAY_3D>::VarRefCajaArray3d(ARRAY_3D &t,const size_t iLayer,const RangoIndice &row_range,const size_t &col)
  : BaseRefCajaArray3d(iLayer,clip(row_range,t.getNumberOfRows()),col),ttz(t)
  {
    if(iLayer>ttz.getNumberOfLayers())
      std::clog << "Aviso; layer index: " << iLayer
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
    if(col>ttz.getNumberOfColumns())
      std::clog << "Aviso; column index: " << col
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
  }

template<class ARRAY_3D>
VarRefCajaArray3d<ARRAY_3D>::VarRefCajaArray3d(ARRAY_3D &t,const RangoIndice &layer_range,const size_t &iRow,const size_t &col)
  : BaseRefCajaArray3d(clip(layer_range,t.getNumberOfLayers()),iRow,col),ttz(t)
  {
    if(iRow>ttz.getNumberOfRows())
      std::clog << "Aviso; row index: " << iRow
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
    if(col>ttz.getNumberOfColumns())
      std::clog << "Aviso; column index: " << col
		<< " out of range in array with ranges: "
		<< Array3dRange(ttz) << std::endl;
  }

template <class ARRAY_3D>
inline std::ostream &operator<<(std::ostream &os,const VarRefCajaArray3d<ARRAY_3D> &c)
  {
    PrintArray3d(c,os);
    return os;
  }

template <class ARRAY_3D, class TRF>
const VarRefCajaArray3d<ARRAY_3D> &transforma(const VarRefCajaArray3d<ARRAY_3D> &caja,const TRF &trf)
  {
    static VarRefCajaArray3d<ARRAY_3D> retval;
    retval= caja;
    const size_t n_layers= caja.getNumberOfLayers();
    const size_t n_rows= caja.getNumberOfRows();
    const size_t n_columns= caja.getNumberOfColumns();
    for(size_t k=1;k<=n_layers;k++) //For each layer.
      for(size_t i=1;i<=n_rows;i++) //For each row.
        for(size_t j=1;j<=n_columns;j++) //For each column.
          retval(i,j,k)= Transforma(caja(i,j,k));
    return retval;
  }

#endif
