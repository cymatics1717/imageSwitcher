#include "eventbus.h"
#include <QDebug>
#include <QMetaClassInfo>

eventBus::eventBus(QObject *parent) : QObject(parent)
{

}

bool eventBus::eventFilter (QObject *obj, QEvent *e)
{
    QSet<QString> buff={"QXcbConnection","QGraphicsScene"};

    if(e->type()==QEvent::MetaCall)
        if(!buff.contains(obj->metaObject()->className())){
        qDebug()<<obj<< "---------"<<e->type();
    }
    return QObject::eventFilter(obj,e);
}
