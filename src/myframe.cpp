#include "myframe.h"
#include "wx/event.h"
#include "wx/generic/panelg.h"
#include "wx/gtk/button.h"
#include "wx/gtk/listbox.h"
#include "wx/gtk/stattext.h"
#include "wx/sizer.h"
#include <wx/splitter.h>

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
END_EVENT_TABLE();

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, wxT("My TODO App")) {
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(wxID_EXIT);

  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar(menuBar);
  CreateStatusBar();
  SetStatusText("Welcome to wxWidgets!");

  auto splitter = new wxSplitterWindow(
      this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
      wxSP_3D | wxSP_LIVE_UPDATE | wxCLIP_CHILDREN | wxSP_NO_XP_THEME);

  auto leftPanel = new wxPanel(splitter, wxID_ANY);
  auto list = new wxListBox(leftPanel, wxID_ANY);
  auto btn = new wxButton(leftPanel, wxID_ANY, wxT("test"));

  auto leftSizer = new wxBoxSizer(wxVERTICAL);
  leftSizer->Add(list, 1, wxEXPAND);
  leftSizer->Add(btn, 0, wxEXPAND);

  leftPanel->SetSizerAndFit(leftSizer);

  auto rightPanel = new wxPanel(splitter, wxID_ANY);
  auto label = new wxStaticText(rightPanel, wxID_ANY, wxT("test text!!"));

  auto rightSizer = new wxBoxSizer(wxVERTICAL);
  rightSizer->Add(label);

  rightPanel->SetSizerAndFit(rightSizer);

  splitter->SplitVertically(leftPanel, rightPanel, 400);
}

void MyFrame::OnExit(wxCommandEvent &) { Close(true); }

void MyFrame::OnAbout(wxCommandEvent &) {
  wxMessageBox("This is a simple todo app", "About wxTodo",
               wxOK | wxICON_INFORMATION);
}