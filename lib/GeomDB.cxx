#include "GeomDB.h"

#include "dbmain.h"
#include "dbents.h"

#include "internalTypes.h"

GeomDB::GeomDB( void )
  : point_store(new internalPointStore)
  , line_store(new internalLineStore)
  , arc_store(new internalArcStore)
  , circle_store(new internalCircleStore)
{

}

GeomDB::~GeomDB( void )
{
  clean_up_vector( this->point_store );
  clean_up_vector( this->line_store );
  clean_up_vector( this->arc_store );
  clean_up_vector( this->circle_store );
}

GeomDB & GeomDB::operator << ( AcDbEntity * entity )
{
  // point
  AcDbPoint * point = AcDbPoint::cast( entity );
  if ( point != 0 )
  {
    this->AddPoint( point->position() );
    return *this;
  }
  // line
  AcDbLine * line = AcDbLine::cast( entity );
  if ( line != 0 )
  {
    size_t start = this->AddPoint( line->startPoint() );
    size_t end = this->AddPoint( line->endPoint() );
    this->AddLine( start, end );
    return *this;
  }
  // polyline
  AcDbPolyline * polyline = AcDbPolyline::cast( entity );
  if ( polyline != 0 )
  {
    AcGePoint3d ac_point;
    size_t start = ERROR_ID;
    size_t end = ERROR_ID;
    for ( unsigned int i = 0; i < polyline->numVerts(); ++i )
    {
      if ( polyline->getPointAt( i, ac_point ) == Acad::eOk )
      {
        end = this->AddPoint( ac_point );
        this->AddLine( start, end );
        start = end;
      }
    }
    return *this;
  }
  // polyline 2d
  AcDb2dPolyline * polyline2d = AcDb2dPolyline::cast( entity );
  if ( polyline2d != 0 )
  {
    size_t start = ERROR_ID;
    size_t end = ERROR_ID;
    AcGePoint3d ac_point;
    AcDbObjectIterator * pBbObjIter = polyline2d->vertexIterator();
    AcDb2dVertex * p2dVert = 0;

    while ( ! pBbObjIter->done() )
    {
      if ( polyline2d->openVertex( p2dVert, pBbObjIter->objectId(), AcDb::kForRead ) == Acad::eOk )
      {
        ac_point = p2dVert->position();
        end = this->AddPoint( ac_point );
        this->AddLine( start, end );
        start = end;
        p2dVert->close();
        p2dVert = 0;
      }
      pBbObjIter->step();
    }
    delete pBbObjIter;
    return *this;
  }
  // polyline 3d
  AcDb3dPolyline * polyline3d = AcDb3dPolyline::cast( entity );
  if ( polyline3d != 0 )
  {
    size_t start = ERROR_ID;
    size_t end = ERROR_ID;
    AcGePoint3d ac_point;
    AcDbObjectIterator * pBbObjIter = polyline3d->vertexIterator();
    AcDb3dPolylineVertex * p3dVert = 0;

    while ( ! pBbObjIter->done() )
    {
      if ( polyline3d->openVertex( p3dVert, pBbObjIter->objectId(), AcDb::kForRead ) == Acad::eOk )
      {
        ac_point = p3dVert->position();
        end = this->AddPoint( ac_point );
        this->AddLine( start, end );
        start = end;
        p3dVert->close();
        p3dVert = 0;
      }
      pBbObjIter->step();
    }
    delete pBbObjIter;
    return *this;
  }
  // arc 
  AcDbArc * arc = AcDbArc::cast( entity );
  if ( arc != 0 )
  {
    this->AddArc( arc->center(), arc->normal(), arc->radius(), arc->startAngle(), arc->endAngle() );
    return *this;
  }
  // circle
  AcDbCircle * circle = AcDbCircle::cast( entity );
  if ( circle != 0 )
  {
    this->AddCircle( circle->center(), circle->normal(), circle->radius() );
    return *this;
  }
  return *this;
}

size_t GeomDB::AddPoint( double point[3] )
{
  return this->point_store->insert( point );
}

size_t GeomDB::AddLine( size_t from, size_t to )
{
  if ( ( from == ERROR_ID ) || ( to == ERROR_ID ) )
    return ERROR_ID;
  size_t return_value = this->line_store->size();
  this->line_store->push_back( new internalLine( from, to ) );
  return return_value;
}

size_t GeomDB::AddArc( double center[3], double normal[3], double radius, double start_angle, double end_angle )
{
  size_t return_value = this->arc_store->size();
  this->arc_store->push_back( new internalArc( center, normal, radius, start_angle, end_angle ) );
  return return_value;
}

size_t GeomDB::AddCircle( double center[3], double normal[3], double radius )
{
  size_t return_value = this->circle_store->size();
  this->circle_store->push_back( new internalCircle( center, normal, radius ) );
  return return_value;
}

