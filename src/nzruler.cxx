#include "nzruler.h"

#include <string>
#include <wx/dcbuffer.h>

void NZRuler::initValues() {
    this->yellow = wxColor(255, 255, 128, 255);
    this->blue = wxColor(0, 0, 170, 255);

    this->mouseOffset.x = 0;
    this->mouseOffset.y = 0;
    this->mouseOffset.dx = 0;
    this->mouseOffset.dy = 0;

    this->mouseIsPressed = false;
    this->resizeArea = 12;
    this->oldCursor = wxCURSOR_ARROW;
    this->mouse.x = 0;
    this->mouse.y = 0;

    this->font = wxFont(wxFontInfo(9).FaceName("FreeSans, Helvetica, Arial, sans-serif").Bold());
    this->safePos = 33;
    this->vertical = false;

    this->panel = unique_ptr<wxPanel>(new wxPanel(this, wxID_ANY));
    this->settings = unique_ptr<wxFileConfig>(new wxFileConfig(
        "nzruler",
        "nzruler",
        wxEmptyString,
        wxEmptyString,
        wxCONFIG_USE_LOCAL_FILE
    ));
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

    int position_x, position_y;
    int size_w, size_h;
    bool vertical;

    if(
        this->settings->Read("position_x", &position_x)
        && this->settings->Read("position_y", &position_y)
    ) {
        firstPos = wxPoint(position_x, position_y);
    } else {
        firstPos = wxPoint(100, 100);
    }
        
    if(
        this->settings->Read("size_w", &size_w)
        && this->settings->Read("size_h", &size_h)
    ) {
        firstSize = wxSize(size_w, size_h);
    } else {
        firstSize = wxSize(200, 60);
    }
    
    if(this->settings->Read("vertical", &vertical)) {
        firstVertical = vertical;
    } else {
        firstVertical = false;
    }
        
    this->vertical = firstVertical;
    this->SetPosition(firstPos);
    this->SetSize(firstSize);

    this->panel->Bind(wxEVT_PAINT, &NZRuler::paintEvent, this);
    this->panel->Bind(wxEVT_KEY_DOWN, &NZRuler::keyDownEvent, this);
    this->panel->Bind(wxEVT_MOTION, &NZRuler::motionEvent, this);
    this->panel->Bind(wxEVT_LEFT_DOWN, &NZRuler::leftDownEvent, this);
    this->panel->Bind(wxEVT_LEFT_UP, &NZRuler::leftUpEvent, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &NZRuler::closeWindowEvent, this);
}

void NZRuler::closeWindowEvent(wxCloseEvent & evt) {
    auto size = this->GetSize();
    auto position = this->GetPosition();
    this->settings->Write("position_x", position.x);
    this->settings->Write("position_y", position.y);
    this->settings->Write("size_w", size.GetWidth());
    this->settings->Write("size_h", size.GetHeight());
    this->settings->Write("vertical", this->vertical);

    evt.Skip();
}

void NZRuler::leftDownEvent(wxMouseEvent & evt) {
    wxSize size = this->GetSize();

    wxPoint screen_pos = wxGetMousePosition();
    wxPoint frame_pos = this->ScreenToClient(screen_pos);

    this->mouseIsPressed = true;
    this->mouseOffset.x = frame_pos.x;
    this->mouseOffset.y = frame_pos.y;
    this->mouseOffset.dx = size.GetWidth() - this->mouseOffset.x;
    this->mouseOffset.dy = size.GetHeight() - this->mouseOffset.y;
}

void NZRuler::leftUpEvent(wxMouseEvent & event) {
    if(this->mouseIsPressed) {
        this->mouseIsPressed = false;
    }
}

