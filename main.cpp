#include "yahtzeeUI.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetWindow w;
    w.show();
    return a.exec();
}
