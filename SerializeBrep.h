#ifndef SerializeBrepH
#define SerializeBrepH

#include <iostream>

using std::ostream;
using std::endl;

class AcDbRegion;
class AcDb3dSolid;

ostream & operator << ( ostream &os, AcDbRegion * region );
ostream & operator << ( ostream &os, AcDb3dSolid * solid );

#endif
