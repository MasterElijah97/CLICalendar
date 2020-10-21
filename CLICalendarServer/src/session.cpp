#include "session.h"

using boost::asio::ip::tcp;
session::session(tcp::socket socket) : socket_(std::move(socket)) {}

void session::start() {
    this->do_read();
}

void session::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            if(!data_.compare("Begin")) {
                this->processData();
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

    while(!(!data_.compare("End"))) {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            if(!data_.compare("BeginUser")) {
                this->receiveUser();
                this->databaseName = this->name + ".sqlite";
                this->localDb = std::make_shared<Storage>(initLocalDb(std::string(this->databaseName)));
                this->localDb->sync_schema();
                this->makeBackup();
                this->deals_ = this->localDb->get_all<Deal>();
                this->days_  = this->localDb->get_all<Day> ();
                this->tasks_ = this->localDb->get_all<Task>();
                this->notes_ = this->localDb->get_all<Note>();
            }
            else if (!data_.compare("BeginTasks")) {
                this->receiveTasks();
            }
            else if (!data_.compare("BeginNotes")) {
                this->receiveNotes();
            }
            else if (!data_.compare("BeginDeals")) {
                this->receiveDeals();
            }
            else if (!data_.compare("BeginDays")) {
                this->receiveDays();
            }
          }
        });
    }
    this->process();
    this->send();


}

void session::receiveUser() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            while(!(!data_.compare("EndUser"))) {
                this->name = data_;
            }
          }
        });
}

void session::makeBackup() {
    std::filesystem::create_directory("backup");
    std::string path = "backup/" + this->databaseName;
    std::filesystem::copy_file(this->databaseName, path, std::filesystem::copy_options::overwrite_existing);
}

void session::receiveTasks() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            while(!(!data_.compare("EndTasks"))) {
                Task task;
                task.deconcatenate(data_);
                this->tasks_.push_back(task);
            }
          }
        });
}

void session::receiveNotes() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            while(!(!data_.compare("EndNotes"))) {
                Note note;
                note.deconcatenate(data_);
                this->notes_.push_back(note);
            }
          }
        });
}

void session::receiveDeals() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            while(!(!data_.compare("EndDeals"))) {
                Deal deal;
                deal.deconcatenate(data_);
                this->deals_.push_back(deal);
            }
          }
        });
}

void session::receiveDays() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            while(!(!data_.compare("EndDays"))) {
                Day day;
                day.deconcatenate(data_);
                this->days_.push_back(day);
            }
          }
        });
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
    this->processDeals();
    this->processDays();
    this->processTasks();
    this->processNotes();
}

void session::sendDeals() {
    std::string tmp;
    try {
        tmp = "BeginDeals";
        boost::asio::async_write(socket_, boost::asio::buffer(tmp, tmp.length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (ec)
          {
            std::cout << "Something went wrong while sending Deals" << std::endl;
          }
        });
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

        for (auto &deal : deals_) {
            tmp = deal.concatenate();
            boost::asio::async_write(socket_, boost::asio::buffer(tmp, tmp.length()),
            [this](boost::system::error_code ec, std::size_t /*length*/)
            {
                if (ec)
                {
                    std::cout << "Something went wrong while sending Deals" << std::endl;
                }
            });
            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        }

        tmp = "EndDeals";
        boost::asio::async_write(socket_, boost::asio::buffer(tmp, tmp.length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (ec)
          {
            std::cout << "Something went wrong while sending Deals" << std::endl;
          }
        });
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
    }
}
void session::sendDays() {
std::string tmp;
    try {
        tmp = "BeginDays";
        boost::asio::async_write(socket_, boost::asio::buffer(tmp, tmp.length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (ec)
          {
            std::cout << "Something went wrong while sending Days" << std::endl;
          }
        });
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

        for (auto &day : days_) {
            tmp = day.concatenate();
            boost::asio::async_write(socket_, boost::asio::buffer(tmp, tmp.length()),
            [this](boost::system::error_code ec, std::size_t /*length*/)
            {
                if (ec)
                {
                    std::cout << "Something went wrong while sending Days" << std::endl;
                }
            });
            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        }

        tmp = "EndDays";
        boost::asio::async_write(socket_, boost::asio::buffer(tmp, tmp.length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (ec)
          {
            std::cout << "Something went wrong while sending Days" << std::endl;
          }
        });
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
    }
}
void session::sendTasks() {
std::string tmp;
    try {
        tmp = "BeginTasks";
        boost::asio::async_write(socket_, boost::asio::buffer(tmp, tmp.length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (ec)
          {
            std::cout << "Something went wrong while sending Tasks" << std::endl;
          }
        });
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

        for (auto &task : tasks_) {
            tmp = task.concatenate();
            boost::asio::async_write(socket_, boost::asio::buffer(tmp, tmp.length()),
            [this](boost::system::error_code ec, std::size_t /*length*/)
            {
                if (ec)
                {
                    std::cout << "Something went wrong while sending Tasks" << std::endl;
                }
            });
            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        }

        tmp = "EndTasks";
        boost::asio::async_write(socket_, boost::asio::buffer(tmp, tmp.length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (ec)
          {
            std::cout << "Something went wrong while sending Tasks" << std::endl;
          }
        });
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
    }
}
void session::sendNotes() {
std::string tmp;
    try {
        tmp = "BeginNotes";
        boost::asio::async_write(socket_, boost::asio::buffer(tmp, tmp.length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (ec)
          {
            std::cout << "Something went wrong while sending Notes" << std::endl;
          }
        });
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));

        for (auto &note : notes_) {
            tmp = note.concatenate();
            boost::asio::async_write(socket_, boost::asio::buffer(tmp, tmp.length()),
            [this](boost::system::error_code ec, std::size_t /*length*/)
            {
                if (ec)
                {
                    std::cout << "Something went wrong while sending Notes" << std::endl;
                }
            });
            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        }

        tmp = "EndNotes";
        boost::asio::async_write(socket_, boost::asio::buffer(tmp, tmp.length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (ec)
          {
            std::cout << "Something went wrong while sending Notes" << std::endl;
          }
        });
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));


    } catch(std::exception& ex) {
        std::cout << "Something went wrong" << std::endl;
        std::cout << ex.what() << std::endl;
    }
}
void session::send() {
    this->sendDeals();
    this->sendDays();
    this->sendTasks();
    this->sendNotes();
}
