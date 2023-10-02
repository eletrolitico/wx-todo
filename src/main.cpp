#include "dao.h"
#include "sqlite3.h"
#include <iostream>
#include <wx/wx.h>

extern "C" {
#include "myframe.h"
}

class MyApp : public wxApp {
public:
  bool OnInit() override;
  int OnExit() override;

private:
  Dao m_dao;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
  if (!m_dao.valid) {
    return false;
  }

  if (!m_dao.create_table()) {
    return false;
  }

  auto frame = new MyFrame(&m_dao);
  frame->Show(true);
  return true;
}

int MyApp::OnExit() { return 0; }
