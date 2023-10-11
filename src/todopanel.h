#ifndef TODO_PANEL_H
#define TODO_PANEL_H

#include "todo.h"
#include "wx/event.h"
#include <wx/wx.h>

enum class PanelMode { NONE, EMPTY, SHOWING, EDITING };

class TodoPanel : public wxPanel {
public:
  TodoPanel(wxWindow *parent);
  void SetTodo(const Todo &todo);
  void Unselect();
  void SetShow();

private:
  wxBoxSizer *m_sizer_main, *m_sizer_title, *m_sizer_btn;
  wxStaticText *m_static_empty, *m_static_title, *m_static_desc;
  wxTextCtrl *m_ctrl_title, *m_ctrl_desc;
  wxButton *m_btn_edit, *m_btn_done, *m_btn_cancel, *m_btn_save;

  DECLARE_EVENT_TABLE();

  void OnEdit(wxCommandEvent &);
  void OnCancelEdit(wxCommandEvent &);

  PanelMode m_mode{PanelMode::NONE};

  void HideChildren();

  const wxFont title_font =
      wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
};

#endif
