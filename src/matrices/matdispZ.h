//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//matdispZ.h
//Matrices dispersas.

#ifndef MATDISPZ_H
#define MATDISPZ_H

#include "ZMatrix.h"
#include <map>
#include <algorithm>

template <class numero>
class matdispZ : public ZMatrix<numero>
  {
  public:
    typedef ZMatrix<numero> ZMatrix_number;
    typedef typename ZMatrix_number::size_type size_type;
    typedef std::map<size_type,numero> map_elem;

    class sp_vector: public map_elem
      {
      public:
        typedef typename map_elem::iterator iterator;
        typedef typename map_elem::const_iterator const_iterator;
        typedef typename map_elem::const_reverse_iterator const_reverse_iterator;
      private:
        inline int hasRow(const typename sp_vector::size_type f) const
          { return (find(f)!=this->end()); }
      public:
        sp_vector &operator+=(const sp_vector &v);
        sp_vector &operator-=(const sp_vector &v);
        void QuitaElem(const numero &n);
        void PutCol(const typename sp_vector::size_type c,ZMatrix_number &m) const;
        sp_vector getNumberOfRows(const typename sp_vector::size_type f1,const typename sp_vector::size_type f2) const;
        size_t ndiagL(const size_t &icol) const;
        size_t ndiagU(const size_t &icol) const;
        void writeCpp(std::ostream &os,const size_t &icol) const;
	void PutColBanda(const size_t &sz,const size_t &i,const size_t &ndiagu,numero *vptr) const;
      };
    typedef std::map<size_type, sp_vector> column_map;
    column_map columns;


    typedef typename sp_vector::const_iterator const_f_iterator;
    typedef typename sp_vector::iterator f_iterator;
    typedef typename column_map::const_iterator const_c_iterator;
    typedef typename column_map::iterator c_iterator;

  private:
    inline virtual size_type Tam(size_type ,size_type )
      { return 0; }
    inline virtual size_type Indice(const size_type &iRow,const size_type &col) const
      { return 0; }
    inline bool hasColumn(const size_type &c) const
      { return (columns.find(c)!=columns.end()); }
    inline const numero &PorDefecto(void) const
      { return (ZMatrix_number::operator()(1,1)); }
    bool IgualA(const matdispZ<numero> &otra) const;

    template<class M>
    matdispZ<numero> Post(const M &b) const;

    matdispZ<numero> Post(const matdispZ<numero> &b) const;

  public:

    matdispZ(size_type n_rows=1,size_type n_columns= 1)
      : ZMatrix_number(1,1,numero())
      { this->PutDim(n_rows,n_columns); }
    matdispZ(const matdispZ<numero> &otra)
      : ZMatrix_number(otra), columns(otra.columns)
      { this->PutDim(otra.n_rows,otra.n_columns); }
    matdispZ<numero>& operator =(const matdispZ<numero> &m)
      {
        ZMatrix_number::operator =(m);
        columns= m.columns;
        return *this;
      }
    matdispZ<numero>& operator+=(const matdispZ<numero> &m);
    matdispZ<numero>& operator-=(const matdispZ<numero> &m);


    size_t ndiagL(void) const;
    size_t ndiagU(void) const;
    void FillVectorBanda(numero *vptr) const;
    //Acceso a los elementos.
    numero &operator()(size_t iRow=1,size_t col=1)
      {
        assert(col>0 && col<=this->n_columns);
        assert(iRow>0 && iRow<=this->n_rows);
        return columns[col][iRow];
      }
    const numero &operator()(size_t iRow=1,size_t col=1) const
      {
        const_c_iterator k1= columns.find(col);
        if(k1!=columns.end())
          {
	    const_f_iterator k2= (k1->second).find(iRow);
            if(k2!= (k1->second).end())
              return k2->second;
            else
              return PorDefecto();
          }
        else 
          return PorDefecto();
      }
    const_c_iterator columns_begin(void) const
      { return columns.begin(); }
    const_c_iterator columns_end(void) const
      { return columns.end(); }
    c_iterator columns_begin(void)
      { return columns.begin(); }
    c_iterator columns_end(void)
      { return columns.end(); }
    const_f_iterator rows_begin(const const_c_iterator &ci) const
      { return ci->second.begin(); }
    const_f_iterator find_row(const const_c_iterator &ci,size_t f) const
      { return ci->second.find(f); }
    const_f_iterator rows_end(const const_c_iterator &ci) const
      { return ci->second.end(); }
    f_iterator find_row(const c_iterator &ci,size_t f)
      { return ci->second.find(f); }
    sp_vector &getColumn(const c_iterator &ci)
      { return ci->second; }

    size_type size(void) const;
    void Compacta(void);
    void Anula(void);
    void Identity(void);
    inline bool Cuadrada(void) const
      { return (this->n_rows == this->n_columns); }
    matdispZ<numero> &Trn(void);
    matdispZ<numero> GetTrn(void)
      {
        matdispZ<numero> retval(*this);
        retval.Trn();
        return retval;
      }
    matdispZ<numero> getBox(size_t f1, size_t c1, size_t f2, size_t c2) const;
    matdispZ<numero> getRow(size_t iRow) const
      { return getBox(iRow,1,iRow,this->n_columns); }
    matdispZ<numero> getColumn(size_t col) const
      { return getBox(1,col,this->n_rows,col); }
    void putBox(size_t f,size_t c,const matdispZ<numero> &box);
    numero Traza(void) const;
    ZMatrix_number GetCompleta(void) const;

    void writeCpp(std::ostream &os) const;

    template <class V>
    numero dot(const V &v2) const
    //Producto escalar de este por v2.
    //v2: column vector.
      {
        check_dot(*this,v2);
        return (this->Post(v2))(1,1);
      }
    numero dot(const matdispZ<numero> &v2) const
    //Producto escalar de este por v2.
    //v2: column vector.
      {
        check_dot(*this,v2);
        return (this->Post(v2))(1,1);
      }
    friend matdispZ<numero> operator+(const matdispZ<numero> &m1,const matdispZ<numero> &m2)
      {
        check_sum(m1,m2);
        matdispZ<numero> suma(m1);
        suma+= m2;
        suma.Compacta();
        return suma;
      }
    friend matdispZ<numero> operator-(const matdispZ<numero> &m1,const matdispZ<numero> &m2)
      {
        check_dif(m1,m2);
        matdispZ<numero> resta(m1);
        resta-=m2;
        resta.Compacta();
        return resta;
      }
    inline friend bool operator==(const matdispZ<numero> &m1,const matdispZ<numero> &m2)
      { return m1.IgualA(m2); }
    //Producto escalar de dos vectores.
    //v1: row vector.
    //v2: column vector.
    friend numero dot(const matdispZ<numero> &v1,const matdispZ<numero> &v2)
      { return v1.dot(v2); }
    friend numero dot(const matdispZ<numero> &v1,const ZMatrix<numero> &v2)
      { return v1.dot(v2); }
    friend matdispZ<numero> operator*(const matdispZ<numero> &m1,const matdispZ<numero> &m2)
      {
        check_prod(m1,m2);
        matdispZ<numero> producto(m1.Post(m2));
        return producto;
      }
    friend matdispZ<numero> operator*(const matdispZ<numero> &m1,const ZMatrix<numero> &m2)
      {
        check_prod(m1,m2);
        matdispZ<numero> producto(m1.Post(m2));
        return producto;
      }
    /*
    friend matdispZ<numero> operator*(const matdispZ<numero> &m1,const ZMatrix<numero> &m2)
      {
        check_prod(m1,m2);
        matdispZ<numero> producto(m1.n_rows,m2.getNumberOfColumns());
        matdispZ<numero>::size_type i=1,j=1;
        for (i= 1;i<=m1.n_rows;i++)
          for (j= 1;j<=m2.getNumberOfColumns();j++)
            producto(i,j) = dot(m1.getRow(i),m2.getColumn(j));
        return producto;
      }
    */
    /*
    friend matdispZ<numero> operator *(const matdispZ<numero> &m,const numero &p)
      {
        matdispZ<numero> producto(m);
        producto.Prod(p);
        return producto;
      }
    friend matdispZ<numero> operator *(const numero &p,const matdispZ<numero> &m)
      { return m*p; }

    friend std::istream &operator >> (std::istream &stream,matdispZ<numero> &m)
      { return ::operator >>(stream,(ZMatrix_number &) m); }
    */
  };

