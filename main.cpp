#include "YahtzeeUI.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YahtzeeUI yahtzeeWindow;
    yahtzeeWindow.show();
    return a.exec();
}
