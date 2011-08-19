#include "httpserver.h"

namespace GDataQtness {

HttpServer::HttpServer(quint16 port, QObject* parent)
    : QTcpServer(parent),
      disabled(false)
{
    listen(QHostAddress::Any, port);
}

HttpServer::HttpServer(QHostAddress address, quint16 port, QObject* parent)
    : QTcpServer(parent),
      disabled(false)
{
    listen(address, port);
}

void HttpServer::incomingConnection(int socket)
{
    if (disabled)
        return;

    QTcpSocket * s = new QTcpSocket(this);
    connect(s, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(s, SIGNAL(disconnected()), this, SLOT(discardClient()));
    s->setSocketDescriptor(socket);
}

void HttpServer::readClient()
{
    if(disabled)
        return;

    QTcpSocket* socket = (QTcpSocket*)sender();

    if(socket->canReadLine()) {
        QTextStream os(socket);
        os.setAutoDetectUnicode(true);

        os << "HTTP/1.0 200 Ok\r\n"
              "Content-Type: text/html; charset=\"utf-8\"\r\n";

        QString line = os.readLine(256);
        QString qdata = line.mid(line.indexOf('?') + 1);
        qDebug() << qdata;

        socket->close();

        if (socket->state() == QTcpSocket::UnconnectedState)
            delete socket;
    }
}

void HttpServer::discardClient()
{
    QTcpSocket* socket = (QTcpSocket*)sender();
    socket->deleteLater();
}

const QString HttpServer::getFullAddress() const
{
    return "http://" + serverAddress().toString() + ":" + QString::number(serverPort());
}

}
