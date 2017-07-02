#ifndef __NZULER_H__

#define __NZULER_H__

#include <memory>
#include <QCloseEvent>
#include <QColor>
#include <QCursor>
#include <QFont>
#include <QFrame>
#include <QMouseEvent>
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

    void closeEvent(QCloseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

public:
    NZRuler(QWidget *, Qt::WindowFlags);
};

#endif // __NZULER_H__