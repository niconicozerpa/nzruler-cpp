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

    MouseOffset mouseOffset;

    bool mouseIsPressed;
    int resizeArea;
    wxCursor * oldCursor;
    Mouse mouse;

    wxFont font;
    int safePos;
    int vertical;

    shared_ptr<wxFileConfig> settings;

    void initValues();

    void paintEvent(wxPaintEvent &);
    void paintNow();
 
    void render(wxDC &);

    /*void closeEvent(QCloseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void resize(int, int);*/

    DECLARE_EVENT_TABLE()

public:
    NZRuler();
};


#endif // __NZULER_H__