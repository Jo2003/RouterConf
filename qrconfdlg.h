#ifndef QRCONFDLG_H
#define QRCONFDLG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QMap>

namespace Ui {
class QRConfDlg;
}

class QRConfDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QRConfDlg(QWidget *parent = 0);
    ~QRConfDlg();

private slots:
    void initDlg();
    void replyMsg(QNetworkReply* reply);
    void authenticate(QNetworkReply* reply, QAuthenticator* authenticator);


    void on_pushSend_clicked();

private:
    Ui::QRConfDlg *ui;
    QNetworkAccessManager *m_pNw;
    QMap<QString, QString> routerMap;
};

#endif // QRCONFDLG_H
