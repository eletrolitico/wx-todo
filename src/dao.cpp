#include "dao.h"
#include <iostream>

Dao::Dao() {
  valid = sqlite3_open("todos.sqlite", &m_db) == SQLITE_OK;
  if (!valid)
    std::cout << "Error db init: " << sqlite3_errmsg(m_db) << "\n";
}

Dao::~Dao() { sqlite3_close(m_db); }

bool Dao::exec(const char *sql) {
  char *err;

  sqlite3_exec(m_db, sql, nullptr, nullptr, &err);
  if (err != nullptr) {
    std::cout << "Error during sqlite exec: " << err << "\n";
    sqlite3_free(err);
    return false;
  }

  return true;
}

bool Dao::create_table() {
  return exec("create table if not exists todos("
              "id integer primary key asc,"
              "title text not null,"
              "desc text,"
              "done integer not null default 0,"
              "timestamp integer not null)");
}
