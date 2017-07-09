#include "backend.h"
#include <QDebug>
#include <QJsonDocument>

#define SOCKET_ADDR "tcp://127.0.0.1:11111"

backEnd::backEnd(QObject *parent) : QObject(parent),init_flag(-1),keep_running(true)
{
  int to = 100;
  sock = nn_socket(AF_SP, NN_PAIR);
  if(sock>=0 && nn_bind (sock, SOCKET_ADDR)>=0 &&
     nn_setsockopt (sock, NN_SOL_SOCKET, NN_RCVTIMEO, &to, sizeof (to)) >= 0){
      init_flag = 0;
    } else {
      init_flag =1;
    }
}

backEnd::~backEnd()
{
  nn_shutdown (sock, 0);
}

void backEnd::run()
{
  if(init_flag) return;

  while(keep_running)
    {
      ///////////////////////////////////////////
      char *buf = NULL;
      int result = nn_recv(sock, &buf, NN_MSG, 0);
      if (result > 0)
        {
          qDebug() <<QString("got : [%1]:[%2]").arg(buf).arg(result);
          QJsonDocument doc = QJsonDocument::fromJson(QByteArray(buf));
          if(!doc.isNull()){
              emit incomingPicture(doc.object());
            }

          nn_freemsg(buf);
        }
//      sleep(1);
//      ///////////////////////////////////////////
      char to[]="I got it";
      size_t sz_n = strlen(to) + 1;
      int ans = nn_send(sock, to, sz_n, 0);
      if(ans>0){
          qDebug() <<QString("sent: [%1]:[%2]").arg(to).arg(sz_n);
        }
    }
  emit stopped();
}

void backEnd::stop()
{
  keep_running = false;
}

