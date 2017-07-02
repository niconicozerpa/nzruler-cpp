#include "nzruler.h"

#include <iostream>
#include <QApplication>

using namespace std;

int main(int argc, char ** argv) {
    
    QApplication app(argc, argv);
    
    NZRuler mainWindow(Q_NULLPTR, Qt::FramelessWindowHint);

    mainWindow.show();
    return app.exec();
}