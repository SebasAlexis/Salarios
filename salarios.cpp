#include "salarios.h"
#include "ui_salarios.h"


Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
    m_controlador=new Controlador();
}

Salarios::~Salarios()
{
    delete ui;
}


void Salarios::on_btnCalcular_clicked()
{
    //Obtener datos de la GUI
    QString nombre=ui->inNombre->text();
    int horas=ui->inHoras->value();
    TipoJornada jornada;
    if(ui->inMatutina->isChecked()){
        jornada=TipoJornada::Matutina;
    }else if(ui->inVespertina->isChecked()){
        jornada=TipoJornada::Vespertina;
    }else{
        jornada=TipoJornada::Nocturna;
    }
    //Validacion de Datos
    if(nombre==""||horas==0){
        QMessageBox::warning(this,"Advertencia","El nombre y/o el numero de horas es incorrecto");
        return;
    }
    //Establecer datos al controlador
    m_controlador->setDatos(nombre,horas,jornada);

    //Calcular Salarios
    if(m_controlador->calcular()){
        //Muestra Resultados
        ui->outCalculos->appendPlainText(m_controlador->getDatos());
    }else{
        QMessageBox::critical(
                    this,
                    "Error",
                    "No se puede calcular el salario.");
    }
    //Limpiar widgets
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();

    //Mostrar mensaje en la barra de estado
    ui->statusbar->showMessage("Salario de "+nombre+" calculado",5000);
}


