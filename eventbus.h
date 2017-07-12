#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <QEvent>
#include <QObject>

class eventBus : public QObject
{
    Q_OBJECT
public:
    explicit eventBus(QObject *parent = nullptr);

    bool eventFilter (QObject *obj, QEvent *event);

signals:

public slots:
};

#endif // EVENTBUS_H
