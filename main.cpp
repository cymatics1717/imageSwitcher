#include <QApplication>
#include <QGraphicsScene>
#include <imageview.h>
#include <eventbus.h>
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  imageView w;

  w.show();
  eventBus bus;
  a.installEventFilter(&bus);
  return a.exec();
}
