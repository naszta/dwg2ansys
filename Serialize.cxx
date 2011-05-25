#include "Serialize.h"

#include "dbmain.h"
#include "dbents.h"

#include "dwg2ansysVersion.h"

#ifdef USE_BREP_MODULE
# include "SerializeBrep.h"
# include "dbregion.h"
# include "dbsol3d.h"
#endif

#include "Model.h"

#include <vector>

void unknown_type( ostream &os, AcDbEntity * entity, const char * base_type )
{
  os << "! Unsupported " << base_type << " type : " << entity->isA()->name() << "\n";
}

ostream & operator << ( ostream &os, AcDbLine * line )
{
  AcGePoint3d p0, p1;
  line->getStartPoint(p0);
  line->getEndPoint(p1);

  os << "K," << ++Model::CurrentModel.NumOfPoints << "," << p0[0] << "," << p0[1] << "," << p0[2] << "\n";
  os << "K," << ++Model::CurrentModel.NumOfPoints << "," << p1[0] << "," << p1[1] << "," << p1[2] << "\n";
  os << "L," << ( Model::CurrentModel.NumOfPoints - 1 ) << "," << Model::CurrentModel.NumOfPoints << "\n";
  
  return os;
}

ostream & operator << ( ostream &os, AcDb2dPolyline * polyline2d )
{
  AcGePoint3d p0;
  AcDbObjectIterator * pBbObjIter = polyline2d->vertexIterator();
  AcDb2dVertex * p2dVert = 0;
  int prev_id = -1;

  while ( ! pBbObjIter->done() )
  {
    if ( polyline2d->openVertex( p2dVert, pBbObjIter->objectId(), AcDb::kForRead ) == Acad::eOk )
    {
      p0 = p2dVert->position();
      os << "K," << ++Model::CurrentModel.NumOfPoints << "," << p0[0] << "," << p0[1] << "," << p0[2] << "\n";
      if ( prev_id >= 0 )
        os << "L," << prev_id << "," << Model::CurrentModel.NumOfPoints << "\n";
      prev_id = Model::CurrentModel.NumOfPoints;
      p2dVert->close();
      p2dVert = 0;
    }
    pBbObjIter->step();
  }
  delete pBbObjIter;

  return os;
}

ostream & operator << ( ostream &os, AcDb3dPolyline * polyline3d )
{
  AcGePoint3d p0;
  AcDbObjectIterator * pBbObjIter = polyline3d->vertexIterator();
  AcDb3dPolylineVertex * p3dVert = 0;
  int prev_id = -1;

  while ( ! pBbObjIter->done() )
  {
    if ( polyline3d->openVertex( p3dVert, pBbObjIter->objectId(), AcDb::kForRead ) == Acad::eOk )
    {
      p0 = p3dVert->position();
      os << "K," << ++Model::CurrentModel.NumOfPoints << "," << p0[0] << "," << p0[1] << "," << p0[2] << "\n";
      if ( prev_id >= 0 )
        os << "L," << prev_id << "," << Model::CurrentModel.NumOfPoints << "\n";
      prev_id = Model::CurrentModel.NumOfPoints;
      p3dVert->close();
      p3dVert = 0;
    }
    pBbObjIter->step();
  }
  delete pBbObjIter;

  return os;
}

ostream & operator << ( ostream &os, AcDbPolyline * polyline )
{
  AcGePoint3d p0;
  unsigned int NumberOfPoints = polyline->numVerts();
  if ( NumberOfPoints < 2 )
    return os;

  int prev_id = -1;
  for ( unsigned int i = 0; i < NumberOfPoints; ++i )
  {
    polyline->getPointAt( i, p0 );
    os << "K," << ++Model::CurrentModel.NumOfPoints << "," << p0[0] << "," << p0[1] << "," << p0[2] << "\n";
    if ( prev_id >= 0 )
      os << "L," << prev_id << "," << Model::CurrentModel.NumOfPoints << "\n";
    prev_id = Model::CurrentModel.NumOfPoints;
  }

  return os;
}

ostream & operator << ( ostream &os, AcDbCurve * curve )
{
  AcDbLine * line = AcDbLine::cast( curve );
  if ( line != 0 )
  {
    os << line;
    return os;
  }
  AcDb2dPolyline * polyline2d = AcDb2dPolyline::cast( curve );
  {
    os << polyline2d;
    return os;
  }
  AcDb3dPolyline * polyline3d = AcDb3dPolyline::cast( curve );
  if ( polyline3d != 0 )
  {
    os << polyline3d;
    return os;
  }
  AcDbPolyline * polyline = AcDbPolyline::cast( curve );
  if ( polyline != 0 )
  {
    os << polyline;
    return os;
  }
  unknown_type( os, curve, "curve" );
  return os;
}

ostream & operator << ( ostream &os, AcDbPoint * point )
{
  AcGePoint3d p0 = point->position();
  os << "K," << ++Model::CurrentModel.NumOfPoints << "," << p0[0] << "," << p0[1] << "," << p0[2] << "\n";
  return os;
}

ostream & operator << ( ostream &os, AcDbEntity * entity )
{
  AcDbCurve * curve = AcDbCurve::cast( entity );
  if ( curve != 0 )
  {
    os << curve;
    return os;
  }
  AcDbPoint * point = AcDbPoint::cast( entity );
  if ( point != 0 )
  {
    os << point;
    return os;
  }
#ifdef USE_BREP_MODULE
  AcDbRegion * region = AcDbRegion::cast( entity );
  if ( region != 0 )
  {
    os << region;
    return os;
  }
  AcDb3dSolid * solid = AcDb3dSolid::cast( entity );
  if ( solid != 0 )
  {
    os << solid;
    return os;
  }
#endif
  unknown_type( os, entity, "entity" );
  return os;
}
