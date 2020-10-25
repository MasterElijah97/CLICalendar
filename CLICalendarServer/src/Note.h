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
        void updateVersion();
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

        //getters
        static std::size_t getNumberOfNotes();

        //setters
        void setLabel      (std::string);
        void setName       (std::string);
        void setDescription(std::string);
        void setAllFields  (std::string,
                            std::string,
                            std::string);

        //user's interface
        void show();
        void edit();

        //needed to communicate with server
        //json on minimal
        std::string concatenate();
        void deconcatenate(std::string);

        //members
        std::string label_;
        std::string name_;
        std::string description_;

    private:
        static std::size_t numberOfNotes;
};

bool operator==(const Note&, const Note&);

#endif // NOTE_H
