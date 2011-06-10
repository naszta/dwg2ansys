#include "Convert.h"

#include "dbmain.h"
#include "dbapserv.h"
#include "dbsymtb.h"

#include "GeomDB.h"
#include "Serialize.h"
#include <fstream>

#include "dwg2ansysVersion.h"

void close_everything( AcDbDatabase * &database, AcDbBlockTable * &block_table, AcDbBlockTableRecord * &block_table_record, AcDbBlockTableRecordIterator * &pRecordIter, GeomDB * &target )
{
  if ( pRecordIter != 0 )
  {
    delete pRecordIter;
    pRecordIter = 0;
  }
  if ( block_table_record != 0 )
  {
    block_table_record->close();
    block_table_record = 0;
  }
  if ( block_table != 0 )
  {
    block_table->close();
    block_table = 0;
  }
  if ( database != 0 )
  {
    acdbHostApplicationServices()->setWorkingDatabase(0);
    delete database;
    database = 0;
  }
  if ( target != 0 )
  {
    delete target;
    target = 0;
  }
}

bool Convert::dwg_to_ansys( const wchar_t * source_name, const wchar_t * target_name )
{
  size_t source_length = wcslen( source_name );
  
  if ( source_length < 5 )
    return false;

  AcDbDatabase * database = new AcDbDatabase(false);
  if ( wcscmp( L".dwg", source_name + source_length - 4 ) == 0 )
  {
    if ( database->readDwgFile( source_name ) != Acad::eOk )
    {
      delete database;
      return false;
    }
  }
  else if ( wcscmp( L".dxf", source_name + source_length - 4 ) == 0 )
  {
    if ( database->dxfIn( source_name ) != Acad::eOk )
    {
      delete database;
      return false;
    }
  }
  else
  {
    delete database;
    return false;
  }
  acdbHostApplicationServices()->setWorkingDatabase( database );

  GeomDB * targetDB = new GeomDB;

  AcDbBlockTable * block_table = 0;
  AcDbBlockTableRecord * block_table_record = 0;
  AcDbBlockTableRecordIterator * pRecordIter = 0;
  AcDbEntity * pEntity = 0;

  if ( database->getSymbolTable( block_table, AcDb::kForRead ) != Acad::eOk )
  {
    close_everything( database, block_table, block_table_record, pRecordIter, targetDB );
    return false;
  }

  if ( block_table->getAt( ACDB_MODEL_SPACE, block_table_record, AcDb::kForRead ) != Acad::eOk )
  {
    close_everything( database, block_table, block_table_record, pRecordIter, targetDB );
    return false;
  }

  if ( block_table_record->newIterator( pRecordIter ) != Acad::eOk )
  {
    close_everything( database, block_table, block_table_record, pRecordIter, targetDB );
    return false;
  }

  while ( ! pRecordIter->done() )
  {
    if (pRecordIter->getEntity( pEntity, AcDb::kForRead ) != Acad::eOk )
    {
      pRecordIter->step();
      continue;
    }

    targetDB->AddEntity( pEntity );

    pEntity->close();
    pRecordIter->step();
  }

  std::ofstream file( target_name, std::ios_base::out | std::ios_base::trunc );
  if ( ! file.is_open() )
  {
    close_everything( database, block_table, block_table_record, pRecordIter, targetDB );
    return true;
  }
  file << Serialize( targetDB );
  file.flush();
  file.close();

  close_everything( database, block_table, block_table_record, pRecordIter, targetDB );
  return true;
}
