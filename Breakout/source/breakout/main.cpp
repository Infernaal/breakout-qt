#include <QApplication>
#include "breakout.h"
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication breakout(argc, argv);
    mainwindow breakoutWindow;
    breakoutWindow.show();
    return breakout.exec();
}
