#ifndef SALARIOS_H
#define SALARIOS_H

#include "obrero.h"
#include "controlador.h"

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class Salarios; }
QT_END_NAMESPACE

class Salarios : public QMainWindow
{
    Q_OBJECT

public:
    Salarios(QWidget *parent = nullptr);
    ~Salarios();

private slots:
    void on_btnCalcular_clicked();

private:
    Ui::Salarios *ui;
    Controlador *m_controlador;
};
#endif // SALARIOS_H
