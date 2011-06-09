#include "MainDialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QString>

#include "Convert.h"

MainDialog::MainDialog( QWidget * parent, Qt::WindowFlags flags )
: QDialog(parent,flags), sets( new QSettings )
{
  ui.setupUi(this);
  connect( ui.pushFrom, SIGNAL(clicked()), this, SLOT(pushFrom()) );
  connect( ui.pushTo, SIGNAL(clicked()), this, SLOT(pushTo()) );
  connect( this, SIGNAL(accepted()), this, SLOT(MakeConvert()) );

  this->restoreGeometry( this->sets->value( "MainDialog/Geometry", this->saveGeometry() ).toByteArray() );
  ui.lineFrom->setText( this->sets->value( "MainDialog/FromFile" ).toString() );
  ui.lineTo->setText( this->sets->value( "MainDialog/ToFile" ).toString() );
}

MainDialog::~MainDialog( void )
{
  if ( this->sets != 0 )
  {
    this->sets->setValue( "MainDialog/Geometry", this->saveGeometry() );
    this->sets->setValue( "MainDialog/FromFile", ui.lineFrom->text() );
    this->sets->setValue( "MainDialog/ToFile", ui.lineTo->text() );

    delete this->sets;
    this->sets = 0;
  }
}

void MainDialog::pushFrom( void )
{
  QString filename = QFileDialog::getOpenFileName( this, "Give DWG or DXF file source...", QDir::currentPath(), "AutoCAD files (*.dwg *.dxf);;All files (*)" );
  if ( filename.isEmpty() )
    return;
  ui.lineFrom->setText( filename );
}

void MainDialog::pushTo( void )
{
  QString filename = QFileDialog::getSaveFileName( this, "Give DAT or INP file target...", QDir::currentPath(), "ANSYS files (*.dat);;ANSYS files (*.inp);;All files (*)" );
  if ( filename.isEmpty() )
    return;
  ui.lineTo->setText( filename );
}

void MainDialog::MakeConvert( void )
{
  if ( ui.lineFrom->text().isEmpty() || ui.lineTo->text().isEmpty() )
  {
    QMessageBox::information( this, "Warning!", "Some of the file names are missing!" );
    return;
  }

  QString sfilename = ui.lineFrom->text();
  QString tfilename = ui.lineTo->text();

  if ( ! Convert::dwg_to_ansys( (wchar_t *) sfilename.utf16(), (wchar_t *) tfilename.utf16() ) )
  {
    QMessageBox::information( this, "Warning!", ui.lineFrom->text() + QString(" cannot be converted to ") + ui.lineTo->text() + QString("!"));
  }
}
