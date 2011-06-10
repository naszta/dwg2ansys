#include "GeomDB.h"

#include "dbregion.h"
#include "dbsol3d.h"
#include "dbmain.h"
#include "dbents.h"

size_t GeomDB::AddRegion( AcDbRegion * region )
{
  return ERROR_ID;
}

size_t GeomDB::AddSolid( AcDb3dSolid * solid )
{
  return ERROR_ID;
}

bool GeomDB::AddAdditionalEntities( AcDbEntity * entity )
{
  AcDbRegion * region = AcDbRegion::cast( entity );
  if ( region != 0 )
  {
    return ( this->AddRegion( region ) != ERROR_ID );
  }
  AcDb3dSolid * solid = AcDb3dSolid::cast( entity );
  if ( solid != 0 )
  {
    return ( this->AddSolid( solid ) != ERROR_ID );
  }
  return false;
}

