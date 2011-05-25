#include <cstdlib>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Convert.h"

int main( int argc, char** argv )
{
  if ( argc < 3 )
  {
    std::cout << "There is no enough input!\n\n";
    std::cout << "Usage: dwg2ansys <dwg file name> <ansys apdl file name>" << std::endl;
    return 0;
  }
  std::wostringstream woss;
  woss << argv[1];
  std::ofstream ansys_apdl( argv[2], std::ios_base::trunc | std::ios_base::out );
  if ( ! ansys_apdl.is_open() )
  {
    std::cout << "Output file cannot be opened for write!\n\n";
    std::cout << "Usage: dwg2ansys <dwg file name> <ansys apdl file name>" << std::endl;
    return 0;
  }
  if ( ! Convert::dwg_to_ansys( woss.str().c_str(), ansys_apdl ) )
  {
    std::cout << "AutoCAD DWG file cannot be opened!\n\n";
    std::cout << "Usage: dwg2ansys <dwg file name> <ansys apdl file name>" << std::endl;
  }
  ansys_apdl.flush();
  ansys_apdl.close();

  return 0;
}
