#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QTcpServer>
#include <QJsonObject>
#include <QTcpSocket>
class backEnd : public QObject
{
    Q_OBJECT
public:
    explicit backEnd(QObject *parent = 0);

signals:
  void incomingPicture(QJsonObject obj);
public slots:
    void newConnection();
    void readyRead();
    void onDisConnection();
private:
    QTcpServer *tcp_server;
};

#endif // BACKEND_H
