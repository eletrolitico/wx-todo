#ifndef MY_FRAME_H
#define MY_FRAME_H

#include "dao.h"
#include "wx/event.h"
#include <wx/wx.h>

class MyFrame : public wxFrame {
public:
  MyFrame(Dao *);

private:
  void OnHello(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void OnAdd(wxCommandEvent &event);
  void OnDelete(wxCommandEvent &event);
  void OnSelect(wxCommandEvent &event);
  DECLARE_EVENT_TABLE();

  int m_curTodo{-1};
  Dao *m_dao;

  wxListBox *m_listBox;
};

#endif