void NZRuler::keyDownEvent(wxKeyEvent & evt) {
    auto key = evt.GetKeyCode();

    if(key == WXK_ESCAPE) {
        this->Close();
    } else {
        unsigned short int increment;
        auto modifiers = evt.GetModifiers();

        if (modifiers & wxMOD_SHIFT) {
            increment = 3;
        } else {
            increment = 1;
        }

        if(modifiers & wxMOD_ALT) {
            wxSize size = this->GetSize();

            int new_width = 0;
            int new_height = 0;

            bool resize = true;

            switch (key) {
                case WXK_LEFT:
                    new_width = size.GetWidth() - increment;
                    new_height = size.GetHeight();
                    break;

                case WXK_UP:
                    new_width = size.GetWidth();
                    new_height = size.GetHeight() - increment;
                    break;

                case WXK_RIGHT:
                    new_width = size.GetWidth() + increment;
                    new_height = size.GetHeight();
                    break;

                case WXK_DOWN:
                    new_width = size.GetWidth();
                    new_height = size.GetHeight() + increment;
                    break;

                default:
                    resize = false;
            }

            if (resize) {
                this->SetSize(new_width, new_height);
            }

        } else {
            
            wxPoint pos = this->GetPosition();
            int new_x = 0;
            int new_y = 0;

            bool move = true;

            switch (key) {
                case WXK_LEFT:
                    new_x = pos.x - increment;
                    new_y = pos.y;
                    break;

                case WXK_UP:
                    new_x = pos.x;
                    new_y = pos.y - increment;
                    break;

                case WXK_RIGHT:
                    new_x = pos.x + increment;
                    new_y = pos.y;
                    break;

                case WXK_DOWN:
                    new_x = pos.x;
                    new_y = pos.y + increment;
                    break;

                default:
                    move = false;
            }
            
            if (move) {
                this->Move(new_x, new_y);
            }
        }
    }
}

void NZRuler::motionEvent(wxMouseEvent & evt) {

    wxPoint screen_pos = wxGetMousePosition();
    wxPoint frame_pos = this->ScreenToClient(screen_pos);
    wxSize frame_size = this->GetSize();

    int x = screen_pos.x;
    int y = screen_pos.y;
    int lx = frame_pos.x;
    int ly = frame_pos.y;
    
    int w = frame_size.GetWidth();
    int h = frame_size.GetHeight();
    
    this->mouse.x = lx;
    this->mouse.y = ly;
    
    if (this->mouseIsPressed) {
        if (this->oldCursor == wxCURSOR_SIZEWE) {
            this->SetSize(lx + this->mouseOffset.dx, h);
        }

        else if (this->oldCursor == wxCURSOR_SIZENS) {
            this->SetSize(w, ly + this->mouseOffset.dy);
        }

        else if (this->oldCursor == wxCURSOR_SIZING) {
            this->SetSize(lx + this->mouseOffset.dx, ly + this->mouseOffset.dy);
        }
        
        else {
            this->Move(x - this->mouseOffset.x, y - this->mouseOffset.y);
        }

    } else {
        wxStockCursor newCursor;

        if (lx > (w - this->resizeArea) && ly > (h - this->resizeArea)) {
            newCursor = wxCURSOR_SIZING;

        } else if (lx > (w - this->resizeArea)) {
            newCursor = wxCURSOR_SIZEWE;
        }

        else if (ly > (h - this->resizeArea)) {
            newCursor = wxCURSOR_SIZENS;
        }

        else {
            newCursor = wxCURSOR_ARROW;
        }
        
        if (newCursor != this->oldCursor) {
            this->SetCursor(newCursor);
            this->oldCursor = newCursor;
        }
        
        this->paintNow();
    }
}

void NZRuler::SetSize(wxSize size) {
    this->SetSize(size.GetWidth(), size.GetHeight());
}
void NZRuler::SetSize(int width, int height) {
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
    
    this->wxFrame::SetSize(width, height);
}

void NZRuler::paintEvent(wxPaintEvent & evt) {
    wxBufferedPaintDC bdc(this->panel.get());
    this->render(bdc);
}

void NZRuler::paintNow()
{
    wxClientDC dc(this->panel.get());
    wxBufferedDC bdc(&dc);
    this->render(bdc);
    bdc.UnMask();
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

    if (!this->mouseIsPressed) {
        dc.SetPen(wxPen(this->blue));
        dc.SetTextForeground(this->blue);
        
        if (this->vertical) {
            dc.DrawLine(0, this->mouse.y, width, this->mouse.y);
        } else {
            dc.DrawLine(this->mouse.x, 0, this->mouse.x, height);
        }

        string label = to_string(this->vertical ? this->mouse.y : this->mouse.x);

        wxCoord w, h;
        dc.GetTextExtent(label, &w, &h);
        
        int posX, posY;
        bool drawLabel;

        if (this->vertical) {
            posX = this->safePos;
            posY = this->mouse.y + 5;
            
            drawLabel = (posY + h) > limit;
        } else {
            posX = this->mouse.x + 5;
            posY = this->safePos;
        
            if (posX + w > (width - 5)) {
                posX = this->mouse.x - 5 - w;
            }
        }
        
        dc.DrawText(label, posX, posY);
    }
}