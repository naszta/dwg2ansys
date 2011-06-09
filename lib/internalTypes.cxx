#include "internalTypes.h"

#include <memory.h>

internalPoint::internalPoint( double point[3] )
{
  memcpy( this->point, point, 3 * sizeof(double) );
}

internalLine::internalLine( size_t from, size_t to )
: from(from), to(to)
{

}

internalArc::internalArc( double center[3], double normal[3], double radius, double start_angle, double end_angle )
: radius(radius), start_angle(start_angle), end_angle(end_angle)
{
  memcpy( this->center, center, 3 * sizeof(double) );
  memcpy( this->normal, normal, 3 * sizeof(double) );
}

internalCircle::internalCircle( double center[3], double normal[3], double radius )
: radius(radius)
{
  memcpy( this->center, center, 3 * sizeof(double) );
  memcpy( this->normal, normal, 3 * sizeof(double) );
}

class internalPointStoreInternal : public vector<internalPoint *>{};

internalPointStore::internalPointStore( void )
  : store( new internalPointStoreInternal )
{

}

internalPointStore::~internalPointStore( void )
{
  clean_up_vector(this->store);
}

size_t internalPointStore::insert( double point[3] )
{
  size_t index = this->store->size();
  this->store->push_back( new internalPoint(point) );
  return index;
}

internalPoint * & internalPointStore::operator[]( size_t index )
{
  return (*this->store)[index];
}

size_t internalPointStore::size( void )
{
  return this->store->size();
}

void internalPointStore::clear( void )
{
  this->store->clear();
}
