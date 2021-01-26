#include "imitator.h"
#include <QApplication>

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  Imitator window;

  window.setWindowTitle("Imitator");
  window.show();

  return app.exec();
}
