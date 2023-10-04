#include "dao.h"

#include <iostream>

#include "sqlite3.h"

Dao::Dao() {
  valid = sqlite3_open("todos.sqlite", &m_db) == SQLITE_OK;
  if (!valid) std::cout << "Error db init: " << sqlite3_errmsg(m_db) << "\n";
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
  return exec(
      "create table if not exists todos("
      "id integer primary key asc,"
      "title text not null,"
      "desc text,"
      "done integer not null default 0,"
      "timestamp integer not null)");
}

bool Dao::insert_todo(Todo &t) {
  const char *sql =
      "insert into todos(title,desc,done,timestamp) values(?,?,0,unixepoch())";

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(m_db, sql, strlen(sql), &stmt, nullptr) != SQLITE_OK) {
    std::cout << "Error prepare insert: " << sqlite3_errmsg(m_db) << "\n";
    return false;
  }

  sqlite3_bind_text(stmt, 1, t.title.c_str(), t.title.length(), SQLITE_STATIC);
  if (t.desc.length() > 0)
    sqlite3_bind_text(stmt, 2, t.desc.c_str(), t.desc.length(), SQLITE_STATIC);
  else
    sqlite3_bind_null(stmt, 2);

  sqlite3_step(stmt);

  if (sqlite3_finalize(stmt) != SQLITE_OK) {
    std::cout << "Error step insert: " << sqlite3_errmsg(m_db) << "\n";
    return false;
  }

  t.id = sqlite3_last_insert_rowid(m_db);

  return true;
}

bool Dao::delete_todo(int id) {
  const char *sql = "delete from todos where id = ?";

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(m_db, sql, strlen(sql), &stmt, nullptr) != SQLITE_OK) {
    std::cout << "Error prepare delete: " << sqlite3_errmsg(m_db) << "\n";
    return false;
  }

  sqlite3_bind_int(stmt, 1, id);
  sqlite3_step(stmt);

  if (sqlite3_finalize(stmt) != SQLITE_OK) {
    std::cout << "Error step insert: " << sqlite3_errmsg(m_db) << "\n";
    return false;
  }

  return true;
}

wxVector<Todo> Dao::get_todos() {
  wxVector<Todo> vec;

  const char *sql = "select id, title, desc, done, timestamp from todos";

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(m_db, sql, strlen(sql), &stmt, nullptr) != SQLITE_OK) {
    std::cout << "Error prepare select: " << sqlite3_errmsg(m_db) << "\n";
    return false;
  }

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    Todo t;
    int idx = 0;
    t.id = sqlite3_column_int(stmt, idx++);
    t.title = sqlite3_column_text(stmt, idx++);
    t.desc = sqlite3_column_text(stmt, idx++);
    t.done = sqlite3_column_int(stmt, idx++);
    t.timestamp = sqlite3_column_int64(stmt, idx++);

    vec.push_back(t);
  }

  if (sqlite3_finalize(stmt) != SQLITE_OK) {
    std::cout << "Error step select: " << sqlite3_errmsg(m_db) << "\n";
    return false;
  }

  return vec;
}
