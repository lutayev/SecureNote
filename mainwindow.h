#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QTextEdit>
#include <QFileDialog>
#include <QLineEdit>
#include "qaesencryption.h"
#include "passworddialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void passwordChanged(QByteArray passwordHash);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTextEdit* mTextEdit;

private slots:
    void on_actionRedo_triggered();

    void on_actionSave_as_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionEncrypt_all_text_triggered();

    void on_actionDecrypt_all_text_triggered();

    void on_actionSet_the_encryption_password_triggered();

    void on_actionEdit_text_triggered();

    void on_actionOpen_encrypted_triggered();

    void on_actionOpen_decrypted_triggered();

    void on_actionExpert_mode_triggered(bool checked);

private:
    void setEditActionsActive(bool isEnabled);
    void updBtnStatusEncrypted();

    Ui::MainWindow *ui;

    QLineEdit m_lineEdit;
    QString m_fileName;
    QByteArray tempData;
    QByteArray encodedData;
    QByteArray decodedData;
    QByteArray fileData;
    QByteArray m_passwordHash;
    PasswordDialog* m_passwordDialog;

    bool isEncrypted;
    bool isExpertMode;
};

#endif // MAINWINDOW_H
