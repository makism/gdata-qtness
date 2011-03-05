#ifndef DOCUMENTSLIST_H
#define DOCUMENTSLIST_H


#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QUrl>


class DocumentsList : public QObject
{
   Q_OBJECT

public:
    DocumentsList(QObject *parent = 0);

    void setAuthToken(const QString &);

	QString getServiceName(void) const;
    void listDocuments(void);

private slots:
    void readData(void);
    void readAuthDataError(QNetworkReply::NetworkError);

private:
    QNetworkRequest m_request;
    QNetworkAccessManager *m_manager;
    QNetworkReply *m_reply;
	QString m_serviceName;

    QString m_auth;
};

#endif