//sp_vector
template<class numero>
typename matdispZ<numero>::sp_vector &matdispZ<numero>::sp_vector::operator+=(const matdispZ<numero>::sp_vector &v)
  {
    const_iterator f;
    for(f= v.begin();f!=v.end();f++)
      if(hasRow(f->first))
        (*this)[f->first]+= f->second;
      else
        (*this)[f->first]= f->second;
    return *this;
  }
template<class numero>
typename matdispZ<numero>::sp_vector &matdispZ<numero>::sp_vector::operator-=(const matdispZ<numero>::sp_vector &v)
  {
    const_iterator f;
    for(f= v.begin();f!=v.end();f++)
      if(hasRow(f->first))
        (*this)[f->first]-= f->second;
      else
        (*this)[f->first]= f->second;
    return *this;
  }
template<class numero>
void matdispZ<numero>::sp_vector::QuitaElem(const numero &n)
  {
    iterator f;
    for(f= this->begin();f!=this->end();f++)
      if(f->second == n)
        this->erase(f);
  }
template<class numero>
void matdispZ<numero>::sp_vector::PutCol(const typename sp_vector::size_type c,ZMatrix_number &m) const
  {
    const_iterator f;
    for(f= this->begin();f!=this->end();f++)
      m(f->first,c)= f->second;
  }
