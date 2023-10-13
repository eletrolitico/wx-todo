#ifndef MY_FRAME_H
#define MY_FRAME_H

#include "dao.h"
#include "todopanel.h"
#include "wx/event.h"
#include <wx/splitter.h>
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
  void OnToggleList(wxCommandEvent &event);
  void OnTogglePanel(wxCommandEvent &event);
  void OnUnsplit(wxSplitterEvent &event);

  // evts from todopanel
  void OnSave(wxCommandEvent &);
  void OnToggleDone(wxCommandEvent &);

  void ResetList();

  DECLARE_EVENT_TABLE();

  int m_curTodo{-1};
  Dao *m_dao;
  wxVector<Todo> m_todos;

  wxPanel *m_panel_listbox;
  wxMenu *m_menu_file;
  wxSplitterWindow *m_splitter;
  wxCheckListBox *m_listBox;
  TodoPanel *m_todoPanel;
};

#endif
