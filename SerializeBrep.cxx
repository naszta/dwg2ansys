#include "SerializeBrep.h"

ostream & operator << ( ostream &os, AcDbRegion * region )
{
  os << "! region object \n";
  return os;
}

ostream & operator << ( ostream &os, AcDb3dSolid * solid )
{
  os << "! solid object \n";
  return os;
}
