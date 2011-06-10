#ifndef SerializeH
#define SerializeH 1

#include <iostream>
#include "GeomDB.h"

#include "dwg2ansysLibExport.h"
#include "dwg2ansysVersion.h"

using std::ostream;

class dwg2ansysLib_EXPORT Serialize
{
public:
  Serialize( GeomDB &my_db );
  Serialize( GeomDB * my_db );
  virtual ~Serialize( void );
  virtual void write( ostream &os );
protected:
  virtual void write_header( ostream &os );
  virtual void write_point_header( ostream &os );
  virtual void write_point( ostream &os, size_t id, double point[3] );
  virtual void write_point_footer( ostream &os );
  virtual void write_line_header( ostream &os );
  virtual void write_line( ostream &os, size_t id, size_t from, size_t to );
  virtual void write_line_footer( ostream &os );
  virtual void write_arc_header( ostream &os );
  virtual void write_arc( ostream &os, size_t id, double center[3], double normal[3], double radius, double start_angle, double end_angle );
  virtual void write_arc_footer( ostream &os );
  virtual void write_circle_header( ostream &os );
  virtual void write_circle( ostream &os, size_t id, double center[3], double normal[3], double radius );
  virtual void write_circle_footer( ostream &os );
  virtual void write_footer( ostream &os );
  virtual void write_other_elements( ostream &os );
private:
  GeomDB &my_db;
};

dwg2ansysLib_EXPORT ostream & operator << ( ostream &os, Serialize &writer );

#endif
