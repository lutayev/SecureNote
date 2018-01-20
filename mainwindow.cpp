#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_version = "0.10";
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    isEncrypted = false;
    isExpertMode = false;

    ui->textEdit->setText("Create new or open a document");

    ui->actionEdit_text->setCheckable(true);
    ui->actionEdit_text->setChecked(false);
    ui->actionEdit_text->setEnabled(false);
    on_actionEdit_text_triggered();

    ui->actionEncrypt_all_text->setEnabled(false);
    ui->actionDecrypt_all_text->setEnabled(false);

    ui->actionExpert_mode->setCheckable(true);

    QFile sFile("data.dat");
    if (!sFile.exists())
    {
        m_passwordHash = QCryptographicHash::hash(QString("1111111111111111").toUtf8(), QCryptographicHash::Md5);
    }
    else
    {
        if (sFile.open(QFile::ReadOnly))
        {
            m_passwordHash = sFile.readAll();
        }
    }

    m_fileName = "NewFile.txt";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    m_fileName = "";
    ui->textEdit->setPlainText("");
    ui->actionEdit_text->setChecked(true);
    ui->actionEdit_text->setEnabled(true);
    m_fileName = "NewFile.txt";
    isEncrypted = false;

    setWindowTitle(m_fileName);
    on_actionEdit_text_triggered();
    updBtnStatusEncrypted();
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Open a file");

    if(!file.isEmpty())
    {
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly))
        {
            m_fileName = file;
            fileData = sFile.readAll();
            qDebug() << "Raw read from file: " << fileData;
            sFile.close();
            ui->textEdit->setPlainText(QString::fromUtf8(fileData));
        }
        sFile.close();
    }

    setWindowTitle(m_fileName);
    on_actionEdit_text_triggered();
    updBtnStatusEncrypted();
}

void MainWindow::on_actionOpen_encrypted_triggered()
{
    isEncrypted = true;
    ui->actionEdit_text->setChecked(false);
    on_actionOpen_triggered();
}

void MainWindow::on_actionOpen_decrypted_triggered()
{
    isEncrypted = false;
    on_actionOpen_triggered();
}

void MainWindow::on_actionSave_triggered()
{
    //get text from UI
    fileData = ui->textEdit->toPlainText().toUtf8();

    //save data to file
    QFile sFile(m_fileName);
    if(sFile.open(QFile::WriteOnly))
    {
       sFile.write(fileData);
       sFile.flush();
       sFile.close();
    }
    qDebug() << "Raw wrote to file: " << fileData;

    setWindowTitle(m_fileName);
}

void MainWindow::on_actionSave_as_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Save a file");

    if(!file.isEmpty())
    {
        m_fileName = file;
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionEncrypt_all_text_triggered()
{
   encodedData = QAESEncryption::Crypt(QAESEncryption::AES_128, QAESEncryption::ECB, ui->textEdit->toPlainText().toUtf8(), QByteArray(m_passwordHash));
   ui->textEdit->setText(encodedData.toBase64());
   qDebug() << "Encoded HEX byteArray: " << encodedData.toBase64();

   fileData = encodedData.toBase64();
   isEncrypted = true;

   on_actionEdit_text_triggered();
   updBtnStatusEncrypted();
}

void MainWindow::on_actionDecrypt_all_text_triggered()
{
    decodedData = QAESEncryption::Decrypt(QAESEncryption::AES_128, QAESEncryption::ECB, QByteArray::fromBase64(ui->textEdit->toPlainText().toUtf8()), QByteArray(m_passwordHash));
    qDebug() << "Read from UI: " << ui->textEdit->toPlainText().toUtf8();
    ui->textEdit->setText(decodedData);
    qDebug() << "Decoded text: " << QString::fromUtf8(decodedData);


    fileData = decodedData;
    isEncrypted = false;

    on_actionEdit_text_triggered();
    updBtnStatusEncrypted();
}

void MainWindow::on_actionSet_the_encryption_password_triggered()
{

//    QByteArray pwd_hash = QCryptographicHash::hash("11111", QCryptographicHash::Md5);
//    qDebug() << "Password hash: " << pwd_hash;
    m_passwordDialog = new PasswordDialog(this);
    m_passwordDialog->exec();
    delete m_passwordDialog;
}

void MainWindow::on_actionEdit_text_triggered()
{
    ui->actionEdit_text->setEnabled(!isEncrypted || isExpertMode);
    ui->textEdit->setReadOnly(!(ui->actionEdit_text->isChecked() || isExpertMode));
    setEditActionsActive(ui->actionEdit_text->isChecked() || isExpertMode);
}

void MainWindow::on_actionExpert_mode_triggered(bool checked)
{
    isExpertMode = checked;
    ui->actionEdit_text->setChecked(checked);
    updBtnStatusEncrypted();
    on_actionEdit_text_triggered();
}

void MainWindow::updBtnStatusEncrypted()
{
    ui->actionEncrypt_all_text->setEnabled(!isEncrypted || isExpertMode);
    ui->actionDecrypt_all_text->setEnabled(isEncrypted || isExpertMode);
}

void MainWindow::setEditActionsActive(bool isEnabled)
{
    ui->actionCut->setEnabled(isEnabled);
    ui->actionPaste->setEnabled(isEnabled);
    ui->actionRedo->setEnabled(isEnabled);
    ui->actionUndo->setEnabled(isEnabled);
}

void MainWindow::passwordChanged(QByteArray passwordHash)
{
    QFile sFile("data.dat");
    if(sFile.open(QFile::WriteOnly))
    {
       sFile.write(passwordHash);
       sFile.flush();
       sFile.close();
    }
    m_passwordHash = passwordHash;
    qDebug() << "Get message from dialog: " << passwordHash;
    qDebug() << "Password in hex: " << passwordHash.toHex();
    qDebug() << "Wrote password to data.dat: " << m_passwordHash;
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

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About Secure Note program", "This is the program for encrypting/decrypting text data.\n"
                                                          "Author: Ivan Lutayev\n"
                                                          "Email: i.lutayev@gmail.com\n"
                                                          "Version: " + m_version);
}
