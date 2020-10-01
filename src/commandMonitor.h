#ifndef COMMANDMONITOR_H
#define COMMANDMONITOR_H

#include <string>
#include <iostream>

#include  "include/sqlite_orm.h"

#include "src/task.h"
#include "src/note.h"
#include "src/important.h"
#include "src/deal.h"
#include "src/day.h"

#include "src/session.h"
#include "src/visitor.h"

void clearConsole();
void commandMonitor(const std::string&,
                    const std::string&,
                    const int&);
#endif // COMMANDMONITOR_H
