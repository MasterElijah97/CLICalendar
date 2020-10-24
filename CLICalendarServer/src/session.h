#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <filesystem>
#include <cstring>
#include <chrono>
#include <thread>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "../include/sqlite_orm.h"
#include "Task.h"
#include "Note.h"
#include "Important.h"
#include "Deal.h"
#include "Day.h"

using namespace sqlite_orm;
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

using Storage = decltype(initLocalDb(""));

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {

    public:
        session(tcp::socket);

        void start();

        std::string name;
        std::string databaseName;
        std::shared_ptr<Storage> localDb = nullptr;

        std::vector<Task> tasks_;
        std::vector<Note> notes_;
        std::vector<Deal> deals_;
        std::vector<Day> days_;

        void clearData();

        void makeBackup();

        void getDataFromLocalBase();

        void processData();

        void receive();
        void process();
        void send();

        void sendDeals();
        void sendDays();
        void sendTasks();
        void sendNotes();

        void receiveUser();
        void receiveDeals();
        void receiveDays();
        void receiveTasks();
        void receiveNotes();

        void processDeals();
        void processDays();
        void processTasks();
        void processNotes();

    private:
        tcp::socket socket_;

        enum { max_length = 1024 };
        char data_[max_length];

        void do_read();
};

#endif // SESSION_H
