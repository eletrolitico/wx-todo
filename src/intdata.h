#ifndef INT_DATA_H
#define INT_DATA_H

#include <iostream>
#include <wx/clntdata.h>

class myIntData : public wxClientData {
public:
  myIntData(){};
  myIntData(int data) : m_data(data) {}
  void SetData(int data) { m_data = data; }
  int GetData() const { return m_data; }

private:
  int m_data{0};
};

#endif
