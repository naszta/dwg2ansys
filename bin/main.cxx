#include <cstdlib>

#include <iostream>

#include <vector>

#include "Convert.h"

int main( int argc, char** argv )
{
  if ( argc < 3 )
  {
    std::cout << "There is no enough input!\n\n";
    std::cout << "Usage: dwg2ansys <dwg file name> <ansys apdl file name>" << std::endl;
    return 0;
  }

  size_t size = strlen( argv[1] );
  std::vector<wchar_t> source_file_name( size + 1 );
  for ( size_t i = 0; i < size; ++i )
    source_file_name[i] = argv[1][i];
  source_file_name[size] = 0;

  size = strlen( argv[2] );
  std::vector<wchar_t> target_file_name( size + 1 );
  for ( size_t i = 0; i < size; ++i )
    target_file_name[i] = argv[2][i];
  target_file_name[size] = 0;

  if ( ! Convert::dwg_to_ansys( &source_file_name[0], &target_file_name[0] ) )
  {
    std::cout << "AutoCAD DWG file cannot be opened!\n\n";
    std::cout << "Usage: dwg2ansys <dwg file name> <ansys apdl file name>" << std::endl;
  }

  return 0;
}

#ifdef WIN32
#include <windows.h>
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  if ( ( lpCmdLine == 0 ) || ( lpCmdLine[0] == 0 ) )
  {
    std::cout << "There is no enough input!\n\n";
    std::cout << "Usage: dwg2ansys <dwg file name> <ansys apdl file name>" << std::endl;
    return 0;
  }
  size_t i = 0;
  std::vector<char *> start_array;
  start_array.push_back(0);
  start_array.push_back( lpCmdLine );

  while ( lpCmdLine[i] != 0 )
  {
    if ( lpCmdLine[i] == ' ' )
    {
      lpCmdLine[i] = 0;
      start_array.push_back( lpCmdLine + i + 1 );
    }
    ++i;
  }
  if ( ( lpCmdLine + i ) == start_array.back() )
    start_array.pop_back();

  return main( start_array.size(), &start_array[0] ); 
}
#endif
