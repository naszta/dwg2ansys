#include "AcadHost.h"

#include <Windows.h>

#include "dbmain.h"

#include "dwg2ansysVersion.h"

AcadHost::StaticHost AcadHost::Instance;

AcadHost::AcadHost(  int createGlobals /* = 1 */ )
: AcDbHostApplicationServices( createGlobals )
{

}

AcadHost::~AcadHost( void )
{

}


Acad::ErrorStatus AcadHost::findFile( ACHAR * pcFullPathOut, int nBufferLength,
  const ACHAR * pcFilename, AcDbDatabase * pDb, AcDbHostApplicationServices::FindFileHint hint )
{
  ACHAR pExtension[5];
  switch (hint)
  {
  case kCompiledShapeFile:
    wcscpy(pExtension, L".shx" );
    break;
  case kTrueTypeFontFile:
    wcscpy(pExtension, L".ttf" );
    break;
  case kPatternFile:
    wcscpy(pExtension, L".pat" );
    break;
  case kARXApplication:
    wcscpy(pExtension, L".dbx" );
    break;
  case kFontMapFile:
    wcscpy(pExtension, L".fmp" );
    break;
  case kXRefDrawing:
    wcscpy(pExtension, L".dwg" );
    break;
  case kFontFile:
  case kEmbeddedImageFile:
  default:
    pExtension[0] = L'\0';
    break;
  }
  ACHAR* filePart;
  DWORD result;
  result = SearchPathW(NULL, pcFilename, (LPCWSTR) pExtension, nBufferLength, pcFullPathOut, &filePart);
  if (result && result < (DWORD)nBufferLength)
    return Acad::eOk;
  else
    return Acad::eFileNotFound;
}

// Return the Install directory for customizable files
Acad::ErrorStatus 
  AcadHost::getRoamableRootFolder(const ACHAR*& folder)
{
  Acad::ErrorStatus ret = Acad::eOk;
  static ACHAR buf[MAX_PATH] = L"\0"; //MDI SAFE
  if (buf[0]==0)
    if (GetModuleFileNameW(NULL, buf, MAX_PATH) != 0)
      ret = Acad::eRegistryAccessError;
  folder = buf;
  return ret;
}

// Return the Install directory for customizable files
Acad::ErrorStatus 
  AcadHost::getLocalRootFolder(const ACHAR*& folder)
{
  Acad::ErrorStatus ret = Acad::eOk;
  static ACHAR buf[MAX_PATH] = L"\0"; //MDI SAFE
  if (buf[0]==0)
    if (GetModuleFileNameW(NULL, buf, MAX_PATH) != 0)
      ret = Acad::eRegistryAccessError;
  folder = buf;
  return ret;
}

// Return our company name
const ACHAR * AcadHost::companyName( void )
{
  return L"NasztaSoft";
}

// Return our product name
const ACHAR * AcadHost::product( void )
{
  return L"Dwg2Ansys";
}

// Return our product version string
const ACHAR * AcadHost::versionString( void )
{
  return dwg2ansys_VERSION_W;
}

// Return our product major version
int AcadHost::releaseMajorVersion( void )
{
  return dwg2ansys_MAJOR_VERSION;
}

// Return our product minor version
int AcadHost::releaseMinorVersion( void )
{
  return dwg2ansys_MINOR_VERSION;
}

AcadHost::StaticHost::StaticHost( void )
  : host( new AcadHost )
{
  acdbSetHostApplicationServices( this->host );
}

AcadHost::StaticHost::~StaticHost( void )
{
  if ( this->host != 0 )
  {
    acdbCleanUp();
    delete this->host;
    this->host = 0;
  }
}
