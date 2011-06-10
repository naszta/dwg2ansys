#include "Serialize.h"

#include "internalTypes.h"

Serialize::Serialize( GeomDB &my_db )
  : my_db(my_db)
{

}

Serialize::Serialize( GeomDB * my_db )
  : my_db(*my_db)
{

}

Serialize::~Serialize( void )
{

}

void Serialize::write( ostream &os )
{
  this->write_header(os);

  size_t i = 0;
  this->write_point_header(os);
  while ( i < my_db.point_store->size() )
  {
    this->write_point( os, i+1, (*my_db.point_store)[i]->point );
    ++i;
  }
  this->write_point_footer(os);

  i = 0;
  this->write_line_header( os );
  while ( i < my_db.line_store->size() )
  {
    this->write_line( os, i+1, (*my_db.line_store)[i]->from, (*my_db.line_store)[i]->to );
    ++i;
  }
  this->write_line_footer( os );

  i = 0;
  this->write_arc_header(os);
  while ( i < my_db.arc_store->size() )
  {
    this->write_arc( os, i+1, (*my_db.arc_store)[i]->center, (*my_db.arc_store)[i]->normal, (*my_db.arc_store)[i]->radius, (*my_db.arc_store)[i]->start_angle, (*my_db.arc_store)[i]->end_angle );
    ++i;
  }
  this->write_arc_footer(os);

  i = 0;
  this->write_circle_header(os);
  while ( i < my_db.circle_store->size() )
  {
    this->write_circle( os, i+1, (*my_db.circle_store)[i]->center, (*my_db.circle_store)[i]->normal, (*my_db.circle_store)[i]->radius );
    ++i;
  }
  this->write_circle_footer(os);

  this->write_other_elements(os);

  this->write_footer(os);
}

void Serialize::write_header( ostream &os )
{
  os << "! This geometry was written by dwg2ansys, (c) Nasztanovics Ferenc\n";
  os << "! Version: " << dwg2ansys_VERSION << "\n";
  os << "/PREP7\n";
  os << "!\n";
}

void Serialize::write_point_header( ostream &os )
{

}

void Serialize::write_point( ostream &os, size_t id, double point[3] )
{
  os << "K,";
  os << id << ",";
  os << point[0] << ",";
  os << point[1] << ",";
  os << point[2] << "\n";
}

void Serialize::write_point_footer( ostream &os )
{

}

void Serialize::write_line_header( ostream &os )
{

}

void Serialize::write_line( ostream &os, size_t id, size_t from, size_t to )
{
  os << "L,";
  os << from << ",";
  os << to << "\n";
}

void Serialize::write_line_footer( ostream &os )
{

}

void Serialize::write_arc_header( ostream &os )
{

}

void Serialize::write_arc( ostream &os, size_t id, double center[3], double normal[3], double radius, double start_angle, double end_angle )
{

}

void Serialize::write_arc_footer( ostream &os )
{

}

void Serialize::write_circle_header( ostream &os )
{

}

void Serialize::write_circle( ostream &os, size_t id, double center[3], double normal[3], double radius )
{

}

void Serialize::write_circle_footer( ostream &os )
{

}

void Serialize::write_footer( ostream &os )
{
  os << "!\n";
  os << "! Number of points : " << my_db.point_store->size() << "\n";
  os << "! Number of lines  : " << my_db.line_store->size() << "\n";
  os << "! Number of arcs   : " << my_db.arc_store->size() << "\n";
  os << "! Number of circles: " << my_db.circle_store->size() << "\n";
  os << "!\n";
}

#ifndef USE_BREP_MODULE
void Serialize::write_other_elements( ostream &os )
{

}
#endif

ostream & operator << ( ostream &os, Serialize &writer )
{
  writer.write(os);
  return os;
}

