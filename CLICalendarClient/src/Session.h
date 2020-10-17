#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <memory>
#include <vector>
#include <iterator>
#include <variant>

#include "../include/sqlite_orm.h"

#include "User.h"

#include "Task.h"
#include "Note.h"
#include "Deal.h"
#include "Important.h"
#include "Day.h"
//--------------------------------------------------------------
// allows to use type of storage in future
//--------------------------------------------------------------
using namespace sqlite_orm;
inline auto initAccountsDb() {

    return make_storage("accounts.sqlite",
                                make_table("Accounts",
                                    make_column("id",
                                        &User::id_,
                                        autoincrement(),
                                        primary_key()),
                                    make_column("login",
                                        &User::login_),
                                    make_column("hashed_pass",
                                        &User::hashedPass_ )));
}

inline auto initLocalDb(const std::string &path) {

    return make_storage(path,
                                make_table("Days",

                                    make_column("id",
                                        &Day::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Day::version_),

                                    make_column("Date",
                                        &Day::date_)),

                                make_table("Importants",

                                    make_column("id",
                                        &Important::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Important::version_),

                                    make_column("Impportant",
                                        &Important::important_),

                                    make_column("Date",
                                        &Important::date_ )),

                                make_table("Deals",

                                    make_column("id",
                                        &Deal::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Deal::version_),

                                    make_column("Name",
                                        &Deal::name_),

                                    make_column("Description",
                                        &Deal::description_),

                                    make_column("Label",
                                        &Deal::label_),

                                    make_column("Priority",
                                        &Deal::priority_),

                                    make_column("Date",
                                        &Deal::date_),

                                    make_column("Begin",
                                        &Deal::begin_),

                                    make_column("End",
                                        &Deal::end_)),

                                make_table("Tasks",

                                    make_column("id",
                                        &Task::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Task::version_),

                                    make_column("IsCompleted",
                                        &Task::isCompleted_),

                                    make_column("Description",
                                        &Task::description_)),

                                make_table("Notes",

                                    make_column("id",
                                        &Note::id_,
                                        autoincrement(),
                                        primary_key()),

                                    make_column("Version",
                                        &Note::version_),

                                    make_column("Label",
                                        &Note::label_),

                                    make_column("Name",
                                        &Note::name_),

                                    make_column("Description",
                                        &Note::description_))
    );
}

using Accounts = decltype(initAccountsDb());
using Storage = decltype(initLocalDb(""));
//--------------------------------------------------------------

class Session {
public:
        Session(std::shared_ptr<User>);
        Session() = default;
        Session(const Session&) = default;
        Session(Session&&) = default;
        Session& operator=(const Session&) = default;
        Session& operator=(Session&&) = default;

        ~Session() = default;

        friend struct CommandChecker;

        std::shared_ptr<User> user = nullptr;

        std::string databaseName;
        std::shared_ptr<Storage> localDb = nullptr;

        std::vector<Task> tasks_;
        std::vector<Note> notes_;
        std::vector<Day> days_;

        enum variantObserver {
            NOT_SETTED = 0,
            DAY_SETTED = 1,
            NOTE_SETTED = 2,
            TASK_SETTED = 3,
            DEAL_SETTED = 4,
            IMPORTANT_SETTED= 5
        };

        std::variant
        <
        std::vector<Day>::iterator,
        std::vector<Note>::iterator,
        std::vector<Task>::iterator,
        std::vector<Deal>::iterator,
        std::vector<Important>::iterator
        > joinedObject_;

        variantObserver joinedSetted = NOT_SETTED;

        std::variant
        <
        std::vector<Day>::iterator,
        std::vector<Note>::iterator,
        std::vector<Task>::iterator,
        std::vector<Deal>::iterator,
        std::vector<Important>::iterator
        > copyableObject_;

        variantObserver copyableSetted = NOT_SETTED;

        std::variant
        <
        std::vector<Day>::iterator,
        std::vector<Note>::iterator,
        std::vector<Task>::iterator,
        std::vector<Deal>::iterator,
        std::vector<Important>::iterator
        > moveableObject_;

        variantObserver moveableSetted = NOT_SETTED;

        void addTask(Task);
        void addNote(Note);
        void addDay(Day);

        void openTasks();
        void openNotes();
        void openDays();

        void showJoined();
        void showHelp();

        void editDeal(const int&);
        void editImportant(const int&);
        void editItem();

        void copyItem();
        void pasteItem();
        void moveItem();
        void pasteMoveableItem();

        void removeTask();
        void removeNote();
        void removeDay();
        void removeDeal(const int&);
        void removeImportant(const int&);

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
        void setJoined(std::vector<Important>::iterator);

        void setMovable();
        void setCopyable();

        void incrementJoined();
        void decrementJoined();

    private: //visitors

struct JoinedEditor {

    JoinedEditor(Session&);
    Session* session;
    ~JoinedEditor();

    template<typename T>
    void operator()(T&);
};


struct JoinedShower {
    template<typename T>
    void operator()(T&);
};



struct MoveablePaster {

    MoveablePaster(Session&);
    Session* session;
    ~MoveablePaster();

	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	//not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Deal>::iterator& it){};
    void operator()(std::vector<Important>::iterator& it){};
};

struct CopyablePaster {

    CopyablePaster(Session&);
    Session* session;
    ~CopyablePaster();

	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	//not using
    //variant wants overloaded operator() for each type
    //so these are empty
    void operator()(std::vector<Deal>::iterator& it){};
    void operator()(std::vector<Important>::iterator& it){};
};

struct JoinedIncrementAllower {

    JoinedIncrementAllower(Session&);
    Session* session;
    ~JoinedIncrementAllower();

	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	//not using
    //variant wants overloaded operator() for each type
    //so these are empty
	void operator()(std::vector<Deal>::iterator& it){};
    void operator()(std::vector<Important>::iterator& it){};
};

struct JoinedDecrementAllower {

    JoinedDecrementAllower(Session&);
    Session* session;
    ~JoinedDecrementAllower();

	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	void operator()(std::vector<Deal>::iterator& it){};
    void operator()(std::vector<Important>::iterator& it){};
};

struct MoveableSetter {

	MoveableSetter(Session&);
	Session* session;
	~MoveableSetter();

	void operator()(std::vector<Deal>::iterator&);
	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	void operator()(std::vector<Important>::iterator&);
};

struct CopyableSetter {

    CopyableSetter(Session&);
    Session* session;
    ~CopyableSetter();

	void operator()(std::vector<Deal>::iterator&);
	void operator()(std::vector<Day>::iterator&);
	void operator()(std::vector<Task>::iterator&);
	void operator()(std::vector<Note>::iterator&);
	void operator()(std::vector<Important>::iterator&);
};
};

#endif // SESSION_H
