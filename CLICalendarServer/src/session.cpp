#include "session.h"

using boost::asio::ip::tcp;
session::session(tcp::socket socket) : socket_(std::move(socket)) {}

void session::start() {
    this->do_read();
}

void session::do_read() {

    auto self(shared_from_this());
    
    async_read(this->socket_, boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            if(strcmp(data_, "ba") == 0) {
                this->processData();
            } else {
                this->do_read();
            }
          }
        });
}

void session::processData() {
    while( strcmp(data_, "ea") != 0 ) {

        auto self(shared_from_this());
        read(this->socket_, boost::asio::buffer(data_));

            if(strcmp(data_, "bu") == 0) {
                std::cout << "receiveUser" << std::endl;
                this->receiveUser();
                this->getDataFromLocalBase();
            }
            else if (strcmp(data_, "bt") == 0) {
                std::cout << "receiveTasks" << std::endl;
                this->receiveTasks();
            }
            else if (strcmp(data_, "bn") == 0) {
                std::cout << "receiveNotes" << std::endl;
                this->receiveNotes();
            }
            else if (strcmp(data_, "bde") == 0) {
                std::cout << "receiveDeals" << std::endl;
                this->receiveDeals();
            }
            else if (strcmp(data_, "bda") == 0) {
                std::cout << "receiveDays" << std::endl;
                this->receiveDays();
            } else {
                std::cout << "Nothing matches" << std::endl;
                std::cout << data_ << std::endl;
                break;
            }
    } 

    this->process();
    this->send();
}

void session::receiveUser() {
    read(this->socket_, boost::asio::buffer(data_));

            while(strcmp(data_, "eu") != 0) {
                this->name = data_;
                this->clearData();
                read(this->socket_, boost::asio::buffer(data_));
            }

            this->clearData();
}

void session::makeBackup() {
    std::filesystem::create_directory("backup");
    std::string path = "backup/" + this->databaseName;
    std::filesystem::copy_file(this->databaseName, 
                                path, 
                                std::filesystem::copy_options::overwrite_existing);
}

void session::receiveTasks() {
    read(this->socket_, boost::asio::buffer(data_));
       
            while(strcmp(data_, "et") != 0) {
                Task task;
                task.deconcatenate(data_);
                this->tasks_.push_back(task);
                this->clearData();
                read(this->socket_, boost::asio::buffer(data_));
            }

            this->clearData();

}

void session::receiveNotes() {
    read(this->socket_, boost::asio::buffer(data_));

            while(strcmp(data_, "en") != 0) {
                Note note;
                note.deconcatenate(data_);
                this->notes_.push_back(note);
                this->clearData();
                read(this->socket_, boost::asio::buffer(data_));
            }

            this->clearData();
}

void session::receiveDeals() {
    read(this->socket_, boost::asio::buffer(data_));

            while(strcmp(data_, "ede") != 0) {
                Deal deal;
                deal.deconcatenate(data_);
                this->deals_.push_back(deal);
                this->clearData();
                read(this->socket_, boost::asio::buffer(data_));
            }

            this->clearData();
}

void session::receiveDays() {
    read(this->socket_, boost::asio::buffer(data_));

            while(strcmp(data_, "eda") != 0) {
                Day day;
                day.deconcatenate(data_);
                this->days_.push_back(day);
                this->clearData();
                read(this->socket_, boost::asio::buffer(data_));
            }

            this->clearData();
}

void session::processDays() {
    std::sort(days_.begin(), days_.end(), [](Day& a, Day& b) {
        if(a.date_.compare(b.date_) > 0) {
            return true;
        }
        else {
            return false;
        }
    });
    auto it = days_.begin();
    while (1) {
        it = std::adjacent_find(days_.begin(), days_.end(), [](Day& a, Day&b) {
            if (a.date_.compare(b.date_) == 0) {
                return true;
            } else {
                return false;
            }
        });

        if (it == days_.end()) {
            break;
        } else {
            if (it->version_ < (it+1)->version_) {
                days_.erase(it);
            } else {
                days_.erase(it+1);
            }
        }
    }

    std::sort(days_.begin(), days_.end(), [](Day& a, Day& b) {
        if(a.id_ > b.id_) {
            return true;
        }
        else {
            return false;
        }
    });

    this->localDb->remove_all<Day>();
    for (auto &day : days_) {
        day.id_ = -1;
        auto insertedId = this->localDb->insert(day);
        day.id_ = insertedId;

        for (auto &important : day.importants_) {
            important.id_ = -1;
            auto insertedId = this->localDb->insert(important);
            important.id_ = insertedId;
        }
    }
}

