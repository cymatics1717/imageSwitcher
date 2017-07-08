#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QJsonObject>
#include <QGraphicsPixmapItem>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "backend.h"

class imageItem : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
    Q_PROPERTY (qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY (QPointF pos READ pos WRITE setPos)
};

class imageView : public QGraphicsView
{
  Q_OBJECT
public:
  explicit imageView(QWidget *parent = Q_NULLPTR);
  ~imageView();

public slots:
  void replyFinished(QNetworkReply*);
  void incomingImage(QJsonObject obj);
  void fadingAway();
  void animate(imageItem *item);
  void startup(const QPixmap &pix, QString desc);
protected:
  void keyPressEvent(QKeyEvent *event)  Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
  imageItem* selected;
  QGraphicsScene *scene;
  backEnd *server;
  QGraphicsTextItem *info;
//  QHash<imageItem*,QJsonObject> buff;

  QNetworkAccessManager *manager;
  QHash<QNetworkReply*,QString> lookup;
};

#endif // IMAGEVIEW_H
