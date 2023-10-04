#ifndef TODO_PANEL_H
#define TODO_PANEL_H

#include <wx/wx.h>
#include "todo.h"

class TodoPanel : public wxPanel
{
public:
    TodoPanel(wxWindow *parent);
    void SetTodo(const Todo &todo);
    void Unselect();

private:
    wxBoxSizer *m_sizer;
    wxStaticText *m_emptyText, *m_title, *m_desc;
    wxCheckBox *m_checkbox;
};

#endif