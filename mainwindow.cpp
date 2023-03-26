#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
   QString fileName = QFileDialog::getSaveFileName(this, "Save as");
   QFile file(fileName);
   if(!file.open(QFile::WriteOnly | QFile::Text)){
       QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
       return;
   }
   currentFile = fileName;
   setWindowTitle(fileName);
   QTextStream out(&file);
   QString text = ui->textEdit->toPlainText();
   out << text;
   file.close();
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer .setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot Access printer");
        return;
    }

    ui->textEdit->print(&printer);

  }

