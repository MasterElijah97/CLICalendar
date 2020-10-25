#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

#include "SEPARATOR.h"
#include "split.h"


class Note {
    public:
        //id as primary key in database
        int id_;
        //version is for comparison between same deals in local and server databases
        int version_;

        Note();
        Note(std::string,
             std::string,
             std::string);
        Note(const Note&);
        Note(Note&&);

        //operators
        friend bool operator==(const Note& left, const Note& right);
        Note& operator=(const Note&);
        Note& operator=(Note&&);

        //destructor
        ~Note();

        //needed to communicate with server
        //json on minimal
        std::string concatenate();
        void deconcatenate(std::string);

        //members
        std::string label_;
        std::string name_;
        std::string description_;
};

bool operator==(const Note&, const Note&);

#endif // NOTE_H
