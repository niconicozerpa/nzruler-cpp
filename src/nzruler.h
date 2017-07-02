#ifndef __NZULER_H__

#define __NZULER_H__

#include <memory>
#include <QColor>
#include <QCursor>
#include <QFont>
#include <QFrame>
#include <QSettings>
#include <QCloseEvent>

using namespace std;

typedef struct MouseOffset {
    int x;
    int y;
    int dx;
    int dy;
} MouseOffset;

typedef struct Mouse {
    int x;
    int y;
} Mouse;

class NZRuler: public QFrame {
protected:
    QColor yellow;
    QColor black;
    QColor blue;
    QColor red;

    MouseOffset mouseOffset;

    bool mouseIsPressed;
    int resizeArea;
    Qt::CursorShape oldCursor;
    Mouse mouse;

    QFont font;
    int safePos;
    int vertical;

    shared_ptr<QSettings> settings;

    void initValues();

public:
    NZRuler(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    void closeEvent(QCloseEvent * evt);
};

#endif // __NZULER_H__