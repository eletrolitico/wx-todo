#ifndef DAO_H
#define DAO_H

#include "todo.h"

extern "C" {
#include "sqlite3.h"
}

class Dao {
 public:
  Dao();
  ~Dao();
  bool valid;

  bool create_table();
  bool insert_todo(Todo &todo);
  bool update_todo(const Todo &todo);
  bool delete_todo(int id);
  wxVector<Todo> get_todos();

 private:
  sqlite3 *m_db;

  bool exec(const char *sql);
};

#endif  // DAO_H
