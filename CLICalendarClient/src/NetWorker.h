#ifndef NETWORKER_H
#define NETWORKER_H

#include <string>
#include <memory>
#include <exception>
#include <filesystem>
#include <cstring>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

#include "Session.h"

using boost::asio::ip::tcp;
class NetWorker : public boost::noncopyable {
    public:
        NetWorker() = delete;
        NetWorker(std::shared_ptr<Session>);

        void setIp(std::string);
        void setPort(std::string);

        void connect();
        void disconnect();

        void send();
        void receive();

        void sync();

        void clearData();

    private:

        void makeBackup();
        void sendUser();
        void sendDeals();
        void sendDays();
        void sendTasks();
        void sendNotes();

        void receiveDeals();
        void receiveDays();
        void receiveTasks();
        void receiveNotes();
        //This is not a net-session
        //It is user's session in app
        std::shared_ptr<Session> thisSession;
        //todo reading ip and port from config
        std::string ip_to_connect = "127.0.0.1";
        std::string port_to_connect = "2001";

        bool isConnected = false;
        enum { max_length = 1024 };
        char data_[max_length];

        boost::asio::io_service io_service;
        tcp::socket s;
        tcp::resolver resolver;
        boost::system::error_code ec;
};

#endif // NETWORKER_H
