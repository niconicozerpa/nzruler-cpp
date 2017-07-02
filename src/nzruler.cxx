#include "nzruler.h"

#include <QPoint>
#include <QSize>

void NZRuler::initValues() {
    this->yellow = make_shared<QColor>(255, 255, 128, 255);
    this->black = make_shared<QColor>(0, 0, 0, 255);
    this->blue = make_shared<QColor>(0, 0, 170, 255);
    this->red = make_shared<QColor>(255, 0, 0, 255);

    this->mouseOffset.x = 0;
    this->mouseOffset.y = 0;
    this->mouseOffset.dx = 0;
    this->mouseOffset.dy = 0;

    this->mouseIsPressed = false;
    this->resizeArea = 12;
    this->oldCursor = Qt::ArrowCursor;
    this->mouse.x = 0;
    this->mouse.y = 0;

    this->font = make_shared<QFont>("FreeSans, Helvetica, Arial, sans-serif", 9, QFont::Bold, false);
    this->safePos = 33;
    this->vertical = false;

    this->settings = make_shared<QSettings>("nzruler", "nzruler");
}

NZRuler::NZRuler(QWidget * parent, Qt::WindowFlags f):
    QFrame(parent, f) {
    this->initValues();

    QPoint firstPos;
    QSize firstSize;
    bool firstVertical;


    if(this->settings->contains("position")) {
        firstPos = this->settings->value("position").toPoint();
    } else {
        firstPos = QPoint(100, 100);
    }
        
    if(this->settings->contains("size")) {
        firstSize = this->settings->value("size").toSize();
    } else {
        firstSize = QSize(200, 60);
    }
    
    if(this->settings->contains("vertical")) {
        firstVertical = this->settings->value("vertical").toBool();
    } else {
        firstVertical = false;
    }
        
    this->vertical = firstVertical;
    this->move(firstPos.x(), firstPos.y());
    this->resize(firstSize.width(), firstSize.height());
    
    this->setMouseTracking(true);
    this->setFocusPolicy((Qt::FocusPolicy)(Qt::ClickFocus | Qt::WheelFocus | Qt::TabFocus | Qt::StrongFocus));
}