#include "backend.h"
#include <QDebug>
#include <QJsonDocument>
backEnd::backEnd(QObject *parent) : QObject(parent),tcp_server(new QTcpServer(this))
{
  if(!tcp_server->listen(QHostAddress::Any,11111)){
      qDebug()<< "error tcp server listen.";
      tcp_server->close();
    }

  connect(tcp_server,SIGNAL(newConnection()),SLOT(newConnection()));
}

void backEnd::newConnection()
{
  QTcpSocket *newpeer = tcp_server->nextPendingConnection();
  connect(newpeer,SIGNAL(readyRead()),SLOT(readyRead()));
  connect(newpeer,SIGNAL(disconnected()),newpeer,SLOT(deleteLater()));
  connect(newpeer,SIGNAL(disconnected()),SLOT(onDisConnection()));

  QByteArray hello("hello,this is wayne");
  newpeer->write(hello);
//  newpeer->disconnectFromHost();
}

void backEnd::readyRead()
{
  QTcpSocket *peer = qobject_cast<QTcpSocket*>(sender());
  if(peer){
      QByteArray reply= peer->readAll();
      qDebug()<< __FUNCTION__<<peer<<","<< reply;

      QJsonDocument doc = QJsonDocument::fromJson(reply);
      if(!doc.isNull()){
          emit incomingPicture(doc.object());
        }
    }
}

void backEnd::onDisConnection()
{
  QTcpSocket *peer = qobject_cast<QTcpSocket*>(sender());
  qDebug()<< __FUNCTION__<<peer<<" disconnected.";
}
