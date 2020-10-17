#include <exception>
#include <boost/asio.hpp>
#include <iostream>

#include "include/sqlite_orm.h"

#include "src/SEPARATOR.h"
#include "src/split.h"
#include "src/Deal.h"
#include "src/Important.h"
#include "src/Task.h"
#include "src/Note.h"
#include "src/Day.h"

#include "src/session.h"
#include "src/server.h"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: CLICalendarServer <port>\n";
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
