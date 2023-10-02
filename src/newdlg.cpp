#include "newdlg.h"

NewDlg::NewDlg(wxWindow *parent)
    : wxDialog(parent, wxID_ANY, "New ToDo", wxDefaultPosition, wxDefaultSize,
               wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {

  m_title = new wxTextCtrl(this, wxID_ANY);
  m_desc = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                          wxDefaultSize, wxTE_MULTILINE);

  m_title->SetValidator(wxTextValidator(wxFILTER_EMPTY));

  auto titleLabel = new wxStaticText(this, wxID_ANY, wxT("Title"));
  auto descLabel = new wxStaticText(this, wxID_ANY, wxT("Description"));

  auto btnOk = new wxButton(this, wxID_OK, wxT("Ok"));
  auto btnCancel = new wxButton(this, wxID_CANCEL, wxT("Cancel"));

  auto mainSizer = new wxBoxSizer(wxVERTICAL);
  auto btnBar = new wxBoxSizer(wxHORIZONTAL);

  mainSizer->Add(titleLabel, 0, wxEXPAND | wxTOP | wxLEFT, 5);
  mainSizer->Add(m_title, 0, wxEXPAND | wxALL, 5);
  mainSizer->Add(descLabel, 0, wxEXPAND | wxTOP | wxLEFT, 5);
  mainSizer->Add(m_desc, 1, wxEXPAND | wxALL, 5);
  mainSizer->Add(btnBar, 0, wxALIGN_RIGHT | wxALL, 5);

  btnBar->Add(btnCancel, 0, wxRIGHT, 5);
  btnBar->Add(btnOk);

  this->SetSizerAndFit(mainSizer);
  this->SetSize({600, 400});
}

Todo NewDlg::GetTodo() {
  Todo t;
  t.id = 0;
  t.title = m_title->GetValue();
  t.desc = m_desc->GetValue();

  return t;
}
