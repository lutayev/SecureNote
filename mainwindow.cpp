#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    ui->textEdit->setText("Create new or open a document");
    ui->textEdit->setReadOnly(true);

    ui->actionEdit_text->setText("ENABLE EDIT");
    ui->actionEdit_text->setEnabled(false);
    enable_edit_actions(false);

    ui->actionEncrypt_all_text->setEnabled(false);
    ui->actionDecrypt_all_text->setEnabled(false);
    isEncrypted = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enable_edit_actions(bool isEnabled)
{
    ui->actionCut->setEnabled(isEnabled);
    ui->actionPaste->setEnabled(isEnabled);
    ui->actionRedo->setEnabled(isEnabled);
    ui->actionUndo->setEnabled(isEnabled);
}


void MainWindow::on_actionNew_triggered()
{
    mFileName = "";
    ui->textEdit->setPlainText("");
    ui->textEdit->setReadOnly(false);
    ui->actionEdit_text->setEnabled(false);

    ui->actionEdit_text->setText("DISABLE EDIT");
    ui->actionEdit_text->setEnabled(true);
    enable_edit_actions(true);

    ui->actionEncrypt_all_text->setEnabled(true);
    isEncrypted = false;
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
            ui->textEdit->setReadOnly(true);
            ui->actionEdit_text->setEnabled(true);

            ui->actionDecrypt_all_text->setEnabled(isEncrypted);
            ui->actionEncrypt_all_text->setEnabled(!isEncrypted);
        }
        sFile.close();
    }
}

void MainWindow::on_actionOpen_encrypted_triggered()
{
    isEncrypted = true;
    on_actionOpen_triggered();
}

void MainWindow::on_actionOpen_decrypted_triggered()
{
    isEncrypted = false;
    on_actionOpen_triggered();
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
    sFile.close();
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
   encodedData = QAESEncryption::Crypt(QAESEncryption::AES_128, QAESEncryption::ECB, ui->textEdit->toPlainText().toUtf8(), QByteArray("1104300711043007"));
   ui->textEdit->setText(QString(encodedData));
   qDebug() << "Encoded raw byteArray: " << encodedData;
   //qDebug() << "Qstring(encodedArray): " <<QString(encodedData);
   //qDebug() << "(QString::fromUtf8(encodedArray)).toUtf8(): " <<(QString::fromUtf8(encodedData)).toUtf8();
   fileData = encodedData;

   ui->actionDecrypt_all_text->setEnabled(true);
   ui->actionEncrypt_all_text->setEnabled(false);
   ui->actionEdit_text->setEnabled(false);
   ui->textEdit->setReadOnly(true);
}

void MainWindow::on_actionDecrypt_all_text_triggered()
{
    decodedData = QAESEncryption::Decrypt(QAESEncryption::AES_128, QAESEncryption::ECB, fileData, QByteArray("1104300711043007"));
    ui->textEdit->setText(QString::fromUtf8(decodedData));
    qDebug() << "Decoded text: " << QString::fromUtf8(decodedData);
    fileData = decodedData;

    ui->actionDecrypt_all_text->setEnabled(false);
    ui->actionEncrypt_all_text->setEnabled(true);
    ui->actionEdit_text->setEnabled(true);
    ui->textEdit->setReadOnly(false);
}

void MainWindow::on_actionSet_the_encryption_password_triggered()
{

}

void MainWindow::on_actionEdit_text_triggered()
{
    if (ui->textEdit->isReadOnly())
    {
        ui->textEdit->setReadOnly(false);
        ui->actionEdit_text->setText("DISABLE EDIT");
        enable_edit_actions(true);
    } else {
        ui->textEdit->setReadOnly(true);
        ui->actionEdit_text->setText("ENABLE EDIT");
        enable_edit_actions(false);
    }
}
