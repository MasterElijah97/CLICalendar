#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <variant>
#include <cstdlib>
#include <boost/asio.hpp>
#include <boost/core/noncopyable.hpp>
#include <ncurses.h>
#include <exception>
#include <chrono>
#include <thread>
#include <filesystem>

#include "include/sqlite_orm.h"
#include "src/SEPARATOR.h"
#include "src/split.h"
#include "src/Deal.h"
#include "src/Important.h"
#include "src/Task.h"
#include "src/Note.h"
#include "src/Day.h"

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

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket socket)
    : socket_(std::move(socket))
  {}

  void start()
  {
    do_read();
  }

    std::string name;
    std::string databaseName;
    std::shared_ptr<Storage> localDb = nullptr;

    std::vector<Task> tasks_;
    std::vector<Note> notes_;
    std::vector<Deal> deals_;
    std::vector<Day> days_;

    void makeBackup();

    void getDataFromLocalBase();

    void processData();

    void send();
    void receive();
    void process();

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
  void do_read()
  {
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

  void do_write(std::size_t length)
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            do_read();
          }
        });
  }

  enum { max_length = 1024 };
  std::string data_;
};

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
		if (it == days_.end()) {
			break;
		}

		it = std::adjacent_find(days_.begin(), days_.end(), [](Day& a, Day&b) {
			if (a.date_.compare(b.date_)) {
				return true;
			} else {
				return false;
			}
		});
		if (it->version_ < (it+1)->version_) {
            days_.erase(it);
        } else {
            days_.erase(it+1);
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
		if (it == deals_.end()) {
			break;
		}

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
		if (it->version_ < (it+1)->version_) {
            deals_.erase(it);
        } else {
            deals_.erase(it+1);
        }
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
		if (it == tasks_.end()) {
			break;
		}

		it = std::adjacent_find(tasks_.begin(), tasks_.end(), [](Task& a, Task&b) {
			if (a.description_.compare(b.description_)) {
				return true;
			} else {
				return false;
			}
		});
        if (it->version_ < (it+1)->version_) {
            tasks_.erase(it);
        } else {
            tasks_.erase(it+1);
        }
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
		if (it == notes_.end()) {
			break;
		}

		it = std::adjacent_find(notes_.begin(), notes_.end(), [](Note& a, Note&b) {
			if (a.name_.compare(b.name_) &&
				a.label_.compare(b.label_)) {
				return true;
			} else {
				return false;
			}
		});
        if (it->version_ < (it+1)->version_) {
            notes_.erase(it);
        } else {
            notes_.erase(it+1);
        }
	}
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
class server
{
public:
  server(boost::asio::io_service& io_service, short port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
      socket_(io_service)
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket_))->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
  tcp::socket socket_;
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    server s(io_service, std::atoi(argv[1]));

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
