# CLICalendar
* Simple client-server CLI Calendar with Tasks, Notes, Days (Deals and Importants as a part of Days) using SQLite3, MD5 and Boost.Asio
* Work in progress...

## Acknowledgments and references
Path "include" contains libraries of these authors and organizations

* sqlite_orm implementation: https://github.com/fnc12/sqlite_orm
* MD5        implementation: https://github.com/JackieTseng/md5

Also this app uses

* lncurses                     https://invisible-island.net/ncurses/
* boost libraries              https://https://www.boost.org/
* sqlite3 (used by sqlite_orm) https://www.sqlite.org/index.html

## How to install
NOTE: both server and client path include item classes (Important, Deal, Day, Task, Note) but they are different - server path contains cutted versions (without some methods)
1. First of all you need to install these packages:
* sqlite3
* libboost1.71-all-dev (or newer)
* libncurses5-dev (or newer)
* cmake 3.16.3 (or newer)

You can use apt package manager (example for Ubuntu):
```bash
sudo apt update
sudo apt install sqlite3
sudo apt install libboost1.71-all-dev
sudo apt install libncurses5-dev
sudo apt install cmake
```
2. Then create directory named "build" at CLICalendarClient (or CLICalendarServer). Cient and Server are built separately
3. Run from "build" directory
```bash
cmake .. && make
```
Or you can use another build system compatible with cmake (see cmake documentation)

## How to use
1. Open executable file
2. Write 'help'. It will show the list of supported commands
3. If you want to use synchronization give this app rights to create directories and copy files

## Description of the items you can use

### 1. Day
Consists of date, list of deals and list of importants
#### 1.1 Deal
Consists of name, description, label, priority and time frame
#### 1.2 Important
Consists of just string (you can use it to summarize deals in short form)

### 2. Task
Consists of description and boolean flag (Completed \ Uncompleted)

### 3. Note
Consists of name, description and label

	
