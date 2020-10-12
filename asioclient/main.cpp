//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{
  try
  {
    /*if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }*/

    std::string ip = "127.0.0.1";
    std::string port = "2001";

    boost::asio::io_service io_service;

    tcp::socket s(io_service);
    tcp::resolver resolver(io_service);
    boost::system::error_code ec;
    boost::asio::connect(s, resolver.resolve({ip, port}), ec);
    std::cout << ec.message() << ec.failed() << std::endl;
    ec.clear();

    while(1) {
    /*Использовать для отсылки серверу*/
        std::cout << "Enter message: ";
        char request[max_length];
        std::cin.getline(request, max_length);
        size_t request_length = std::strlen(request);
        boost::asio::write(s, boost::asio::buffer(request, request_length), ec);
        std::cout << ec.message() << ec.failed() << std::endl;
        ec.clear();
    /*Использовать для приёма от сервера*/
        char reply[max_length];
        size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply, request_length), ec);
        std::cout << ec.message() << ec.failed() << std::endl;
        ec.clear();
        std::cout << "Reply is: ";
        std::cout.write(reply, reply_length);
        std::cout << "\n";
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
