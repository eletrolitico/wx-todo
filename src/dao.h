#ifndef DAO_H
#define DAO_H

extern "C" {
#include "sqlite3.h"
}

class Dao {
public:
  Dao();
  ~Dao();
  bool valid;

  bool create_table();

private:
  sqlite3 *m_db;

  bool exec(const char *sql);
};

#endif // DAO_H
