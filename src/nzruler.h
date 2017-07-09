#ifndef __NZULER_H__

#define __NZULER_H__

#include <memory>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/fileconf.h>

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
    wxColour black;
    wxColour blue;
    wxColour red;

    unique_ptr<wxPanel> panel;

    MouseOffset mouseOffset;

    bool mouseIsPressed;
    int resizeArea;
    wxCursor * oldCursor;
    Mouse mouse;

    wxFont font;
    int safePos;
    int vertical;

    unique_ptr<wxFileConfig> settings;

    void initValues();

    void paintEvent(wxPaintEvent &);
    void paintNow();
 
    void render(wxDC &);

    /*void closeEvent(QCloseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);*/
    void keyDownEvent(wxKeyEvent &);
    /*void mouseMoveEvent(QMouseEvent *);*/
    
    void SetSize(int, int);
    void SetSize(wxSize);

public:
    NZRuler();
};


#endif // __NZULER_H__