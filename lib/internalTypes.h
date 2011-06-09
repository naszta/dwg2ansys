#ifndef internalTypesH
#define internalTypesH 1

#include <vector>
using std::vector;

template <class T> void clean_up_vector( T * &_arg )
{
  if ( _arg == 0 )
    return;
  for ( size_t i = 0; i < _arg->size(); ++i )
  {
    if ( (*_arg)[i] != 0 )
    {
      delete (*_arg)[i];
      (*_arg)[i] = 0;
    }
  }
  _arg->clear();
  delete _arg;
  _arg = 0;
}

struct internalPoint
{
  internalPoint( double point[3] );
  double point[3];
};

struct internalLine
{
  internalLine( size_t from, size_t to );
  size_t from, to;
};

struct internalArc
{
  internalArc( double center[3], double normal[3], double radius, double start_angle, double end_angle );
  double center[3];
  double normal[3];
  double radius;
  double start_angle;
  double end_angle;
};

struct internalCircle
{
  internalCircle( double center[3], double normal[3], double radius );
  double center[3];
  double normal[3];
  double radius;
};

class internalPointStoreInternal;

class internalPointStore
{
public:
  internalPointStore( void );
  ~internalPointStore( void );
  size_t insert( double point[3] );
  internalPoint * & operator[]( size_t index );
  size_t size( void );
  void clear( void );
private:
  internalPointStoreInternal * store;
};

class internalLineStore : public vector<internalLine *>{};
class internalArcStore : public vector<internalArc *>{};
class internalCircleStore : public vector<internalCircle *>{};

#endif
