#include "newdlg.h"

NewDlg::NewDlg(wxWindow *parent) : wxDialog(parent, wxID_ANY, "New ToDo") {
  auto title = new wxTextCtrl(this, wxID_ANY);
  auto desc = new wxTextCtrl(this, wxID_ANY);

  auto btnOk = new wxButton(this, wxID_OK, wxT("Ok"));
  auto btnCancel = new wxButton(this, wxID_CANCEL, wxT("Cancel"));

  auto mainSizer = new wxBoxSizer(wxVERTICAL);
  auto btnBar = new wxBoxSizer(wxHORIZONTAL);

  mainSizer->Add(title);
  mainSizer->Add(desc);
  mainSizer->Add(btnBar);

  btnBar->Add(btnOk);
  btnBar->Add(btnCancel);

  this->SetSizerAndFit(mainSizer);
}
