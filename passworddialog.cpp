#include "passworddialog.h"
#include "mainwindow.h"

PasswordDialog::PasswordDialog(QWidget* parent) : QDialog(parent)
{
    setLayout(&m_dialogLayout);
    m_dialogLayout.addWidget(&m_passwordInput);
    m_dialogLayout.addLayout(&m_buttonsLayout);
    m_buttonsLayout.addWidget(&m_acceptBtn);
    m_buttonsLayout.addWidget(&m_cancelBtn);

    m_passwordInput.setEchoMode(QLineEdit::Password);

    m_acceptBtn.setText("Accept");
    m_cancelBtn.setText("Cancel");

    QObject::connect(&m_acceptBtn, SIGNAL(clicked()), this, SLOT(setNewPassword()));
    QObject::connect(&m_cancelBtn, SIGNAL(clicked()), this, SLOT(close()));

    QObject::connect(this, SIGNAL(sendNewPassword(QByteArray)), parent, SLOT(passwordChanged(QByteArray)));
}

void PasswordDialog::setNewPassword()
{
    m_passwordHash = QCryptographicHash::hash(m_passwordInput.text().toUtf8(), QCryptographicHash::Md5);
    emit sendNewPassword(m_passwordHash);
    close();
}