void session::processDeals() {
    std::sort(deals_.begin(), deals_.end(), [](Deal& a, Deal& b) {
        if(a.date_.compare(b.date_) > 0) {
            return true;
        }
        else {
            return false;
        }
    });
    auto it = deals_.begin();
    while (1) {
        it = std::adjacent_find(deals_.begin(), deals_.end(), [](Deal& a, Deal&b) {
            if (a.date_.compare(b.date_)               == 0 &&
                a.name_.compare(b.name_)               == 0 &&
                a.priority_.compare(b.priority_)       == 0 &&
                a.description_.compare(b.description_) == 0) {
                return true;
            } else {
                return false;
            }
        });
        if (it == deals_.end()) {
            break;
        } else {
            if (it->version_ < (it+1)->version_) {
                deals_.erase(it);
            } else {
                deals_.erase(it+1);
            }
        }
    }

    std::sort(deals_.begin(), deals_.end(), [](Deal& a, Deal& b) {
        if(a.id_ > b.id_) {
            return true;
        }
        else {
            return false;
        }
    });

    this->localDb->remove_all<Deal>();
    for (auto &deal : deals_) {
        deal.id_ = -1;
        auto insertedId = this->localDb->insert(deal);
        deal.id_ = insertedId;
    }
}

void session::processTasks() {
    std::sort(tasks_.begin(), tasks_.end(), [](Task& a, Task& b) {
        if(a.description_.compare(b.description_) > 0) {
            return true;
        }
        else {
            return false;
        }
    });
    auto it = tasks_.begin();
    while (1) {
        it = std::adjacent_find(tasks_.begin(), tasks_.end(), [](Task& a, Task&b) {
            if (a.description_.compare(b.description_) == 0) {
                return true;
            } else {
                return false;
            }
        });
        if (it == tasks_.end()) {
            break;
        } else {
            if (it->version_ < (it+1)->version_) {
                tasks_.erase(it);
            } else {
                tasks_.erase(it+1);
            }
        }
    }

    std::sort(tasks_.begin(), tasks_.end(), [](Task& a, Task& b) {
        if(a.id_ > b.id_) {
            return true;
        }
        else {
            return false;
        }
    });

    this->localDb->remove_all<Task>();
    for (auto &task : tasks_) {
        task.id_ = -1;
        auto insertedId = this->localDb->insert(task);
        task.id_ = insertedId;
    }
}

void session::processNotes() {
    std::sort(notes_.begin(), notes_.end(), [](Note& a, Note& b) {
        if(a.name_.compare(b.name_) > 0) {
            return true;
        }
        else {
            return false;
        }
    });

    auto it = notes_.begin();
    while (1) {
        it = std::adjacent_find(notes_.begin(), notes_.end(), [](Note& a, Note&b) {
            if (a.name_.compare(b.name_) == 0 &&
                a.label_.compare(b.label_)== 0) {
                return true;
            } else {
                return false;
            }
        });
        if (it == notes_.end()) {
            break;
        } else {
            if (it->version_ < (it+1)->version_) {
                notes_.erase(it);
            } else {
                notes_.erase(it+1);
            }
        }
    }

    std::sort(notes_.begin(), notes_.end(), [](Note& a, Note& b) {
        if(a.id_ > b.id_) {
            return true;
        }
        else {
            return false;
        }
    });

    this->localDb->remove_all<Note>();
    for (auto &note : notes_) {
        note.id_ = -1;
        auto insertedId = this->localDb->insert(note);
        note.id_ = insertedId;
    }
}

void session::process() {
    std::cout << "Processing" << std::endl;
    this->processDeals();
    this->processDays();
    this->processTasks();
    this->processNotes();
    std::cout << "End processing" << std::endl;
}

