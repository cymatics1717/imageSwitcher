#include "backend.h"
#include <QDateTime>
#include <QDebug>
#include <QJsonDocument>
#include <QTcpSocket>
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

  qDebug() << newpeer->peerAddress() <<":" << newpeer->peerPort()<< newpeer->peerName();
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
      peer->write(QString("backEnd::%1:%2").arg(__FUNCTION__)
                  .arg(QDateTime::currentDateTime().toString(Qt::ISODateWithMs)).toUtf8());
    }
}

void backEnd::onDisConnection()
{
  QTcpSocket *peer = qobject_cast<QTcpSocket*>(sender());
  if(peer){
      qDebug()<< __FUNCTION__<<peer->peerAddress()<<peer->peerPort()<<" disconnected.";
  }
}
