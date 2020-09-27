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

#include "src/iversion.h"
#include "src/iuniqueid.h"

const std::string SEPARATOR(3, '&');

class Note : public IVersion, public IUniqueId {
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
        static std::size_t getNumberOfNotes() const;
        std::string getLabel() const;
        std::string getName() const;
        std::string getDescription() const;

        friend const std::size_t getNumberOfNotes();
        //setters
        void setLabel(base_t*, std::string);
        void setName(base_t*, std::string);
        void setDescription(base_t*, std::string);
        void setAllFields(base_t*, std::string,
                          std::string,
                          std::string);
        //clearing
        void clearName();
        void clearDescription();
        void clearLabel();
        //funcs
        void show();

        void edit(base_t*);

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
    return (left.getLabel() == right.getLabel()) &&
           (left.getName() == right.getName()) &&
           (left.getDescription() == right.getDescription()) &&
           (left.getVersion() == right.getVersion());
}

#endif // NOTE_H