void session::sendDeals() {
    if(!deals_.empty()) {
        std::cout << "Sending deals" << std::endl;
        try {
            this->clearData();

            std::strncpy(data_, "bde", 4);
            boost::asio::write(socket_, boost::asio::buffer(data_, max_length));

            for (auto &deal : deals_) {
                this->clearData();
                std::strncpy(data_, deal.concatenate().c_str(), 1024);
                boost::asio::write(socket_, boost::asio::buffer(data_, max_length));
            }

            this->clearData();

            std::strncpy(data_, "ede", 4);
            boost::asio::write(socket_, boost::asio::buffer(data_, max_length));

        } catch(std::exception& ex) {
            std::cout << "Something went wrong" << std::endl;
            std::cout << ex.what() << std::endl;
        }
    }
}
void session::sendDays() {
    if(!days_.empty()) {
        std::cout << "Sending days" << std::endl;
        try {
            this->clearData();

            std::strncpy(data_, "bda", 4);
            boost::asio::write(socket_, boost::asio::buffer(data_, max_length));

            for (auto &day : days_) {
                this->clearData();
                std::strncpy(data_, day.concatenate().c_str(), 1024);
                boost::asio::write(socket_, boost::asio::buffer(data_, max_length));
            }

            this->clearData();
            std::strncpy(data_, "eda", 4);
            boost::asio::write(socket_, boost::asio::buffer(data_, max_length));

        } catch(std::exception& ex) {
            std::cout << "Something went wrong" << std::endl;
            std::cout << ex.what() << std::endl;
        }
    }
}
void session::sendTasks() {
    if(!tasks_.empty()) {
        std::cout << "Sending tasks" << std::endl;
        try {
            this->clearData();

            std::strncpy(data_, "bt", 3);
            boost::asio::write(socket_, boost::asio::buffer(data_, max_length));
        
            for (auto &task : tasks_) {
                this->clearData();

                std::strncpy(data_, task.concatenate().c_str(), 1024);
                boost::asio::write(socket_, boost::asio::buffer(data_, max_length));
            }

            this->clearData();

            std::strncpy(data_, "et", 3);
            boost::asio::write(socket_, boost::asio::buffer(data_, max_length));

        } catch(std::exception& ex) {
            std::cout << "Something went wrong" << std::endl;
            std::cout << ex.what() << std::endl;
        }
    }
}
void session::sendNotes() {
    if(!notes_.empty()) {
        std::cout << "Sending notes" << std::endl;
        try {
            this->clearData();

            std::strncpy(data_, "bn", 3);
            boost::asio::write(socket_, boost::asio::buffer(data_));

            for (auto &note : notes_) {
                this->clearData();
                std::strncpy(data_, note.concatenate().c_str(), note.concatenate().size());
                std::cout << data_ << std::endl;
                boost::asio::write(socket_, boost::asio::buffer(data_));
            }

            this->clearData();

            std::strncpy(data_, "en", 3);
            boost::asio::write(socket_, boost::asio::buffer(data_));

        } catch(std::exception& ex) {
            std::cout << "Something went wrong" << std::endl;
            std::cout << ex.what() << std::endl;
        }
    }
}
void session::send() {

    this->clearData(); 

    std::strncpy(data_, "ba", 3);
    boost::asio::write(socket_, boost::asio::buffer(data_));
   
    this->sendDeals();
    this->sendDays();
    this->sendTasks();
    this->sendNotes();

    this->clearData();

    std::strncpy(data_, "ea", 3);
    boost::asio::write(socket_, boost::asio::buffer(data_));
}

void session::clearData() {
    for (int i = 0; i < this->max_length; i++) {
        this->data_[i] = 0;
    }
}

void session::getDataFromLocalBase() {
    this->databaseName = this->name + ".sqlite";
    this->localDb = std::make_shared<Storage>(initLocalDb(std::string(this->databaseName)));
    this->localDb->sync_schema();

    this->makeBackup();

    this->deals_ = this->localDb->get_all<Deal>();
    this->days_  = this->localDb->get_all<Day> ();
    this->tasks_ = this->localDb->get_all<Task>();
    this->notes_ = this->localDb->get_all<Note>();
}