#ifndef TODO_H
#define TODO_H

#include <wx/wx.h>

typedef struct Todo {
  int id;
  wxString title;
  wxString desc;
  bool done;
  long long timestamp;
} Todo;

#endif // !TODO_H
