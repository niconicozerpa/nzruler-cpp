#include "nzruler.h"

#include <string>
#include <iostream>
using namespace std;

void NZRuler::initValues() {
    this->yellow = wxColor(255, 255, 128, 255);
    this->black = wxColor(0, 0, 0, 255);
    this->blue = wxColor(0, 0, 170, 255);
    this->red = wxColor(255, 0, 0, 255);

    this->mouseOffset.x = 0;
    this->mouseOffset.y = 0;
    this->mouseOffset.dx = 0;
    this->mouseOffset.dy = 0;

    this->mouseIsPressed = false;
    this->resizeArea = 12;
    this->oldCursor = (wxCursor * )wxSTANDARD_CURSOR;
    this->mouse.x = 0;
    this->mouse.y = 0;

    this->font = wxFont(wxFontInfo(9).FaceName("FreeSans, Helvetica, Arial, sans-serif").Bold());
    this->safePos = 33;
    this->vertical = false;

    // this->settings = make_shared<QSettings>("nzruler", "nzruler");
}

NZRuler::NZRuler():
    wxFrame(
        NULL,
        wxID_ANY,
        "NZRuler",
        wxDefaultPosition,
        wxDefaultSize,
        wxNO_BORDER | wxWANTS_CHARS
    ) {
    this->initValues();

    wxPoint firstPos;
    wxSize firstSize;
    bool firstVertical;

    /*if(this->settings->contains("position")) {
        firstPos = this->settings->value("position").toPoint();
    } else {*/
        firstPos = wxPoint(100, 100);
    /*}*/
        
    /*if(this->settings->contains("size")) {
        firstSize = this->settings->value("size").toSize();
    } else {*/
        firstSize = wxSize(200, 60);
    /*}*/
    
    /*if(this->settings->contains("vertical")) {
        firstVertical = this->settings->value("vertical").toBool();
    } else {*/
        firstVertical = false;
    /*}*/
        
    this->vertical = firstVertical;
    this->SetPosition(firstPos);
    this->SetSize(firstSize);

    this->panel = unique_ptr<wxPanel>(new wxPanel(this, wxID_ANY, firstPos, firstSize));
    
    this->panel->Bind(wxEVT_PAINT, &NZRuler::paintEvent, this);
    this->panel->Bind(wxEVT_KEY_DOWN, &NZRuler::keyDownEvent, this);
    
    /*this->setMouseTracking(true);
    this->setFocusPolicy((Qt::FocusPolicy)(Qt::ClickFocus | Qt::WheelFocus | Qt::TabFocus | Qt::StrongFocus));*/
}
/*


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
}*/

void NZRuler::keyDownEvent(wxKeyEvent & evt) {
    cout << "Hola mundo!" << endl;
    evt.Skip();
    //auto key = evt.GetKeyCode();

    
    
    /*if(key == WXK_ESCAPE) {
        this->Close();
    }/* else {
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
    }*/
}

/*
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
}*/

void NZRuler::paintEvent(wxPaintEvent & evt) {
    wxPaintDC dc(this->panel.get());
    this->render(dc);
}

void NZRuler::paintNow()
{
    wxClientDC dc(this->panel.get());
    this->render(dc);
}

void NZRuler::render(wxDC & dc) {
    
    dc.SetFont(this->font);

    wxSize size_obj = this->GetSize();
    int width = size_obj.GetWidth();
    int height = size_obj.GetHeight();
    
    dc.SetBrush(wxBrush(this->yellow));
    dc.SetPen(* wxBLACK_PEN);
    dc.DrawRectangle(0, 0, width, height);

    this->safePos = this->vertical ? 0 : 33;
        
    int size = this->vertical ? height : width;
    
    dc.SetTextForeground(* wxRED);
    int limit;
    
    if (this->vertical) {
        string str = to_string(height);
        
        wxCoord w, h;
        dc.GetTextExtent(str, &w, &h);

        limit = height - 3 - h;

        dc.DrawText(str, 17.5, limit);
    } else {
        string str = to_string(width);

        wxCoord w, h;
        dc.GetTextExtent(str, &w, &h);

        limit = (width - 3 - w);

        dc.DrawText(str, limit, 17.5);
    }
    
    dc.SetTextForeground(* wxBLACK);
    
    for (int i = 0; i < size; i += 2) {
        int length;

        if (i % 50 == 0) {
            length = 15;

        } else if (i % 10 == 0) {
            length = 10;
        } else {
            length = 5;
        }
        
        if (this->vertical) {
            dc.DrawLine(0, i, length, i);
        } else {
            dc.DrawLine(i, 0, i, length);
        }
        
        if (length == 15) {
            string label = to_string(i);

            wxCoord w, h;
            dc.GetTextExtent(label, &w, &h);

            float labelX;
            float labelY;

            bool drawLabel;
            
            if (this->vertical) {
                labelX = 17.5;
                labelY = i - (h / 2);
                
                if (this->safePos < w) {
                    this->safePos = w + 5;
                }
                    
                drawLabel = (labelY + h) < limit;
            } else {
                labelX = i - (w / 2);
                labelY = 17.5;
                
                drawLabel = (labelX + w) < limit;
            }

            if(drawLabel) {
                dc.DrawText(label, labelX, labelY);
            }
        }
    }

    /*if (!this->mouseIsPressed) {
        pnt.setPen(this->blue);
        
        if (this->vertical) {
            pnt.drawLine(0, this->mouse.y, width, this->mouse.y);
        } else {
            pnt.drawLine(this->mouse.x, 0, this->mouse.x, height);
        }

        QStaticText label(QString("%1").arg(this->vertical ? this->mouse.y : this->mouse.x));
        
        int posX, posY;
        bool drawLabel;

        if (this->vertical) {
            posX = this->safePos;
            posY = this->mouse.y + 5;
            
            drawLabel = (posY + label.size().height()) > limit;
        } else {
            posX = this->mouse.x + 5;
            posY = this->safePos;
        
            if (posX + label.size().width() > (width - 5)) {
                posX = this->mouse.x - 5 - label.size().width();
            }
        }
        
        pnt.drawStaticText(posX, posY, label);
    }
    pnt.end();*/
}