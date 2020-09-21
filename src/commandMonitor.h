#ifndef COMMANDMONITOR_H
#define COMMANDMONITOR_H

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

void clearConsole();
void commandMonitor(const std::string&,
                    const std::string&,
                    const int&);
#endif // COMMANDMONITOR_H
