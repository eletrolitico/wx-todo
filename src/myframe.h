#ifndef MY_FRAME_H
#define MY_FRAME_H

#include "wx/event.h"
#include <wx/wx.h>

class MyFrame : public wxFrame {
public:
  MyFrame();

private:
  void OnHello(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  DECLARE_EVENT_TABLE();
};

#endif
