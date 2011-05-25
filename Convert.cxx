#include "Convert.h"

#include "dbmain.h"
#include "dbapserv.h"
#include "dbsymtb.h"

#include "Serialize.h"

#include "dwg2ansysVersion.h"

bool Convert::dwg_to_ansys( const wchar_t * source_name, std::ostream &os )
{
  AcDbDatabase * database = new AcDbDatabase(false);
  if ( database->readDwgFile( source_name ) != Acad::eOk )
    return false;
  acdbHostApplicationServices()->setWorkingDatabase( database );

  AcDbBlockTable * block_table = 0;
  AcDbBlockTableRecord * block_table_record = 0;
  AcDbBlockTableRecordIterator * pRecordIter = 0;
  AcDbEntity * pEntity = 0;

  if ( database->getSymbolTable( block_table, AcDb::kForRead ) != Acad::eOk )
  {
    acdbHostApplicationServices()->setWorkingDatabase(0);
    delete database;
    return false;
  }

  if ( block_table->getAt( ACDB_MODEL_SPACE, block_table_record, AcDb::kForRead ) != Acad::eOk )
  {
    block_table->close();
    acdbHostApplicationServices()->setWorkingDatabase(0);
    delete database;
    return false;
  }

  if ( block_table_record->newIterator( pRecordIter ) != Acad::eOk )
  {
    block_table_record->close();
    block_table->close();
    acdbHostApplicationServices()->setWorkingDatabase(0);
    delete database;
    return false;
  }

  os << "! This geometry was written by dwg2ansys, (c) Nasztanovics Ferenc\n";
  os << "! Version: " << dwg2ansys_VERSION << "\n!\n";

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

  delete pRecordIter;
  block_table_record->close();
  block_table->close();
  acdbHostApplicationServices()->setWorkingDatabase(0);
  delete database;
  return true;
}
