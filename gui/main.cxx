#include <cstdlib>

#include <QApplication>

#include "MainDialog.h"

#include "dwg2ansysVersion.h"

int main( int argc, char** argv )
{
  QApplication app( argc, argv );

  app.setApplicationName( "dwg2ansys" );
  app.setOrganizationName( "Nasztanovics Ferenc" );
  app.setOrganizationDomain( "naszta.hu" );
  app.setApplicationVersion( dwg2ansys_VERSION );

  MainDialog GUI;
  GUI.show();
  return app.exec();
}

#ifdef WIN32
#include <windows.h>
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  return main( nCmdShow, &lpCmdLine ); 
}
#endif
