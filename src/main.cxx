#include "nzruler.h"

class NZRulerApp : public wxApp {
public:
    virtual bool OnInit();
};

bool NZRulerApp::OnInit() {
    NZRuler * window = new NZRuler();
    window->Show(true);
    return true;
}

wxIMPLEMENT_APP(NZRulerApp);