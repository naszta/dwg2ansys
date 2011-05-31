#ifndef MainDialogH
#define MainDialogH 1

#include <QDialog>

#include "ui_MainDialog.h"

class QSettings;

class MainDialog : public QDialog
{
  Q_OBJECT
public:
  MainDialog( QWidget * parent = 0, Qt::WindowFlags flags = 0 );
  virtual ~MainDialog( void );
protected slots:
  virtual void pushFrom( void );
  virtual void pushTo( void );
  virtual void MakeConvert( void );
private:
  Ui::MainDialog ui;
  QSettings * sets;
};

#endif
