#include "nzruler.h"

#include <QPoint>
#include <QSize>

void NZRuler::initValues() {
    this->yellow = QColor(255, 255, 128, 255);
    this->black = QColor(0, 0, 0, 255);
    this->blue = QColor(0, 0, 170, 255);
    this->red = QColor(255, 0, 0, 255);

    this->mouseOffset.x = 0;
    this->mouseOffset.y = 0;
    this->mouseOffset.dx = 0;
    this->mouseOffset.dy = 0;

    this->mouseIsPressed = false;
    this->resizeArea = 12;
    this->oldCursor = Qt::ArrowCursor;
    this->mouse.x = 0;
    this->mouse.y = 0;

    this->font = QFont("FreeSans, Helvetica, Arial, sans-serif", 9, QFont::Bold, false);
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



void NZRuler::closeEvent(QCloseEvent * evt) {
    this->settings->setValue("position", QVariant(this->pos()));
    this->settings->setValue("size", QVariant(this->size()));
    this->settings->setValue("vertical", QVariant(this->vertical));

    evt->accept();
}

void NZRuler::mousePressEvent(QMouseEvent * evt) {
    if(evt->buttons() & Qt::LeftButton) {
        this->mouseIsPressed = true;
        this->mouseOffset.x = evt->x();
        this->mouseOffset.y = evt->y();
        this->mouseOffset.dx = this->width() - this->mouseOffset.x;
        this->mouseOffset.dy = this->height() - this->mouseOffset.y;
    }
}

void NZRuler::mouseReleaseEvent(QMouseEvent * event) {
    if(this->mouseIsPressed) {
        this->mouseIsPressed = false;
    }
}

void NZRuler::keyPressEvent(QKeyEvent * evt) {
    auto key = evt->key();
    
    if(key == Qt::Key_Escape) {
        this->close();
    } else {
        unsigned short int increment;
        auto modifiers = evt->modifiers();

        if (modifiers & Qt::ShiftModifier) {
            increment = 3;
        } else {
            increment = 1;
        }

        if(modifiers & Qt::AltModifier) {
            QSize size = this->size();

            int new_width = 0;
            int new_height = 0;

            bool resize = true;

            switch (key) {
                case Qt::Key_Left:
                    new_width = size.width() - increment;
                    new_height = size.height();
                    break;

                case Qt::Key_Up:
                    new_width = size.width();
                    new_height = size.height() - increment;
                    break;

                case Qt::Key_Right:
                    new_width = size.width() + increment;
                    new_height = size.height();
                    break;

                case Qt::Key_Down:
                    new_width = size.width();
                    new_height = size.height() + increment;
                    break;

                default:
                    resize = false;
            }

            if (resize) {
                this->resize(new_width, new_height);
            }

        } else {
            
            QPoint pos = this->pos();
            int new_x = 0;
            int new_y = 0;

            bool move = true;

            switch (key) {
                case Qt::Key_Left:
                    new_x = pos.x() - increment;
                    new_y = pos.y();
                    break;

                case Qt::Key_Up:
                    new_x = pos.x();
                    new_y = pos.y() - increment;
                    break;

                case Qt::Key_Right:
                    new_x = pos.x() + increment;
                    new_y = pos.y();
                    break;

                case Qt::Key_Down:
                    new_x = pos.x();
                    new_y = pos.y() + increment;
                    break;

                default:
                    move = false;
            }
            
            if (move) {
                this->move(new_x, new_y);
            }
        }
    }
}


void NZRuler::mouseMoveEvent(QMouseEvent * evt) {
    int x = evt->globalX();
    int y = evt->globalY();
    int lx = evt->x();
    int ly = evt->y();
    int w = this->width();
    int h = this->height();
    
    this->mouse.x = lx;
    this->mouse.y = ly;
    
    if (this->mouseIsPressed) {
        if (this->oldCursor == Qt::SizeHorCursor) {
            this->resize(lx + this->mouseOffset.dx, h);
        }

        else if (this->oldCursor == Qt::SizeVerCursor) {
            this->resize(w, ly + this->mouseOffset.dy);
        }

        else if (this->oldCursor == Qt::SizeFDiagCursor) {
            this->resize(lx + this->mouseOffset.dx, ly + this->mouseOffset.dy);
        }
        
        else {
            this->move(x - this->mouseOffset.x, y - this->mouseOffset.y);
        }

    } else {
        Qt::CursorShape newCursor;

        if (lx > (w - this->resizeArea) && ly > (h - this->resizeArea)) {
            newCursor = Qt::SizeFDiagCursor;

        } else if (lx > (w - this->resizeArea)) {
            newCursor = Qt::SizeHorCursor;
        }

        else if (ly > (h - this->resizeArea)) {
            newCursor = Qt::SizeVerCursor;
        }

        else {
            newCursor = Qt::ArrowCursor;
        }
        
        if (newCursor != this->oldCursor) {
            this->setCursor(newCursor);
            this->oldCursor = newCursor;
        }
        
        this->update();
    }
}

void NZRuler::resize(int width, int height) {
    int minWidth = 60;
    int minHeight = 60;
    
    if (width < minWidth) {
        width = minWidth;
    }
    if (height < minHeight) {
        height = minHeight;
    }
    
    if (width != height) {
        this->vertical = (width < height);
    }
    
    this->QWidget::resize(width, height);
}