#ifndef __NZULER_H__

#define __NZULER_H__

#include <memory>
#include <QColor>
#include <QCursor>
#include <QFont>
#include <QSettings>

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

class NZRuler {
protected:
    shared_ptr<QColor> yellow;
    shared_ptr<QColor> black;
    shared_ptr<QColor> blue;
    shared_ptr<QColor> red;

    MouseOffset mouseOffset;

    bool mouseIsPressed;
    int resizeArea;
    Qt::CursorShape oldCursor;
    Mouse mouse;

    shared_ptr<QFont> font;
    int safePos;
    int vertical;

    shared_ptr<QSettings> settings;
};

#endif // __NZULER_H__