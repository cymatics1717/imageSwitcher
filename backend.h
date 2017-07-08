#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QJsonObject>

extern "C"{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <nanomsg/nn.h>
#include <nanomsg/pair.h>

}

class backEnd : public QObject
{
    Q_OBJECT
public:
    explicit backEnd(QObject *parent = 0);
    ~backEnd();
signals:
  void incomingPicture(QJsonObject obj);
  void stopped();
public slots:
  void run();
  void stop();

private:
  int sock;
  int init_flag;
  bool keep_running;
};

#endif // BACKEND_H
