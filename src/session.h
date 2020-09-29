#ifndef SESSION_H
#define SESSION_H


#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iterator>

#include "src/MD5.h"
#include "src/deal.h"
#include "src/day.h"
#include "src/task.h"
#include "src/note.h"
#include "src/user.h"
#include "src/black_magic.h"

class Session { //Singleton
    public:
        static Session& instance();

        User user;
        base_t* localDb;
        
        void addBasePtr(base_t&);
        
        std::vector<Task> tasks_;
        std::vector<Note> notes_;
        std::vector<Day> days_;

        std::variant
        <
        std::vector<Day>::iterator,
        std::vector<Note>::iterator,
        std::vector<Task>::iterator,
        std::vector<Deal>::iterator
        > joinedObject_;

        std::variant
        <
        std::vector<Day>::iterator,
        std::vector<Note>::iterator,
        std::vector<Task>::iterator,
        std::vector<Task>::iterator
        > copyableObject_;

        std::variant
        <
        std::vector<Day>::iterator,
        std::vector<Note>::iterator,
        std::vector<Task>::iterator,
        std::vector<Task>::iterator
        > moveableObject_;

        void addingNewUser();
        void setLoginAndPassword(std::string&, std::string&);
        void logIn();
        void logOut();

        void addTask(Task);
        void addNote(Note);
        void addDay(Day);

        void showJoined();
        void showHelp();

        void creatingTask();
        void creatingNote();
        void creatingDay();
        void creatingDeal();
        void creatingImportant();

        void getDataFromLocalBase();

        void setJoined(std::vector<Day>::iterator);
        void setJoined(std::vector<Deal>::iterator);
        void setJoined(std::vector<Task>::iterator);
        void setJoined(std::vector<Note>::iterator);

        void incrementJoined();
        void decrementJoined();

        void setMovable(std::vector<Day>::iterator);
        void setMovable(std::vector<Deal>::iterator);
        void setMovable(std::vector<Task>::iterator);
        void setMovable(std::vector<Note>::iterator);

        void setCopyable(std::vector<Day>::iterator);
        void setCopyable(std::vector<Deal>::iterator);
        void setCopyable(std::vector<Task>::iterator);
        void setCopyable(std::vector<Note>::iterator);

        void setJoinedLabel(const std::string);
        void setJoinedName(const std::string);
        void setJoinedDescription(const std::string);
        void setJoinedPriority(const std::string);

        void setJoinedTime(const std::string);
        void setJoinedComplited(const bool);
        void setJoinedDate(const std::string);

        void eraseDealFromJoined(int&);
        void eraseImportantFromJoined(int&);

        void eraseJoinedTask();
        void eraseJoinedNote();
        void eraseJoinedDay();

    private:
        Session();
        Session(const Session&) = delete;
        Session(Session&&) = delete;
        Session& operator=(const Session&) = delete;
        Session& operator=(Session&&) = delete;
};

#endif // SESSION_H
