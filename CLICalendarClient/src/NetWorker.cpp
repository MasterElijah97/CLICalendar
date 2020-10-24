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
    try {
        this->clearData();
        std::strncpy(data_, "bu", 3);
        boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));

        this->clearData();
        std::strncpy(data_, thisSession->user->login_.c_str(), 1024);
        boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));

        this->clearData();
        std::strncpy(data_, "eu", 3);
        boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));


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
        this->clearData();
        std::strncpy(data_, "bde", 4);
        boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));

        for (auto &deal : deals) {
            this->clearData();
            std::strncpy(data_, deal.concatenate().c_str(), 1024);
            //data_ = deal.concatenate().c_str();
            boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
            std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
        }

        this->clearData();
        std::strncpy(data_, "ede", 4);
        boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
        this->isConnected = false;
    }

}
void NetWorker::sendDays() {
    try {
        this->clearData();
        std::strncpy(data_, "bda", 4);
        boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));

        for (auto &day : thisSession->days_) {
            this->clearData();
            std::strncpy(data_, day.concatenate().c_str(), 1024);
            boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
            std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
        }

        this->clearData();
        std::strncpy(data_, "eda", 4);
        boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
        this->isConnected = false;
    }
}
void NetWorker::sendTasks() {
    try {
        this->clearData();
        std::strncpy(data_, "bt", 3);
        boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));

        for (auto &task : thisSession->tasks_) {
            this->clearData();
            std::strncpy(data_, task.concatenate().c_str(), 1024);
            //data_ = task.concatenate().c_str();
            boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
            std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
        }

        this->clearData();
        std::strncpy(data_, "et", 3);
        boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
        this->isConnected = false;
    }
}
void NetWorker::sendNotes() {
    try {
        this->clearData();
        std::strncpy(data_, "bn", 3);
        boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));

        for (auto &note : thisSession->notes_) {
            this->clearData();
            std::strncpy(data_, note.concatenate().c_str(), max_length);
            //data_ = note.concatenate().c_str();
            boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
            std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
        }

        this->clearData();
        std::strncpy(data_, "en", 3);
        boost::asio::write(this->s, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
        this->isConnected = false;
    }
}

void NetWorker::send() {
    if (isConnected) {
    try {
        this->clearData();
        std::strncpy(data_, "ba", 3);
        //data_[0] = 'b';
        //data_[1] = 'a';
        boost::asio::write(this->s, boost::asio::buffer(data_, max_length), ec);
        std::cout << "Aaaaaand it's gone" << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(1000));

        this->sendUser();
        std::cout << "Aaaaaand it's gone2" << std::endl;
        this->sendTasks();
        std::cout << "Aaaaaand it's gone3" << std::endl;
        this->sendNotes();
        std::cout << "Aaaaaand it's gone4" << std::endl;
        this->sendDeals();
        std::cout << "Aaaaaand it's gone5" << std::endl;
        this->sendDays();
        std::cout << "Aaaaaand it's gone6" << std::endl;
        this->clearData();
        std::strncpy(data_, "ea", 3);
        boost::asio::write(this->s, boost::asio::buffer(data_, max_length), ec);
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));

    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
    }
    } else {
        std::cout << "You need to connect first" << std::endl;
    }
}
void NetWorker::receiveDeals() {
    this->clearData();
    this->thisSession->localDb->remove_all<Deal>();

    while(1) {

        boost::asio::read(this->s, boost::asio::buffer(data_));

        if (std::string(data_).find("ede") != std::string::npos) {
            break;
        }

        Deal deal;

        try {
            deal.deconcatenate(data_);
        } 
        catch (std::exception& ex) { 
            std::cout << "Wrong data: " << ex.what() << std::endl;
        }

        try {
            deal.id_ = -1;
            auto insertedId = this->thisSession->localDb->insert(deal);
            deal.id_ = insertedId;
            std::cout << insertedId << std::endl;
        } catch (std::exception& ex) { 
            std::cout << "Something went wrong with database" << ex.what() << std::endl; 
        }
        
        this->clearData();
    }
    //could be optimized by finding day by date_
    for (auto &day : this->thisSession->days_) {
        day.deals_ = this->thisSession->localDb->get_all<Deal>(where(is_equal(&Deal::date_, day.date_))); 
    }
}

