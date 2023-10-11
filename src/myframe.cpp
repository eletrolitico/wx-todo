#include "myframe.h"

#include <wx/splitter.h>

#include "dao.h"
#include "ids.h"
#include "intdata.h"
#include "newdlg.h"

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_BUTTON(wxID_ADD, MyFrame::OnAdd)
EVT_BUTTON(wxID_DELETE, MyFrame::OnDelete)
EVT_LISTBOX(wxID_ANY, MyFrame::OnSelect)

EVT_BUTTON(MyId::DONE, MyFrame::OnToggleDone)
EVT_BUTTON(wxID_SAVE, MyFrame::OnSave)
END_EVENT_TABLE();

MyFrame::MyFrame(Dao *dao)
    : wxFrame(nullptr, wxID_ANY, wxT("My TODO App"), wxDefaultPosition,
              {600, 400}),
      m_dao(dao) {
#ifdef __WXMSW__
  this->SetIcon(wxIcon("icon"));
#endif

  this->SetSizeHints({500, 300});
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

  auto splitter =
      new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                           wxSP_3D | wxSP_LIVE_UPDATE);

  auto leftPanel = new wxPanel(splitter, wxID_ANY);
  m_listBox = new wxCheckListBox(leftPanel, wxID_ANY);

  auto btnAdd = new wxButton(leftPanel, wxID_ADD, wxT("Add"));
  auto btnDel = new wxButton(leftPanel, wxID_DELETE, wxT("Delete"));

  auto btnBar = new wxBoxSizer(wxHORIZONTAL);
  btnBar->Add(btnAdd, 1);
  btnBar->AddSpacer(5);
  btnBar->Add(btnDel, 1);

  auto leftSizer = new wxBoxSizer(wxVERTICAL);
  leftSizer->Add(m_listBox, 1, wxEXPAND | wxLEFT, 5);
  leftSizer->Add(btnBar, 0, wxEXPAND | wxLEFT, 5);

  leftPanel->SetSizerAndFit(leftSizer);

  m_todoPanel = new TodoPanel(splitter);

  splitter->SplitVertically(leftPanel, m_todoPanel, 150);

  m_todos = dao->get_todos();
  for (auto t : m_todos) {
    m_listBox->Append(t.title, new myIntData(t.id));
  }
}

void MyFrame::OnExit(wxCommandEvent &) { Close(true); }

void MyFrame::OnAbout(wxCommandEvent &) {
  wxMessageBox("This is a simple todo app", "About wxTodo",
               wxOK | wxICON_INFORMATION);
}

void MyFrame::OnAdd(wxCommandEvent &) {
  NewDlg newDlg(this);
  if (newDlg.ShowModal() != wxID_OK)
    return;

  auto t = newDlg.GetTodo();

  if (!m_dao->insert_todo(t)) {
    wxMessageBox(wxT("Error inserting todo into database"));
    return;
  }

  m_todos.push_back(t);
  m_listBox->Append(t.title, new myIntData(t.id));
}
void MyFrame::OnDelete(wxCommandEvent &) {
  if (m_curTodo <= 0) {
    wxMessageBox("Select a todo to delete!");
    return;
  }
  if (!m_dao->delete_todo(m_curTodo)) {
    wxMessageBox(wxT("Error deleting todo!"));
    return;
  }

  m_curTodo = -1;
  m_todoPanel->Unselect();

  m_listBox->Clear();
  m_todos = m_dao->get_todos();
  for (auto t : m_todos) {
    m_listBox->Append(t.title, new myIntData(t.id));
  }
}

void MyFrame::OnSelect(wxCommandEvent &evt) {
  m_curTodo = static_cast<myIntData *>(evt.GetClientObject())->GetData();
  Todo t;
  for (const Todo &tt : m_todos) {
    if (tt.id == m_curTodo) {
      t = tt;
      break;
    }
  }
  m_todoPanel->SetTodo(t);
}

void MyFrame::OnSave(wxCommandEvent &) {}
void MyFrame::OnToggleDone(wxCommandEvent &) {}
