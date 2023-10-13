#include "myframe.h"

#include "dao.h"
#include "ids.h"
#include "intdata.h"
#include "newdlg.h"

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(MyId::LIST, MyFrame::OnToggleList)
EVT_MENU(MyId::PANEL, MyFrame::OnTogglePanel)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_BUTTON(wxID_ADD, MyFrame::OnAdd)
EVT_BUTTON(wxID_DELETE, MyFrame::OnDelete)
EVT_LISTBOX(wxID_ANY, MyFrame::OnSelect)
EVT_CHECKLISTBOX(wxID_ANY, MyFrame::OnToggleDone)
EVT_SPLITTER_UNSPLIT(wxID_ANY, MyFrame::OnUnsplit)

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
  m_menu_file = new wxMenu;
  m_menu_file->Append(MyId::LIST, "Show list", wxEmptyString, wxITEM_CHECK);
  m_menu_file->Append(MyId::PANEL, "Show panel", wxEmptyString, wxITEM_CHECK);
  m_menu_file->AppendSeparator();
  m_menu_file->Append(wxID_EXIT);

  m_menu_file->Check(MyId::LIST, true);
  m_menu_file->Check(MyId::PANEL, true);

  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(m_menu_file, "&File");
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar(menuBar);
  CreateStatusBar();

  m_splitter =
      new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                           wxSP_LIVE_UPDATE | wxSP_3DSASH);

  m_panel_listbox = new wxPanel(m_splitter, wxID_ANY);
  m_listBox = new wxCheckListBox(m_panel_listbox, wxID_ANY);

  auto btnAdd = new wxButton(m_panel_listbox, wxID_ADD, wxT("Add"));
  auto btnDel = new wxButton(m_panel_listbox, wxID_DELETE, wxT("Delete"));

  auto btnBar = new wxBoxSizer(wxHORIZONTAL);
  btnBar->Add(btnAdd, 1);
  btnBar->AddSpacer(5);
  btnBar->Add(btnDel, 1);

  auto leftSizer = new wxBoxSizer(wxVERTICAL);
  leftSizer->Add(m_listBox, 1, wxEXPAND | wxALL, 10);
  leftSizer->Add(btnBar, 0, wxEXPAND | wxLEFT | wxBOTTOM | wxRIGHT, 10);

  m_panel_listbox->SetSizerAndFit(leftSizer);

  m_todoPanel = new TodoPanel(m_splitter);

  m_splitter->SplitVertically(m_panel_listbox, m_todoPanel, 150);

  ResetList();
}

void MyFrame::OnExit(wxCommandEvent &) { Close(true); }

void MyFrame::ResetList() {
  m_todos = m_dao->get_todos();
  m_listBox->Clear();
  for (size_t i = 0; i < m_todos.size(); ++i) {
    auto t = m_todos[i];
    m_listBox->Append(t.title, new myIntData(t.id));
    if (t.done) {
      m_listBox->Check(i, true);
    }
  }
}

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

  ResetList();
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

void MyFrame::OnSave(wxCommandEvent &) {
  for (size_t idx = 0; idx < m_todos.size(); ++idx) {
    Todo &t = m_todos[idx];
    if (t.id == m_curTodo) {
      t.title = m_todoPanel->GetTitle();
      t.desc = m_todoPanel->GetDesc();
      m_dao->update_todo(t);
      m_todoPanel->SetTodo(t);
      break;
    }
  }

  ResetList();
}

void MyFrame::OnToggleDone(wxCommandEvent &evt) {
  int id = m_curTodo;
  if (evt.GetEventType() == wxEVT_COMMAND_CHECKLISTBOX_TOGGLED) {
    id = m_todos[evt.GetInt()].id;
  }

  for (size_t idx = 0; idx < m_todos.size(); ++idx) {
    Todo &t = m_todos[idx];

    if (t.id == id) {
      t.done = !t.done;
      m_dao->update_todo(t);

      if (id == m_curTodo) {
        m_todoPanel->SetTodo(t);
      }
      m_listBox->Check(idx, t.done);
      break;
    }
  }
}

void MyFrame::OnToggleList(wxCommandEvent &) {
  if (m_splitter->IsSplit()) {
    m_splitter->Unsplit(m_panel_listbox);
  } else {
    m_splitter->SplitVertically(m_panel_listbox, m_todoPanel, 150);
    m_menu_file->Check(MyId::LIST, true);
  }
}

void MyFrame::OnTogglePanel(wxCommandEvent &) {
  if (m_splitter->IsSplit()) {
    m_splitter->Unsplit(m_todoPanel);
  } else {
    m_splitter->SplitVertically(m_panel_listbox, m_todoPanel, 150);
    m_menu_file->Check(MyId::PANEL, true);
  }
}

void MyFrame::OnUnsplit(wxSplitterEvent &evt) {
  if (evt.GetWindowBeingRemoved() == m_panel_listbox) {
    m_menu_file->Check(MyId::LIST, false);
    m_menu_file->Check(MyId::PANEL, true);
  } else {
    m_menu_file->Check(MyId::LIST, true);
    m_menu_file->Check(MyId::PANEL, false);
  }
}
