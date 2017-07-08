#include <QApplication>
#include <QGraphicsScene>
#include <imageview.h>
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  imageView w;

  w.show();

  return a.exec();
}
