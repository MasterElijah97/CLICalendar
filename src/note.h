#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>

#include "include/sqlite_orm.h"

#include "src/black_magic.h"

#include "src/iversion.h"
#include "src/iuniqueid.h"
#include "src/idatabase.h"

class Note : public IVersion, public IUniqueId, public IDatabase {
    public:
        //constructors
        Note();
        Note(std::string,
             std::string,
             std::string);
        Note(const Note&);
        Note(Note&&);
        //destructors
        ~Note();
        //operators
        friend bool operator==(const Note& left, const Note& right);

        Note& operator=(const Note&);
        Note& operator=(Note&&);
        //getters
        static std::size_t getNumberOfNotes();
        
        //setters
        void setLabel(std::string);
        void setName(std::string);
        void setDescription(std::string);
        void setAllFields(std::string,
                          std::string,
                          std::string);
        //clearing
        void clearName();
        void clearDescription();
        void clearLabel();
        //funcs
        void show();

        void edit();

        std::string concatenate();
        void deconcatenate(const std::string&);

        std::string label_;
        std::string name_;
        std::string description_;

    private:
        static std::size_t numberOfNotes;
};

std::size_t Note::numberOfNotes = 0;


bool operator==(const Note& left, const Note& right) {
    return (left.label_ == right.label_) &&
           (left.name_ == right.name_) &&
           (left.description_ == right.description_) &&
           (left.version_ == right.version_);
}

#endif // NOTE_H
