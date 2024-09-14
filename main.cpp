#include <QApplication>
#include <QFontDatabase>
#include <QDir>
#include <QDebug>
#include "YahtzeeUiSetup.h"
#include "YahtzeeUI.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    YahtzeeUI yahtzeeWindow;
    yahtzeeWindow.show();
    return a.exec();
}

