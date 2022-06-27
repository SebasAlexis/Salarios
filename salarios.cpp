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
    calcular();
}

void Salarios::on_actionNuevo_triggered()
{

    //Limpiar widgets
    limpiar();
    //Limpiar el texto de los calculos
    ui->outCalculos->clear();
    ui->statusbar->showMessage("Nuevo Archivo",5000);
}

void Salarios::limpiar()
{
    //Limpiar widgets
    ui->inNombre->setText("");
    ui->inHoras->setValue(0);
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();
}

void Salarios::calcular()
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

    limpiar();
    //Mostrar mensaje en la barra de estado
    ui->statusbar->showMessage("Salario de "+nombre+" calculado",5000);
}


void Salarios::on_actionCalcular_triggered()
{
    calcular();
}


void Salarios::on_actionSalir_2_triggered()
{
    this->close();
}


void Salarios::on_actionGuardar_triggered()
{
    //Abrir cuadro de dialogo
    QString nombreArchivo=QFileDialog::getSaveFileName(this,
                                                       "Guardar calculos de salario",
                                                       QDir::home().absolutePath()+"/salario.txt",
                                                       "Archivos de texto (.txt)");
    //Crear un objeto File
    QFile archivo(nombreArchivo);
    //Abrir para escritura
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        //crear un objeto stream de texto
        QTextStream salida(&archivo);
        //enviar los datos del resultado a la salida
        salida<<ui->outCalculos->toPlainText();
        //Mostrar mensajes en barra de estado
        ui->statusbar->showMessage("Datos Guardados en: "+nombreArchivo,5000);
        //cerrar el archivo
        archivo.close();

    }else{
        //Mensaje de error
        QMessageBox::warning(this,
                             "Guardar Archivo",
                             "No se puede acceder al archivo para guardar los datos");
    }
}


void Salarios::on_actionAcerca_de_triggered()
{
    // Crear un objeto del cuadro de diálogo
    Acerca *dialog = new Acerca(this);
    // Enviar datos a la otra ventana
    dialog->setVersion(VERSION);
    // Mostrar la venta en modo MODAL
    dialog->exec();
    // Luego de cerrar la ventana, se acceden a los datos de la misma
    qDebug() << dialog->valor();
}