template<class numero>
typename matdispZ<numero>::sp_vector matdispZ<numero>::sp_vector::getNumberOfRows(const typename sp_vector::size_type f1,const typename sp_vector::size_type f2) const
  {
    sp_vector retval;
    if(f2<f1) return retval;
    const_iterator f;
    for(f= this->begin();f!=this->end();f++)
      if((f->first>=f1) && (f->first<=f2))
        retval[f->first-f1+1]= f->second;
    return retval;
  }

//! @brief Return el número de diagonales, con algún elemento no nulo, que tiene the column por debajo de la diagonal principal. 
//! @param icol: Índice de the column a la que corresponde este vector.
template<class numero>
size_t matdispZ<numero>::sp_vector::ndiagL(const size_t &icol) const
  {
    size_t retval= 0;
    if(!this->empty())
      {
        const numero zero= numero();
        for(const_reverse_iterator f= this->rbegin();f!=this->rend();f++)
          {
            const size_t iRow= f->first;
            if(iRow>icol) //El elemento esta por debajo de la diagonal principal.
              {
                if(f->second != zero) //no nulo.
                  {
                    retval= iRow-icol;
                    break;
                  }
              }
            else //El elemento esta en la diagonal principal o por encima.
              break;
          }
      }
    return retval;
  }

//! @brief Return el número de diagonales, con algún elemento no nulo, que tiene the column por encima de la diagonal principal. 
//! @param icol: Índice de the column a la que corresponde este vector.
template<class numero>
size_t matdispZ<numero>::sp_vector::ndiagU(const size_t &icol) const
  {
    size_t retval= 0;
    if(!this->empty())
      {
        const numero zero= numero();
        for(const_iterator f= this->begin();f!=this->end();f++)
          {
            const size_t iRow= f->first;
            if(iRow<icol) //El elemento esta por encima de la diagonal principal.
              {
                if(f->second != zero) //no nulo.
                  {
                    retval= icol-iRow;
                    break;
                  }
              }
            else //El elemento esta en la diagonal principal o por debajo.
              break;
          }
      }
    return retval;
  }

//! @brief Escribe los elementos no nulos de the column en formato de C++.
template<class numero>
void matdispZ<numero>::sp_vector::writeCpp(std::ostream &os,const size_t &icol) const
  {
    if(!this->empty())
      {
        const numero zero= numero();
        for(const_iterator f= this->begin();f!=this->end();f++)
          if(f->second != zero)
            os << "mtx(" << f->first << ',' << icol << ")= " << f->second << "; ";
      }    
  }

