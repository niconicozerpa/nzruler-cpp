#ifndef __NZULER_H__

#define __NZULER_H__

#include <memory>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/event.h>

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

class NZRuler: public wxFrame {
protected:
    wxColour yellow;
    wxColour blue;

    unique_ptr<wxPanel> panel;

    MouseOffset mouseOffset;

    bool mouseIsPressed;
    int resizeArea;
    wxStockCursor oldCursor;
    Mouse mouse;

    wxFont font;
    int safePos;
    int vertical;

    unique_ptr<wxFileConfig> settings;

    void initValues();

    void paintEvent(wxPaintEvent &);
    void paintNow();
 
    void render(wxDC &);

    void closeWindowEvent(wxCloseEvent &);
    void leftDownEvent(wxMouseEvent &);
    void leftUpEvent(wxMouseEvent &);
    void keyDownEvent(wxKeyEvent &);
    void motionEvent(wxMouseEvent &);
    void enterWindow(wxMouseEvent &);
    
    void SetSize(int, int);
    void SetSize(wxSize);

public:
    NZRuler();
};


#endif // __NZULER_H__