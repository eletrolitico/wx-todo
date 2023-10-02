#ifndef NEW_DLG_H
#define NEW_DLG_H

#include "todo.h"
#include "wx/wx.h"

class NewDlg : public wxDialog {
public:
  NewDlg(wxWindow *parent);
  Todo GetTodo();

private:
  wxTextCtrl *m_title;
  wxTextCtrl *m_desc;
};

#endif // !NEW_DLG_H