//! @brief Coloca los elementos de the column que forman parte de la banda
//! en el vector que is being passed as parameter.
//! @param sz: Ancho de banda.
//! @param icol: Índice de the column.
//! @param ndiagu: Número de diagonales por encima de la principal.
//! @param vptr: Vector en el que se colocal los elementos.
template<class numero>
void matdispZ<numero>::sp_vector::PutColBanda(const size_t &sz,const size_t &icol,const size_t &ndiagu,numero *vptr) const
  {
    if(!this->empty())
      {
        const numero zero= numero();
        const int offset= (icol-1)*sz-icol+ndiagu;
        for(const_iterator f= this->begin();f!=this->end();f++)
          {
            const size_t iRow_banda= f->first+offset;
            if(f->second != zero)
              vptr[iRow_banda]= f->second;
          }
      }    
  }

//matdispZ
template <class numero>
matdispZ<numero>& matdispZ<numero>::operator+=(const matdispZ<numero> &m)
  {
    const_c_iterator c;
    for(c= m.columns.begin();c!=m.columns.end();c++)
      if(hasColumn(c->first))
        columns[c->first]+= c->second;
      else
        columns[c->first]= c->second;
    return *this;
  }

template <class numero>
matdispZ<numero>& matdispZ<numero>::operator-=(const matdispZ<numero> &m)
  {
    const_c_iterator c;
    for(c= m.columns.begin();c!=m.columns.end();c++)
      if(hasColumn(c->first))
        columns[c->first]-= c->second;
      else
        columns[c->first]= c->second;
    return *this;
  }

template <class numero>
typename matdispZ<numero>::size_type matdispZ<numero>::size(void) const
  {
    size_type retval= 0;
    const_c_iterator c;
    for(c= columns.begin();c!=columns.end();c++)
      retval+=c->second.size();
    return retval;
  }

template <class numero>
void matdispZ<numero>::Compacta(void)
  {
    const numero &n= PorDefecto();
    typename column_map::iterator c;
    for(c= columns.begin();c!=columns.end();c++)
      c->second.QuitaElem(n);
  }

template <class numero>
void matdispZ<numero>::Anula(void)
  { columns.erase(columns.begin(),columns.end()); }

template <class numero>
void matdispZ<numero>::Identity(void)
  {
    this->Anula();
    if(this->n_rows!=this->n_columns)
      std::cerr << "matdispZ::" << __FUNCTION__
	        << "not a square matrix: "
	        << this->n_rows << " x " << this->n_columns << std::endl;
    const size_t sz= std::min(this->n_rows,this->n_columns);
    for(size_t i=1;i<=sz;i++)
      (*this)(i,i)= 1.0;
    Compacta();
  }

template <class numero>
matdispZ<numero> &matdispZ<numero>::Trn(void)
  {
    ZMatrix_number::Trn();
    const_c_iterator c;
    const_f_iterator f;
    for(c= columns.begin();c!=columns.end();c++)
      for(f= c->second.find(c->first+1);f!=c->second.end();f++)
        std::swap((*this)(f->first,c->first),(*this)(c->first,f->first));
    Compacta();
    return *this;
  }

template <class numero>
size_t matdispZ<numero>::ndiagL(void) const
  {
    const_c_iterator c;
    size_t retval= 0;
    for(c= columns.begin();c!=columns.end();c++)
      retval= std::max(retval,c->second.ndiagL(c->first));
    return retval;
  }
template <class numero>
size_t matdispZ<numero>::ndiagU(void) const
  {
    const_c_iterator c;
    size_t retval= 0;
    for(c= columns.begin();c!=columns.end();c++)
      retval= std::max(retval,c->second.ndiagU(c->first));
    return retval;
  }

//! @brief Rellena el vector en banda que is being passed as parameter para su empleo en Arpack++.
template<class numero>
void matdispZ<numero>::FillVectorBanda(numero *vptr) const
  {
    const size_t ndiagu= ndiagU();
    const size_t ndiagl= ndiagL();
    const size_t ancho_banda= ndiagl+ndiagu+1;
    for(const_c_iterator c= columns.begin();c!=columns.end();c++)
      c->second.PutColBanda(ancho_banda,c->first,ndiagu,vptr);
  }

