#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QTextEdit>
#include <QFileDialog>
#include "qaesencryption.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QTextEdit* mTextEdit;
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
    QString mFileName;
    QByteArray tempData;
    QByteArray encodedData;
    QByteArray decodedData;
    QByteArray fileData;
    bool isEncoded;
};

#endif // MAINWINDOW_H
