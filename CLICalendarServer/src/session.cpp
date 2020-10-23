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
                std::cout << "Process data" << std::endl;
                std::cout << data_ << std::endl;
                this->processData();
            } else {
                this->do_read();
            }
          }
        });
}

void session::do_write(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(this->socket_, boost::asio::buffer(this->data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            this->do_read();
          }
        });
}

void session::processData() {
     while( strcmp(data_, "ea") != 0 ) {
        std::cout << "In while" << std::endl;
        auto self(shared_from_this());
        read(this->socket_, boost::asio::buffer(data_));
            std::cout << "In checker" << std::endl;
            std::cout  << data_ << std::endl;
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
                std::cout << "Name" << name << std::endl;
                for (int i = 0; i < max_length; i++) {
                    std::cout << data_[i];
                }
                std::cout << std::endl;
                this->name = data_;
                this->clearData();
                read(this->socket_, boost::asio::buffer(data_));
            }
            std::cout << data_ << std::endl;
            this->clearData();
}

void session::makeBackup() {
    std::filesystem::create_directory("backup");
    std::string path = "backup/" + this->databaseName;
    std::filesystem::copy_file(this->databaseName, path, std::filesystem::copy_options::overwrite_existing);
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
            std::cout << data_ << std::endl;
            this->clearData();

}

void session::receiveNotes() {
    read(this->socket_, boost::asio::buffer(data_));

            while(data_[0] != 'e' && data_[1] != 'n') {
                Note note;
                note.deconcatenate(data_);
                this->notes_.push_back(note);
                this->clearData();
                read(this->socket_, boost::asio::buffer(data_));
            }
            std::cout << data_ << std::endl;
            this->clearData();
}

void session::receiveDeals() {
    read(this->socket_, boost::asio::buffer(data_));
            while(data_[0] != 'e' && data_[1] != 'd' && data_[2] != 'e') {
                Deal deal;
                deal.deconcatenate(data_);
                this->deals_.push_back(deal);
                this->clearData();
            }
            std::cout << data_ << std::endl;
            this->clearData();
}

void session::receiveDays() {
    read(this->socket_, boost::asio::buffer(data_));
            while(data_[0] != 'e' && data_[1] != 'd' && data_[2] != 'a') {
                Day day;
                day.deconcatenate(data_);
                this->days_.push_back(day);
                this->clearData();
            }
            std::cout << data_ << std::endl;
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
			if (a.date_.compare(b.date_)) {
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
			if (a.date_.compare(b.date_)         &&
				a.name_.compare(b.name_)         &&
				a.priority_.compare(b.priority_) &&
				a.description_.compare(b.description_)) {
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
			if (a.description_.compare(b.description_)) {
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
			if (a.name_.compare(b.name_) &&
				a.label_.compare(b.label_)) {
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
}

void session::process() {
    std::cout << "In process" << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(3000));
    this->processDeals();
    std::this_thread::sleep_for(std::chrono::microseconds(3000));
    this->processDays();
    std::this_thread::sleep_for(std::chrono::microseconds(3000));
    this->processTasks();
    std::this_thread::sleep_for(std::chrono::microseconds(3000));
    this->processNotes();
    std::this_thread::sleep_for(std::chrono::microseconds(3000));
    std::cout << "End process" << std::endl;
}

void session::sendDeals() {
    if(!deals_.empty()) {
    try {
        this->clearData();
        std::strncpy(data_, "bde", 4);
        boost::asio::write(socket_, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::microseconds(3000));

        for (auto &deal : deals_) {
            this->clearData();
            std::strncpy(data_, deal.concatenate().c_str(), 1024);
            boost::asio::write(socket_, boost::asio::buffer(data_, max_length));
            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        }
        this->clearData();
        std::strncpy(data_, "ede", 4);
        boost::asio::write(socket_, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
    }
    }
}
void session::sendDays() {
    if(!days_.empty()) {
    try {
        this->clearData();
        std::strncpy(data_, "bda", 4);
        boost::asio::write(socket_, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

        for (auto &day : days_) {
            this->clearData();
            std::strncpy(data_, day.concatenate().c_str(), 1024);
            boost::asio::write(socket_, boost::asio::buffer(data_, max_length));
            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        }

        this->clearData();
        std::strncpy(data_, "eda", 4);
        boost::asio::write(socket_, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
    }
    }
}
void session::sendTasks() {
    if(!tasks_.empty()) {
    try {
        this->clearData();
        std::strncpy(data_, "bt", 3);
        boost::asio::write(socket_, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

        for (auto &task : tasks_) {
            this->clearData();
            std::strncpy(data_, task.concatenate().c_str(), 1024);
            //data_ = task.concatenate().c_str();
            boost::asio::write(socket_, boost::asio::buffer(data_, max_length));
            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        }

        this->clearData();
        std::strncpy(data_, "et", 3);
        boost::asio::write(socket_, boost::asio::buffer(data_, max_length));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
    }
    }
}
void session::sendNotes() {
    if(!notes_.empty()) {
    try {
        this->clearData();
        std::strncpy(data_, "bn", 3);
        boost::asio::write(socket_, boost::asio::buffer(data_));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        int i = 0;
        for (auto &note : notes_) {
            std::cout << i << std::endl;
            i++;
            this->clearData();
            std::strncpy(data_, note.concatenate().c_str(), note.concatenate().size());
            std::cout << data_ << std::endl;
            //data_ = note.concatenate().c_str();
            boost::asio::write(socket_, boost::asio::buffer(data_));
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }

        this->clearData();
        std::strncpy(data_, "en", 3);
        boost::asio::write(socket_, boost::asio::buffer(data_));
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
    }
    }
}
void session::send() {
    std::strncpy(data_, "ba", 3);
    boost::asio::write(socket_, boost::asio::buffer(data_));
    std::cout << "In send" << std::endl;
    std::this_thread::sleep_for(std::chrono::nanoseconds(5));
    this->sendDeals();
    std::this_thread::sleep_for(std::chrono::nanoseconds(5));
    this->sendDays();
    std::this_thread::sleep_for(std::chrono::nanoseconds(5));
    this->sendTasks();
    std::this_thread::sleep_for(std::chrono::nanoseconds(5));
    this->sendNotes();
    std::this_thread::sleep_for(std::chrono::nanoseconds(5));
    this->clearData();
    std::strncpy(data_, "ea", 3);
    boost::asio::write(socket_, boost::asio::buffer(data_));
    std::cout << "End send" << std::endl;
}

void session::clearData() {
    for (int i = 0; i < this->max_length; i++) {
        this->data_[i] = 0;
    }
}

void session::getDataFromLocalBase() {
    std::cout << "getDataFromLocalBase" << std::endl;
    this->databaseName = this->name + ".sqlite";
    this->localDb = std::make_shared<Storage>(initLocalDb(std::string(this->databaseName)));
    this->localDb->sync_schema();
    this->makeBackup();
    this->deals_ = this->localDb->get_all<Deal>();
    this->days_  = this->localDb->get_all<Day> ();
    this->tasks_ = this->localDb->get_all<Task>();
    this->notes_ = this->localDb->get_all<Note>();
    //std::cout << "Note: " << notes_[0].label_ << " " << notes_[0].name_ << " " << notes_[0].description_ << std::endl;
}