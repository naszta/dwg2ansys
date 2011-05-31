#ifndef SerializeH
#define SerializeH 1

#include <iostream>

using std::ostream;
using std::endl;

class AcDbEntity;

ostream & operator << ( ostream &os, AcDbEntity * entity );

#endif
