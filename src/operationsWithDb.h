#ifndef OPERATIONSWITHDB_H
#define OPERATIONSWITHDB_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>

#include "src/sqlite_orm.h"
#include "src/deal.h"
#include "src/day.h"
#include "src/note.h"
#include "src/task.h"

//merging
void mergeDays(std::vector<Day>& fromDataBase, std::vector<Day>& fromProgram) {
    std::size_t sizeFromDataBase = fromDataBase.size();
    std::size_t sizeFromPogram = fromProgram.size();

    fromProgram.resize(sizeFromPogram + sizeFromDataBase);

    std::copy(fromDataBase.begin(), fromDataBase.end(),
                fromProgram.begin() + size);

    std::sort(fromProgram.begin(), fromProgram.end(),
        [](const T& first, const T& second) -> bool {
            return first.getDate() <= second.getDate();
        }
    );

    bool flag = true;
    std::vector<Day>::iterator fromWhere = fromProgram.begin();

    while(flag) {
        std::vector<Day>::iterator it =
        std::adjacent_find(fromWhere, fromProgram.end(),
            [](const Day& first, const Day& second) -> bool {
                return first.getDate() == second.getDate();
            }
        );

        if (it != fromProgram.end()) {
            if (it.getVersion() <= (it + 1).getVersion()) {
                fromProgram.erase(it);
                fromWhere = it;
            } else {
                fromProgram.erase(it + 1);
                fromWhere = it + 1;
            }
            flag = false;
        } else {
            flag = true;
        }
    }
}

void mergeTasks(std::vector<Task>& fromDataBase, std::vector<Task>& fromProgram) {
    std::size_t sizeFromDataBase = fromDataBase.size();
    std::size_t sizeFromPogram = fromProgram.size();

    fromProgram.resize(sizeFromPogram + sizeFromDataBase);

    std::copy(fromDataBase.begin(), fromDataBase.end(),
                fromProgram.begin() + size);

    std::sort(fromProgram.begin(), fromProgram.end(),
        [](const Task& first, const Task& second) -> bool {
            return *(first.getDescription()).begin() < *(second.getDescription()).begin();
        }
    );

    bool flag = true;
    std::vector<Task>::iterator fromWhere = fromProgram.begin();

    while(flag) {
        std::vector<Task>::iterator it =
        std::adjacent_find(fromWhere, fromProgram.end(),
            [](const Task& first, const Task& second) -> bool {
                return first.getDescription() == second.getDescription();
            }
        );

        if (it != fromProgram.end()) {
            if (it.getVersion() <= (it + 1).getVersion()) {
                fromProgram.erase(it);
                fromWhere = it;
            } else {
                fromProgram.erase(it + 1);
                fromWhere = it + 1;
            }
            flag = false;
        } else {
            flag = true;
        }
    }
}

void mergeNotes(std::vector<Note>& fromDataBase, std::vector<Note>& fromProgram) {
    std::size_t sizeFromDataBase = fromDataBase.size();
    std::size_t sizeFromPogram = fromProgram.size();

    fromProgram.resize(sizeFromPogram + sizeFromDataBase);

    std::copy(fromDataBase.begin(), fromDataBase.end(),
                fromProgram.begin() + size);

    std::sort(fromProgram.begin(), fromProgram.end(),
        [](const Task& first, const Task& second) -> bool {
            return *(first.getName()).begin() < *(second.getName()).begin();
        }
    );

    bool flag = true;
    std::vector<Note>::iterator fromWhere = fromProgram.begin();

    while(flag) {
        std::vector<Note>::iterator it =
        std::adjacent_find(fromWhere, fromProgram.end(),
            [](const Note& first, const Note& second) -> bool {
                return first.getName() == second.getName();
            }
        );

        if (it != fromProgram.end()) {
            if (it.getVersion() <= (it + 1).getVersion()) {
                fromProgram.erase(it);
                fromWhere = it;
            } else {
                fromProgram.erase(it + 1);
                fromWhere = it + 1;
            }
            flag = false;
        } else {
            flag = true;
        }
    }
}

template<typename T>
find inLocalBase
find inServerBase
erase fromLocal
erase fromServer
insert toLocal
insert toServer

#endif // OPERATIONSWITHDB_H