//! @brief Writes the matrix in C++ format (only non-zero components).
template<class numero>
void matdispZ<numero>::writeCpp(std::ostream &os) const
  {
    for(const_c_iterator c= columns.begin();c!=columns.end();c++)
      c->second.writeCpp(os,c->first);
  }


template <class numero>
matdispZ<numero> matdispZ<numero>::getBox(size_t f1, size_t c1, size_t f2, size_t c2) const
  {
    // XXX "mejorar esta rutina"
    this->check_get_box(f1,c1,f2,c2);
    matdispZ<numero> box(f2-f1+1,c2-c1+1);
    const_c_iterator c;
    const_f_iterator f;
    for(c= columns.begin();c!=columns.end();c++)
      for(f= c->second.begin();f!=c->second.end();f++)
        if( (c->first>=c1) && (c->first<=c2) &&
            (f->first>=f1) && (f->first<=f2))
          box(f->first-f1+1,c->first-c1+1)= f->second;
    return box;
  }

template <class numero>
void matdispZ<numero>::putBox(size_t f,size_t c,const matdispZ<numero> &box)
  {
    check_put_box(f,c,box);
    size_t i,j;
    for (i=1;i<=box.n_rows;i++)
      for (j=1;j<=box.n_columns;j++)
        (*this)(i+f-1,j+c-1)= box(i,j);
    Compacta();
  }

template<class numero>
numero matdispZ<numero>::Traza(void) const
  {
    this->check_traza();
    numero n= numero();
    const_c_iterator c;
    const_f_iterator f;
    for(c= columns.begin();c!=columns.end();c++)
      if((f= c->second.find(c->first)) != c->second.end())
        n+=f->second;
    return n;
  }

template<class numero>
typename matdispZ<numero>::ZMatrix_number matdispZ<numero>::GetCompleta(void) const
  {
    ZMatrix_number retval(this->n_rows,this->n_columns,PorDefecto());
    const_c_iterator c;
    for(c= columns.begin();c!=columns.end();c++)
      c->second.PutCol(c->first,retval);
    return retval;
  }

template<class numero>
bool matdispZ<numero>::IgualA(const matdispZ<numero> &otra) const
  {
    if(!CompDim(*this,otra)) return false;
    typename matdispZ<numero>::const_c_iterator c;
    for(c= this->columns.begin();c!=this->columns.end();c++)
      {
        typename matdispZ<numero>::const_f_iterator f;
        for(f= c->second.begin();f!=c->second.end();f++)
          if(f->second != otra(f->first,c->first)) return false;
      }
    return true;
  }

template<class numero>
//Return the product of this matrix by the matrix argument.
matdispZ<numero> matdispZ<numero>::Post(const matdispZ<numero> &b) const
  {
    check_prod(*this,b);
    matdispZ<numero> ret(this->getNumberOfRows(),b.getNumberOfColumns());
    const_c_iterator bc;
    const_c_iterator c;
    const_f_iterator f;
    for(bc= b.columns.begin();bc!=b.columns.end();bc++)
      for(c= columns.begin();c!=columns.end();c++)
        for(f= c->second.begin();f!=c->second.end();f++)
          ret(f->first,bc->first)+= f->second*b(c->first,bc->first);
    return(ret);
  }

template<class numero>
template<class M>
//Return the product of this matrix by the matrix argument.
matdispZ<numero> matdispZ<numero>::Post(const M &b) const
  {
    check_prod(*this,b);
    matdispZ<numero> ret(this->getNumberOfRows(),b.getNumberOfColumns());
    size_type bc;
    const_c_iterator c;
    const_f_iterator f;
    for(bc= 1;bc<=b.getNumberOfColumns();bc++)
      for(c= columns.begin();c!=columns.end();c++)
        for(f= c->second.begin();f!=c->second.end();f++)
          ret(f->first,bc)+= f->second*b(c->first,bc);
    return(ret);
  }


#endif
