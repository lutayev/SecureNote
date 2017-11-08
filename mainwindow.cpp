#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    ui->textEdit->setText("Some test text");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionNew_triggered()
{
    mFileName = "";
    ui->textEdit->setPlainText("");
    //ui->textEdit->selectAll();
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Open a file");

    if(!file.isEmpty())
    {
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly))
        {
            mFileName = file;
            fileData = sFile.readAll();
            sFile.close();
            ui->textEdit->setPlainText(QString::fromUtf8(fileData));
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    QFile sFile(mFileName);
    if(sFile.open(QFile::WriteOnly))
    {
       sFile.write(fileData);

       sFile.flush();
       sFile.close();
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Save a file");

    if(!file.isEmpty())
    {
        mFileName = file;
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionEncrypt_all_text_triggered()
{
   encodedData = QAESEncryption::Crypt(QAESEncryption::AES_128, QAESEncryption::ECB, ui->textEdit->toPlainText().toUtf8(), QByteArray("1111111111111111"));
   ui->textEdit->setText(QString(encodedData));
   qDebug() << "Encoded raw byteArray: " << encodedData;
   //qDebug() << "Qstring(encodedArray): " <<QString(encodedData);
   //qDebug() << "(QString::fromUtf8(encodedArray)).toUtf8(): " <<(QString::fromUtf8(encodedData)).toUtf8();
   fileData = encodedData;
}

void MainWindow::on_actionDecrypt_all_text_triggered()
{
    decodedData = QAESEncryption::Decrypt(QAESEncryption::AES_128, QAESEncryption::ECB, fileData, QByteArray("1111111111111111"));
    ui->textEdit->setText(QString::fromUtf8(decodedData));
    qDebug() << "Decoded text: " << QString::fromUtf8(decodedData);
    fileData = decodedData;
}

void MainWindow::on_actionSet_the_encryption_password_triggered()
{

}
