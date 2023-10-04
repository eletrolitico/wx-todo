#include "todopanel.h"

TodoPanel::TodoPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {
  m_sizer = new wxBoxSizer(wxVERTICAL);
  Unselect();
}

void TodoPanel::SetTodo(const Todo &todo) {
  if (m_emptyText != nullptr) {
    m_sizer->Clear(true);
    m_emptyText = nullptr;

    m_checkbox = new wxCheckBox(this, wxID_ANY, "");
    m_title = new wxStaticText(this, wxID_ANY, todo.title);
    m_desc = new wxStaticText(this, wxID_ANY, todo.desc);

    m_checkbox->SetValue(todo.done);

    auto hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(m_checkbox);
    hSizer->Add(m_title);

    m_sizer->Add(hSizer);
    m_sizer->Add(m_desc);
    this->Fit();
    return;
  }

  m_title->SetLabel(todo.title);
  m_desc->SetLabel(todo.desc);
  m_checkbox->SetValue(todo.done);
  this->Fit();
}

void TodoPanel::Unselect() {
  m_sizer->Clear(true);
  m_emptyText =
      new wxStaticText(this, wxID_ANY, wxT("Select a todo to see it here!"));
  m_sizer->AddStretchSpacer(1);
  m_sizer->Add(m_emptyText, 0, wxALIGN_CENTER);
  m_sizer->AddStretchSpacer(1);
  this->SetSizerAndFit(m_sizer);
}