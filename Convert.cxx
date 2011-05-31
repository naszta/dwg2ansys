#include "Convert.h"

#include "dbmain.h"
#include "dbapserv.h"
#include "dbsymtb.h"

#include "Serialize.h"
#include "Model.h"

#include "dwg2ansysVersion.h"

void close_everything( AcDbDatabase * &database, AcDbBlockTable * &block_table, AcDbBlockTableRecord * &block_table_record, AcDbBlockTableRecordIterator * &pRecordIter )
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
}

bool Convert::dwg_to_ansys( const wchar_t * source_name, std::ostream &os )
{
  size_t length = wcslen( source_name );
  
  if ( length < 5 )
    return false;

  AcDbDatabase * database = new AcDbDatabase(false);
  if ( wcscmp( L".dwg", source_name + length - 4 ) == 0 )
  {
    if ( database->readDwgFile( source_name ) != Acad::eOk )
    {
      delete database;
      return false;
    }
  }
  else if ( wcscmp( L".dxf", source_name + length - 4 ) == 0 )
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

  AcDbBlockTable * block_table = 0;
  AcDbBlockTableRecord * block_table_record = 0;
  AcDbBlockTableRecordIterator * pRecordIter = 0;
  AcDbEntity * pEntity = 0;

  if ( database->getSymbolTable( block_table, AcDb::kForRead ) != Acad::eOk )
  {
    close_everything( database, block_table, block_table_record, pRecordIter );
    return false;
  }

  if ( block_table->getAt( ACDB_MODEL_SPACE, block_table_record, AcDb::kForRead ) != Acad::eOk )
  {
    close_everything( database, block_table, block_table_record, pRecordIter );
    return false;
  }

  if ( block_table_record->newIterator( pRecordIter ) != Acad::eOk )
  {
    close_everything( database, block_table, block_table_record, pRecordIter );
    return false;
  }

  os << "! This geometry was written by dwg2ansys, (c) Nasztanovics Ferenc\n";
  os << "! Version: " << dwg2ansys_VERSION << "\n";
  os << "/PREP7\n";
  os << "!\n";

  while ( ! pRecordIter->done() )
  {
    if (pRecordIter->getEntity( pEntity, AcDb::kForRead ) != Acad::eOk )
    {
      pRecordIter->step();
      continue;
    }

    os << pEntity;

    pEntity->close();
    pRecordIter->step();
  }

  os << "!\n";
  os << "! Number of points: " << Model::CurrentModel.NumOfPoints << "\n";
  os << "! Number of lines : " << Model::CurrentModel.NumOfLines << "\n";
  os << "!\n";

  close_everything( database, block_table, block_table_record, pRecordIter );
  return true;
}
