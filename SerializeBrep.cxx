#include "SerializeBrep.h"

ostream & operator << ( ostream &os, AcDbRegion * region )
{
  os << "! AcDbRegion\n";
  return os;
}

ostream & operator << ( ostream &os, AcDb3dSolid * solid )
{
  os << "! AcDb3dSolid\n";
  return os;
}
