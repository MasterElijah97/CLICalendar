#ifndef SESSION_H
#define SESSION_H


#include <memory>
#include <vector>
#include <string>
#include <map>

#include "MD5.h"
#include "deal.h"
#include "day.h"
#include "task.h"
#include "note.h"

class Session { //Singleton
    public:
        static Session& instance();

        void setLoginAndPassword(std::string&, std::string&);
        void logIn(const std::string& login, const std::string& password);
        void logOut();

        void connectToServer();
        void disconnectFromServer();

        void getTasksFromServer();
        void getNotesFromServer();
        void getDaysFromServer();

        void connectToLocalBase();
        void syncWithLocalBase();
        void syncWithServerBase();
        void syncBases();

        void addTask(Task);
        void addNote(Note);
        void addDay(Day);

        void creatingTask();
        void creatingNote();
        void creatingDay();
        void creatingDeal();

        void getDataFromLocalBase();
        //getters

        //setters

    private:
        Session();
        Session(const Session&);
        Session(Session&&);
        Session& operator=(const Session&);
        Session& operator=(Session&&);

        std::string login_;
        std::string password_;

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

        std::unique_ptr<Connection> thisConnection_ = nullptr;
        std::shared_ptr<Database> localBase_ = nullptr;
        std::shared_ptr<Database> serverBase_ = nullptr;

        std::unordered_map<std::string, std::string> logindAndPassword; /*getfrombase*/

        //move to public
        
        std::variant<
            std::vector<Day>::iterator,
            std::vector<Note>::iterator,
            std::vector<Task>::iterator,
            std::vector<Deal>::iterator
        > getJoined() const;

        std::variant<
            std::vector<Day>::iterator,
            std::vector<Note>::iterator,
            std::vector<Task>::iterator,
            std::vector<Deal>::iterator
        > getCopyable() const;

        std::variant<
            std::vector<Day>::iterator,
            std::vector<Note>::iterator,
            std::vector<Task>::iterator,
            std::vector<Deal>::iterator
        > getMoveable() const;

        void setJoined(std::vector<Day>::iterator);
        void setJoined(std::vector<Deal>::iterator);
        void setJoined(std::vector<Task>::iterator);
        void setJoined(std::vector<Note>::iterator);

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
};

#endif // SESSION_H
