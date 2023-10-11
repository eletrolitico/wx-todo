#include "todopanel.h"
#include "ids.h"

BEGIN_EVENT_TABLE(TodoPanel, wxPanel)
EVT_BUTTON(wxID_EDIT, TodoPanel::OnEdit)
EVT_BUTTON(wxID_CANCEL, TodoPanel::OnCancelEdit)
END_EVENT_TABLE();

TodoPanel::TodoPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {
  m_sizer_main = new wxBoxSizer(wxVERTICAL);
  m_sizer_title = new wxBoxSizer(wxHORIZONTAL);
  m_sizer_btn = new wxStdDialogButtonSizer();

  m_static_title = new wxStaticText(this, wxID_ANY, wxT("EMPTY"));
  m_static_title->SetFont(title_font);

  m_static_desc = new wxStaticText(this, wxID_ANY, wxT("EMPTY"));

  m_static_empty =
      new wxStaticText(this, wxID_ANY, wxT("Select a todo to see it here!"));

  m_btn_edit = new wxButton(this, wxID_EDIT);
  m_btn_done = new wxButton(this, MyId::DONE, wxT("EMPTY"));
  m_btn_cancel = new wxButton(this, wxID_CANCEL);
  m_btn_save = new wxButton(this, wxID_SAVE);

  m_ctrl_title = new wxTextCtrl(this, wxID_ANY);
  m_ctrl_desc = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                               wxDefaultSize, wxTE_MULTILINE);

  m_sizer_title->Add(m_static_title);

  SetSizer(m_sizer_main);
  Unselect();
}

void TodoPanel::SetTodo(const Todo &todo) {
  m_static_title->SetLabel(todo.title);
  m_static_desc->SetLabel(todo.desc);
  m_btn_done->SetLabel(todo.done ? wxT("Mark as not done")
                                 : wxT("Mark as done"));

  SetShow();
}

void TodoPanel::Unselect() {
  if (m_mode == PanelMode::EMPTY)
    return;
  m_mode = PanelMode::EMPTY;
  HideChildren();

  m_sizer_main->Clear();

  m_static_empty->Show(true);
  m_sizer_main->AddStretchSpacer(1);
  m_sizer_main->Add(m_static_empty, 0, wxALIGN_CENTER);
  m_sizer_main->AddStretchSpacer(1);

  Fit();
}

void TodoPanel::SetShow() {
  if (m_mode == PanelMode::SHOWING) {
    return;
  }

  m_mode = PanelMode::SHOWING;
  HideChildren();
  m_static_title->Show();
  m_static_desc->Show();
  m_btn_edit->Show();
  m_btn_done->Show();

  m_sizer_btn->Clear();

  m_sizer_btn->Add(m_btn_edit);
  m_sizer_btn->Add(m_btn_done);

  m_sizer_main->Clear();

  m_sizer_main->Add(m_sizer_title, 0, wxALL | wxEXPAND, 10);
  m_sizer_main->Add(m_static_desc, 1, wxLEFT | wxRIGHT | wxEXPAND, 10);
  m_sizer_main->Add(m_sizer_btn, 0, wxALL | wxEXPAND, 10);

  Fit();
}

void TodoPanel::HideChildren() {
  m_static_empty->Hide();
  m_static_title->Hide();
  m_static_desc->Hide();
  m_ctrl_title->Hide();
  m_ctrl_desc->Hide();
  m_btn_edit->Hide();
  m_btn_done->Hide();
  m_btn_save->Hide();
  m_btn_cancel->Hide();
}

void TodoPanel::OnEdit(wxCommandEvent &) {
  m_mode = PanelMode::EDITING;
  HideChildren();
  m_ctrl_title->Show();
  m_ctrl_desc->Show();
  m_btn_save->Show();
  m_btn_cancel->Show();

  m_ctrl_title->SetValue(m_static_title->GetLabel());
  m_ctrl_desc->SetValue(m_static_desc->GetLabel());

  m_sizer_btn->Clear();

  m_sizer_btn->Add(m_btn_cancel);
  m_sizer_btn->Add(m_btn_save);

  m_sizer_main->Add(m_ctrl_title, 0, wxALL | wxEXPAND, 10);
  m_sizer_main->Add(m_ctrl_desc, 1, wxLEFT | wxRIGHT | wxEXPAND, 10);
  m_sizer_main->Add(m_sizer_btn, 0, wxALL | wxEXPAND, 10);

  Fit();
}

void TodoPanel::OnCancelEdit(wxCommandEvent &) { SetShow(); }
