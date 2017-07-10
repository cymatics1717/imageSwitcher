#include "imageview.h"
#include <QGLWidget>
#include <QPropertyAnimation>
#include <QDebug>
#include <QThread>
//#include <QtMath>
#define m 400
imageView::imageView(QWidget *parent): QGraphicsView(nullptr,parent),selected(nullptr),
    scene(new QGraphicsScene(0,0,m,m,this)),manager(new QNetworkAccessManager(this))
{
  setGeometry(200,200,800,600);

  setScene(scene);
//  setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
//  setBackgroundBrush(QBrush(QPixmap("/usr/share/backgrounds/warty-final-ubuntu.png").scaledToHeight(m)));
  setBackgroundBrush(QBrush(QColor(0,74,128,240)));
  QFont ft;
  ft.setPointSize(40);
  info = scene->addText("hi,This is wayne",ft);
  info->setDefaultTextColor(Qt::white);
  info->setPos(0,m/2);
  info->setZValue(1);

  server = new backEnd;
  QThread *worker = new QThread;
  server->moveToThread(worker);

  connect(worker, SIGNAL(started()), server, SLOT(run()));
  connect(server,SIGNAL(incomingPicture(QJsonObject)),SLOT(incomingImage(QJsonObject)));
  connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));

  connect(manager, SIGNAL(finished(QNetworkReply*)),SLOT(replyFinished(QNetworkReply*)));

  {
    QJsonObject obj;
    obj.insert("url","/usr/share/backgrounds/Cielo_estrellado_by_Eduardo_Diez_Viñuela.jpg");
    obj.insert("desc","Cielo_estrellado_by_Eduardo_Diez_Viñuela");
    incomingImage(obj);
  }
  {
    QJsonObject obj;
    obj.insert("url","/usr/share/backgrounds/Flora_by_Marek_Koteluk.jpg");
    obj.insert("desc","Flora_by_Marek_Koteluk");
    incomingImage(obj);
  }
  worker->start();

}

void imageView::incomingImage(QJsonObject obj)
{
  if(!obj.isEmpty()&&obj.contains("url")&&obj.contains("desc")){
      QString url = obj.value("url").toString();
      QString desc = obj.value("desc").toString();
      qDebug() <<QUrl(url).scheme();
      if(QUrl(url).scheme()=="http"){
          QNetworkRequest req(url);
          QNetworkReply *reply = manager->get(req);
          lookup.insert(reply,desc);
        } else {
          startup(QPixmap(url),desc);
        }
    }
}

void imageView::fadingAway()
{
  QPropertyAnimation* ani= qobject_cast<QPropertyAnimation*>(sender());
  imageItem *itm = qobject_cast<imageItem*>(ani->targetObject());

  QPropertyAnimation *fadeout = new QPropertyAnimation(itm,"pos");
  connect(fadeout,SIGNAL(finished()),itm,SLOT(deleteLater()));
  fadeout->setDuration(3000);
  fadeout->setStartValue(itm->pos());
  fadeout->setEndValue(itm->pos()+QPoint(2*m,0));
  fadeout->start(QAbstractAnimation::DeleteWhenStopped);
}

void imageView::animate(imageItem *item)
{
//    qDebug()<<sceneRect();
    QPropertyAnimation *ani = new QPropertyAnimation(item,"pos");
    connect(ani,SIGNAL(finished()),this,SLOT(fadingAway()));
    ani->setDuration(3000);
    ani->setStartValue(QPoint(-m,m));
    ani->setEndValue(QPoint(-m/3,-m/3));
    ani->setEasingCurve(QEasingCurve::OutElastic);
    ani->start(QAbstractAnimation::DeleteWhenStopped);
}

void imageView::keyPressEvent(QKeyEvent *e)
{
  qDebug() <<e->text();
  switch (e->key()) {
    case Qt::Key_F:
      {
        static bool tag = false;
        tag = !tag;
        if(tag){
            showFullScreen();
          } else {
            showNormal();
          }
      }
      break;
    case Qt::Key_Q:
      {
        close();
      }
      break;
    }
}

void imageView::mouseMoveEvent(QMouseEvent *e)
{
//  qDebug()<< e->pos() <<items(e->pos());
//  info->setHtml(QString("pos:(%1,%2)").arg(e->pos().x()).arg(e->pos().y()));
//  imageItem *item = qgraphicsitem_cast<imageItem*>(itemAt(e->pos()));
//  if(item){
//      info->setHtml(buff.value(item).value("desc").toString());
//    }
}

void imageView::mousePressEvent(QMouseEvent *e)
{
//  qDebug()<< e->pos() <<itemAt(e->pos());
  selected = qgraphicsitem_cast<imageItem*>(itemAt(e->pos()));
  if(selected){
      animate(selected);
    }
}

imageView::~imageView()
{
    delete server;
}

void imageView::startup(const QPixmap &pix,QString desc){
  imageItem *item = new imageItem;
  scene->addItem(item);
  item->setPixmap(pix.scaledToHeight(m));
  item->setToolTip(desc);
  item->setOffset(qrand()%(m/2),qrand()%(m/2));
  info->setHtml(desc);
  animate(item);
  selected = item;
}

void imageView::replyFinished(QNetworkReply *reply)
{
  QByteArray ans =reply->readAll();
  qDebug()<< ans.size();

  QPixmap pix;
  if(pix.loadFromData(ans)){
      QString desc = lookup.value(reply);
      startup(pix,desc);
    }
  reply->deleteLater();
}
