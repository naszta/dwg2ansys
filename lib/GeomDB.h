#ifndef GeomDBH
#define GeomDBH 1

#include "dwg2ansysLibExport.h"
#include "dwg2ansysVersion.h"

#include <iostream>

using std::ostream;

class AcDbEntity;
class AcDbRegion;
class AcDb3dSolid;

class internalPointStore;
class internalLineStore;
class internalArcStore;
class internalCircleStore;

class dwg2ansysLib_EXPORT GeomDB
{
  friend class Serialize;
public:
  enum { ERROR_ID = 0xFFFFFFFF };
  GeomDB( void );
  virtual ~GeomDB( void );
  virtual bool AddEntity( AcDbEntity * entity );
  virtual GeomDB & operator << ( AcDbEntity * entity );

protected:
  virtual size_t AddPoint( double point[3] );
  template <class T> size_t AddPoint( T &t_value )
  {
    double values[3];
    values[0] = t_value[0];
    values[1] = t_value[1];
    values[2] = t_value[2];
    return this->AddPoint( values );
  };
  virtual size_t AddLine( size_t from, size_t to );
  virtual size_t AddArc( double center[3], double normal[3], double radius, double start_angle, double end_angle );
  template <class T1, class T2> size_t AddArc( T1 center, T2 normal, double radius, double start_angle, double end_angle )
  {
    double cent[3], norm[3];
    cent[0] = center[0];
    cent[1] = center[1];
    cent[2] = center[2];
    norm[0] = normal[0];
    norm[1] = normal[1];
    norm[2] = normal[2];
    return this->AddArc( cent, norm, radius, start_angle, end_angle );
  };
  virtual size_t AddCircle( double center[3], double normal[3], double radius );
  template <class T1, class T2> size_t AddCircle( T1 center, T2 normal, double radius )
  {
    double cent[3], norm[3];
    cent[0] = center[0];
    cent[1] = center[1];
    cent[2] = center[2];
    norm[0] = normal[0];
    norm[1] = normal[1];
    norm[2] = normal[2];
    return this->AddCircle( cent, norm, radius );
  };
  virtual bool AddAdditionalEntities( AcDbEntity * entity );
#ifdef USE_BREP_MODULE
  virtual size_t AddRegion( AcDbRegion * region );
  virtual size_t AddSolid( AcDb3dSolid * solid );
#endif

private:
  internalPointStore * point_store;
  internalLineStore * line_store;
  internalArcStore * arc_store;
  internalCircleStore * circle_store;
};

#endif
