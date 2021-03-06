#ifndef SERVER_H
#define SERVER_H

#include "session.h"

class server
{
public:
  server(boost::asio::io_service&, short);

private:
  void do_accept();

  tcp::acceptor acceptor_;
  tcp::socket socket_;
};

#endif // SERVER_H
