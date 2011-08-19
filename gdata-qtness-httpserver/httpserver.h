#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>


namespace GDataQtness {

class HttpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit HttpServer(quint16 port, QObject* parent = 0);
    explicit HttpServer(QHostAddress address, quint16 port, QObject* parent = 0);

    const QString getFullAddress() const;

    void incomingConnection(int socket);

signals:
//    void calledback(const QString &);
//    void callIgnored();

private slots:
    void readClient();
    void discardClient();

private:
    bool disabled;

};

}

#endif // SIMPLEHTTPSERVER_H
