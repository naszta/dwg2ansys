#ifndef AcadHostH
#define AcadHostH 1

#include "dbapserv.h"

class AcadHost : public AcDbHostApplicationServices
{
public:
  AcadHost( int createGlobals = 1 );
  virtual ~AcadHost( void );

  Acad::ErrorStatus findFile( ACHAR * pcFullPathOut, int nBufferLength,
    const ACHAR * pcFilename, AcDbDatabase * pDb = NULL, AcDbHostApplicationServices::FindFileHint hint = kDefault);

  Acad::ErrorStatus getRoamableRootFolder(const ACHAR *& folder);
  Acad::ErrorStatus getLocalRootFolder(const ACHAR *& folder);

  virtual const ACHAR * companyName( void );
  virtual const ACHAR * product( void );
  virtual const ACHAR * versionString( void );
  virtual int releaseMajorVersion( void );
  virtual int releaseMinorVersion( void );
private:
  class StaticHost
  {
  public:
    StaticHost( void );
    ~StaticHost( void );
  private:
    AcDbHostApplicationServices * host;
  };
  static StaticHost Instance;
};

#endif
