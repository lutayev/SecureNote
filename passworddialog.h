#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QCryptographicHash>
#include <QVBoxLayout>
#include <QHBoxLayout>


class PasswordDialog : public QWidget
{
    Q_OBJECT
public:
    PasswordDialog(QWidget* parent = 0);

signals:
    void sendNewPassword(QByteArray);

private slots:
    void setNewPassword();

private:

    QVBoxLayout m_dialogLayout;
    QHBoxLayout m_buttonsLayout;
    QLineEdit m_passwordInput;
    QPushButton m_acceptBtn;
    QPushButton m_cancelBtn;

    QByteArray m_passwordHash;
};

#endif // PASSWORDDIALOG_H
