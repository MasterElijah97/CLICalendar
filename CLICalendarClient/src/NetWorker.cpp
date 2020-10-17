#include "NetWorker.h"

NetWorker::NetWorker(std::shared_ptr<Session> session) : s(io_service), resolver(io_service) {
    this->thisSession = session;
}

void NetWorker::setIp(std::string ip) {
    this->ip_to_connect = ip;
}

void NetWorker::setPort(std::string port) {
    this->port_to_connect = port;
}

void NetWorker::connect() {
    try {
        boost::asio::connect(this->s, this->resolver.resolve(ip_to_connect, port_to_connect));
        std::cout << "Connection established" << std::endl;
        this->isConnected = true;
    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
        std::cout << "Try:\n1.Check internet connection\n2.Check server" << std::endl;
        this->isConnected = false;
    }
}

void NetWorker::disconnect() {

    if (isConnected) {

        this->s.close(ec);
        if (ec) {
            std::cout << "Something went wrong with NetWorker" << std::endl;
            ec.clear();
        }

        std::cout << "Connection closed" << std::endl;

        this->isConnected = false;

    } else {
            std::cout << "There is no one connection established" << std::endl;
    }
}

void NetWorker::sendUser() {
    std::string tmp;
    try {

        tmp = "BeginUser";
        boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

        tmp = thisSession->user->login_; /* + '`' + thisSession->user->hashedPass_; */
        boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

        tmp = "EndUser";
        boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
        this->isConnected = false;
    }
}
void NetWorker::sendDeals() {
    auto deals = thisSession->localDb->get_all<Deal>();
    std::string tmp;
    try {
        tmp = "BeginDeals";
        boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

        for (auto &deal : deals) {
            tmp = deal.concatenate();
            boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        }

        tmp = "EndDeals";
        boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
        this->isConnected = false;
    }

}
void NetWorker::sendDays() {
    std::string tmp;
    try {
        tmp = "BeginDays";
        boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

        for (auto &day : thisSession->days_) {
            tmp = day.concatenate();
            boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        }

        tmp = "EndDays";
        boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
        this->isConnected = false;
    }
}
void NetWorker::sendTasks() {
    std::string tmp;
    try {
        tmp = "BeginTasks";
        boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

        for (auto &task : thisSession->tasks_) {
            tmp = task.concatenate();
            boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        }

        tmp = "EndTasks";
        boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
        this->isConnected = false;
    }
}
void NetWorker::sendNotes() {
    std::string tmp;
    try {
        tmp = "BeginNotes";
        boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

        for (auto &note : thisSession->notes_) {
            tmp = note.concatenate();
            boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        }

        tmp = "EndNotes";
        boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
        this->isConnected = false;
    }
}

void NetWorker::send() {
    if (isConnected) {
    std::string tmp;
    try {
        tmp = "Begin";
        boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()), ec);
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

        this->sendUser();
        this->sendTasks();
        this->sendNotes();
        this->sendDeals();
        this->sendDays();

        tmp = "End";
        boost::asio::write(this->s, boost::asio::buffer(tmp, tmp.length()), ec);
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
    }
    } else {
        std::cout << "You need to connect first" << std::endl;
    }
}
void NetWorker::receiveDeals() {
    std::string receiver;
    std::vector<Deal> dealsFromServer;
    while(!receiver.compare("EndDeals") != 0) {
        std::size_t reply_length = boost::asio::read(this->s, boost::asio::buffer(receiver));
        Deal deal;
        deal.deconcatenate(receiver);
        dealsFromServer.push_back(deal);
    }

    this->thisSession->localDb->remove_all<Deal>();

    for (auto &item : dealsFromServer){
        item.id_ = -1;
        auto insertedId = this->thisSession->localDb->insert(item);
        item.id_ = insertedId;
    }
}
void NetWorker::receiveDays() {
    std::string receiver;
    std::vector<Day> daysFromServer;
    while(!receiver.compare("EndDays") != 0) {
        std::size_t reply_length = boost::asio::read(this->s, boost::asio::buffer(receiver));
        Day day;
        day.deconcatenate(receiver);
        daysFromServer.push_back(day);
    }

    this->thisSession->localDb->remove_all<Day>();

    for (auto &item : daysFromServer){
        item.id_ = -1;
        auto insertedId = this->thisSession->localDb->insert(item);
        item.id_ = insertedId;

        for (auto &important : item.importants_) {
            important.id_ = -1;
            auto insertedId = this->thisSession->localDb->insert(important);
            important.id_ = insertedId;
        }
    }
}
void NetWorker::receiveTasks() {
    std::string receiver;
    std::vector<Task> tasksFromServer;
    while(!receiver.compare("EndTasks") != 0) {
        std::size_t reply_length = boost::asio::read(this->s, boost::asio::buffer(receiver));
        Task task;
        task.deconcatenate(receiver);
        tasksFromServer.push_back(task);
    }
    this->thisSession->localDb->remove_all<Task>();

    for (auto &item : tasksFromServer){
        item.id_ = -1;
        auto insertedId = this->thisSession->localDb->insert(item);
        item.id_ = insertedId;
    }
}
void NetWorker::receiveNotes() {
    std::string receiver;
    std::vector<Note> notesFromServer;
    while(!receiver.compare("EndNotes") != 0) {
        std::size_t reply_length = boost::asio::read(this->s, boost::asio::buffer(receiver));
        Note note;
        note.deconcatenate(receiver);
        notesFromServer.push_back(note);
    }
    this->thisSession->localDb->remove_all<Note>();

    for (auto &item : notesFromServer){
        item.id_ = -1;
        auto insertedId = this->thisSession->localDb->insert(item);
        item.id_ = insertedId;
    }
}
void NetWorker::receive() {
    std::string receiver;
    while(!receiver.compare("End")) {
        try {
            std::size_t reply_length = boost::asio::read(this->s, boost::asio::buffer(receiver));
            if (!receiver.compare("BeginDeals")) {
                this->receiveDeals();
            }
            else if(!receiver.compare("BeginDays")) {
                this->receiveDays();
            }
            else if(!receiver.compare("BeginTasks")) {
                this->receiveTasks();
            }
            else if(!receiver.compare("BeginNotes")) {
                this->receiveNotes();
            }
        } catch(std::exception& ex) {
            std::cout << "Something went wrong on receive" << std::endl;
        }
    }
}
void NetWorker::sync() {
    std::filesystem::create_directory("backup");
    std::string path = "backup/" + this->thisSession->databaseName;
    std::filesystem::copy_file(this->thisSession->databaseName, path, std::filesystem::copy_options::overwrite_existing);
    this->send();
    std::string receiver;
    std::size_t reply_length = boost::asio::read(this->s, boost::asio::buffer(receiver));
    if (!receiver.compare("Begin")) {
        this->receive();
    }
}