void NetWorker::receiveDays() {
    this->clearData();
    this->thisSession->localDb->remove_all<Day>();
    this->thisSession->localDb->remove_all<Important>();

    while(1) {

        boost::asio::read(this->s, boost::asio::buffer(data_));

        if (std::string(data_).find("eda") != std::string::npos) {
            break;
        }

        Day day;

        try {
            day.deconcatenate(data_);
        } 
        catch (std::exception& ex) { 
            std::cout << "Wrong data: " << ex.what() << std::endl;
        }

        try {
            day.id_ = -1;
            auto insertedId = this->thisSession->localDb->insert(day);
            day.id_ = insertedId;
            std::cout << insertedId << std::endl;

            for (auto &important : day.importants_) {
                important.id_ = -1;
                auto insertedId = this->thisSession->localDb->insert(important);
                important.id_ = insertedId;
            }

        } catch (std::exception& ex) { 
            std::cout << "Something went wrong with database" << ex.what() << std::endl; 
        }

        this->clearData();
    }

    this->thisSession->days_ = this->thisSession->localDb->get_all<Day>(); 
}
void NetWorker::receiveTasks() {
    this->clearData();
    this->thisSession->localDb->remove_all<Task>();

    while(1) {

        boost::asio::read(this->s, boost::asio::buffer(data_));

        if (std::string(data_).find("et") != std::string::npos) {
            break;
        }

        Task task;

        try {
            task.deconcatenate(data_);
        } 
        catch (std::exception& ex) { 
            std::cout << "Wrong data: " << ex.what() << std::endl;
        }

        try {
            task.id_ = -1;
            auto insertedId = this->thisSession->localDb->insert(task);
            task.id_ = insertedId;
            std::cout << insertedId << std::endl;
        } catch (std::exception& ex) { 
            std::cout << "Something went wrong with database" << ex.what() << std::endl; 
        }
        
        this->clearData();
    }

    this->thisSession->tasks_ = this->thisSession->localDb->get_all<Task>(); 
}
void NetWorker::receiveNotes() {
    this->clearData();
    this->thisSession->localDb->remove_all<Note>();

    while(1) {

        boost::asio::read(this->s, boost::asio::buffer(data_));

        if (std::string(data_).find("en") != std::string::npos) {
            break;
        }

        Note note;

        try {
            note.deconcatenate(data_);
        } 
        catch (std::exception& ex) { 
            std::cout << "Wrong data: " << ex.what() << std::endl;
        }

        try {
            note.id_ = -1;
            auto insertedId = this->thisSession->localDb->insert(note);
            note.id_ = insertedId;
            std::cout << insertedId << std::endl;
        } catch (std::exception& ex) { 
            std::cout << "Something went wrong with database" << ex.what() << std::endl; 
        }

        this->clearData();
    }

    this->thisSession->notes_ = this->thisSession->localDb->get_all<Note>(); 
}
void NetWorker::receive() {
    std::cout << "In receive" << std::endl;
    this->clearData();
    //while(strcmp(data_, "ea") != 0) {
    while(1) {
        if (std::string(data_).find("ea") != std::string::npos) {
            break;
        }
        try {
            std::size_t reply_length = boost::asio::read(this->s, boost::asio::buffer(data_));
            if (strcmp(data_, "bde") == 0) {
                this->receiveDeals();
            }
            else if(strcmp(data_, "bda") == 0) {
                this->receiveDays();
            }
            else if(strcmp(data_, "bt") == 0) {
                this->receiveTasks();
            }
            else if(strcmp(data_, "bn") == 0) {
                this->receiveNotes();
            }
            else {
                std::cout << "Nothing matches" << std::endl;
                std::cout << data_ << std::endl;
            }
        } catch(std::exception& ex) {
            std::cout << "Something went wrong on receive" << std::endl;
            std::cout << ex.what() << std::endl;
        }
    }
}
void NetWorker::sync() {
    std::filesystem::create_directory("backup");
    std::string path = "backup/" + this->thisSession->databaseName;
    std::filesystem::copy_file(this->thisSession->databaseName, path, std::filesystem::copy_options::overwrite_existing);
    this->send();
    this->clearData();
    std::size_t reply_length = boost::asio::read(this->s, boost::asio::buffer(data_, max_length));
    std::cout << "Before receive" << std::endl;
    std::cout << data_ << std::endl;
    if (data_[0] == 'b' && data_[1] == 'a') {
        this->receive();
    }
}

void NetWorker::clearData() {
    for (int i = 0; i < this->max_length; i++) {
        this->data_[i] = 0;
    }
}