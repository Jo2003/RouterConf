#include "qrconfdlg.h"
#include "ui_qrconfdlg.h"
#include <QTimer>
#include <QMessageBox>
#include <QByteArray>

QRConfDlg::QRConfDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRConfDlg)
{
    ui->setupUi(this);
    m_pNw = NULL;

    routerMap["NETGEAR"]   = "Netgear Router"    ;
    routerMap["Broadband"] = "Broadband Router"  ;
    routerMap["MVOE"]      = "Pseudo Router MVOE";

    QTimer::singleShot(250, this, SLOT(initDlg()));
}

QRConfDlg::~QRConfDlg()
{
    delete ui;
    if (m_pNw)
    {
        delete (m_pNw);
    }
}

void QRConfDlg::initDlg()
{
    m_pNw = new QNetworkAccessManager(this);

    if (m_pNw)
    {
        connect (m_pNw, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyMsg(QNetworkReply*)));
        connect (m_pNw, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(authenticate(QNetworkReply*,QAuthenticator*)));
    }
}

void QRConfDlg::replyMsg(QNetworkReply *reply)
{
    QString s = QString("%1():%2\n").arg(__FUNCTION__).arg(__LINE__);

    foreach (QByteArray ba, reply->rawHeaderList())
    {
        s += QString("%1: %2\n").arg(QString(ba)).arg(QString(reply->rawHeader(ba)));
    }

    ui->textBrowser->append(s);
    reply->deleteLater();
}

void QRConfDlg::authenticate(QNetworkReply *reply, QAuthenticator *authenticator)
{
    QString s = QString("%1():%2\n").arg(__FUNCTION__).arg(__LINE__);

    foreach (QByteArray ba, reply->rawHeaderList())
    {
        s += QString("%1: %2\n").arg(QString(ba)).arg(QString(reply->rawHeader(ba)));
    }

    s += QString("Realm: %1\n").arg(authenticator->realm());

    ui->textBrowser->append(s);

    if ((ui->lineUser->text() != "") && (ui->linePass->text() != ""))
    {
        authenticator->setUser(ui->lineUser->text());
        authenticator->setPassword(ui->linePass->text());
    }

    reply->deleteLater();

    if (authenticator->realm() != "")
    {
        foreach (QString key, routerMap.keys())
        {
            if (authenticator->realm().contains(key))
            {
                QMessageBox::information (this, "Hurray", tr("We've found a %1").arg(routerMap[key]));
            }
        }
    }
}

void QRConfDlg::on_pushSend_clicked()
{
    if (ui->lineEdit->text() != "http://")
    {
        m_pNw->get(QNetworkRequest(QUrl(ui->lineEdit->text())));
    }
}
