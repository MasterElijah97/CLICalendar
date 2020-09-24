#ifndef BLACK_MAGIC
#define BLACK_MAGIC

#include "src/sqlite_orm.h"

#include "src/deal.h"
#include "src/day.h"
#include "src/task.h"
#include "src/note.h"

/* WARNING!!!
 * For educational purposes only!!!
 * Never do this way  in serious projects
 */

using base_t = sqlite_orm::internal::storage_t<sqlite_orm::internal::table_t<
                Day, sqlite_orm::internal::column_t<Day, int, const int& (Day::*)
                () const, void (Day::*)(int), sqlite_orm::constraints::autoincrement_t,
                sqlite_orm::constraints::primary_key_t<> >, sqlite_orm::internal::column_t<
                Day, std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >, const std::__cxx11::basic_string<char,
                std::char_traits<char>, std::allocator<char> >& (Day::*)() const, void
                (Day::*)(std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >)> >, sqlite_orm::internal::table_t<Important,
                sqlite_orm::internal::column_t<Important, int, const int& (Important::*)()
                const, void (Important::*)(int), sqlite_orm::constraints::autoincrement_t,
                sqlite_orm::constraints::primary_key_t<> >, sqlite_orm::internal::column_t<
                Important, std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >, const std::__cxx11::basic_string<char,
                std::char_traits<char>, std::allocator<char> >& (Important::*)()
                const, void (Important::*)(std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >)> >, sqlite_orm::internal::table_t<Deal,
                sqlite_orm::internal::column_t<Deal, int, const int& (Deal::*)()
                const, void (Deal::*)(int), sqlite_orm::constraints::autoincrement_t,
                sqlite_orm::constraints::primary_key_t<> >, sqlite_orm::internal::column_t<Deal,
                std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >,
                const std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&
                (Deal::*)() const, void (Deal::*)(std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >)>, sqlite_orm::internal::column_t<Deal, std::__cxx11::basic_string<char,
                std::char_traits<char>, std::allocator<char> >, const std::__cxx11::basic_string<char,
                std::char_traits<char>, std::allocator<char> >& (Deal::*)() const, void (Deal::*)
                (std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)>,
                sqlite_orm::internal::column_t<Deal, std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >, const std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >& (Deal::*)() const, void (Deal::*)(std::__cxx11::basic_string<char,
                std::char_traits<char>, std::allocator<char> >)>, sqlite_orm::internal::column_t<
                Deal, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >,
                const std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&
                (Deal::*)() const, void (Deal::*)(std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >)>, sqlite_orm::internal::column_t<Deal, std::__cxx11::basic_string<char,
                std::char_traits<char>, std::allocator<char> >, const std::__cxx11::basic_string<char,
                std::char_traits<char>, std::allocator<char> >& (Deal::*)() const, void (Deal::*)
                (std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)>,
                sqlite_orm::internal::column_t<Deal::Time, std::__cxx11::basic_string<char,
                std::char_traits<char>, std::allocator<char> >, const std::__cxx11::basic_string<char,
                std::char_traits<char>, std::allocator<char> >& (Deal::Time::*)() const, void (Deal::Time::*)
                (std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)>,
                sqlite_orm::internal::column_t<Deal::Time, std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >, const std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >& (Deal::Time::*)() const, void (Deal::Time::*)
                (std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)> >,
                sqlite_orm::internal::table_t<Task, sqlite_orm::internal::column_t<Task, int, const int&
                (Task::*)() const, void (Task::*)(int), sqlite_orm::constraints::autoincrement_t,
                sqlite_orm::constraints::primary_key_t<> >, sqlite_orm::internal::column_t<Task, bool, const bool&
                (Task::*)() const, void (Task::*)(bool)>, sqlite_orm::internal::column_t<Task,
                std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >,
                const std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >& (Task::*)
                () const, void (Task::*)(std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >)> >, sqlite_orm::internal::table_t<Note, sqlite_orm::internal::column_t<
                Note, int, const int& (Note::*)() const, void (Note::*)(int), sqlite_orm::constraints::autoincrement_t,
                sqlite_orm::constraints::primary_key_t<> >, sqlite_orm::internal::column_t<Note,
                std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >,
                const std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&
                (Note::*)() const, void (Note::*)(std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >)>, sqlite_orm::internal::column_t<Note, std::__cxx11::basic_string<char,
                std::char_traits<char>, std::allocator<char> >, const std::__cxx11::basic_string<char,
                std::char_traits<char>, std::allocator<char> >& (Note::*)() const, void (Note::*)
                (std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)>,
                sqlite_orm::internal::column_t<Note, std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >, const std::__cxx11::basic_string<char, std::char_traits<char>,
                std::allocator<char> >& (Note::*)() const, void (Note::*)(std::__cxx11::basic_string<char,
                std::char_traits<char>, std::allocator<char> >)> > >;

#endif // BLACK_MAGIC
