#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyThread thread;
    thread.start();
    MainWindow window;
    window.show();

    return a.exec();
}

