#include "Serialize.h"

#include "internalTypes.h"

GeomDBWriter::GeomDBWriter( GeomDB &my_db )
  : my_db(my_db)
{

}

void GeomDBWriter::write( ostream &os )
{
  this->write_header(os);

  size_t i = 0;
  while ( i < my_db.point_store->size() )
  {
    this->write_point( os, i+1, (*my_db.point_store)[i]->point );
    ++i;
  }

  i = 0;
  while ( i < my_db.line_store->size() )
  {
    this->write_line( os, i+1, (*my_db.line_store)[i]->from, (*my_db.line_store)[i]->to );
    ++i;
  }

  i = 0;
  while ( i < my_db.arc_store->size() )
  {
    this->write_arc( os, i+1, (*my_db.arc_store)[i]->center, (*my_db.arc_store)[i]->normal, (*my_db.arc_store)[i]->radius, (*my_db.arc_store)[i]->start_angle, (*my_db.arc_store)[i]->end_angle );
    ++i;
  }

  i = 0;
  while ( i < my_db.circle_store->size() )
  {
    this->write_circle( os, i+1, (*my_db.circle_store)[i]->center, (*my_db.circle_store)[i]->normal, (*my_db.circle_store)[i]->radius );
    ++i;
  }

  this->write_footer(os);
}

void GeomDBWriter::write_header( ostream &os )
{
  os << "! This geometry was written by dwg2ansys, (c) Nasztanovics Ferenc\n";
  os << "! Version: " << dwg2ansys_VERSION << "\n";
  os << "/PREP7\n";
  os << "!\n";
}

void GeomDBWriter::write_point( ostream &os, size_t id, double point[3] )
{
  os << "K,";
  os << id << ",";
  os << point[0] << ",";
  os << point[1] << ",";
  os << point[2] << "\n";
}

void GeomDBWriter::write_line( ostream &os, size_t id, size_t from, size_t to )
{
  os << "L,";
  os << from << ",";
  os << to << "\n";
}

void GeomDBWriter::write_arc( ostream &os, size_t id, double center[3], double normal[3], double radius, double start_angle, double end_angle )
{

}

void GeomDBWriter::write_circle( ostream &os, size_t id, double center[3], double normal[3], double radius )
{

}

void GeomDBWriter::write_footer( ostream &os )
{
  os << "!\n";
  os << "! Number of points : " << my_db.point_store->size() << "\n";
  os << "! Number of lines  : " << my_db.line_store->size() << "\n";
  os << "! Number of arcs   : " << my_db.arc_store->size() << "\n";
  os << "! Number of circles: " << my_db.circle_store->size() << "\n";
  os << "!\n";
}

ostream & operator << ( ostream &os, GeomDBWriter &writer )
{
  writer.write(os);
  return os;
}

