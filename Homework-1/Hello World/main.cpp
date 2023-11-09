#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
    
  QLabel *label = new QLabel("Hello World!");
  label->setWindowTitle("First Qt!");
  label->resize(200, 50);
  label->show();

  return app.exec();
}
