# CLICalendar
* Simple client-server CLI Calendar with Tasks, Notes, Days (Deals and Importants as a part of Days) using SQLite3, MD5 and Boost.Asio
* Work in progress...

## Acknowledgments and references
Path "include" contains libraries of these authors and organizations

* sqlite_orm implementation: https://github.com/fnc12/sqlite_orm
* MD5        implementation: https://github.com/JackieTseng/md5

Also this app uses

* lncurses                   https://invisible-island.net/ncurses/
* boost libraries            https://https://www.boost.org/

## How to install
1. First of all you need to install these packages:
* sqlite3
* libboost1.71-dev
* libncurses5-dev

You can use apt package manager (example for Ubuntu):
```bash
sudo apt update
sudo apt install sqlite3
sudo apt install libboost1.71-dev
sudo apt install libncurses5-dev
```
2. Then create directory named "build" at CLICalendarClient (or CLICalendarServer)
Cient and Server are built separately
3. Run
```bash
cmake .. && make
```


