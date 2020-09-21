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
            template<class... Ts>
    friend  sqlite_orm::internal::storage_t<Ts...> make_storage(const std::string&, Ts...);
        //constructors
        Note() {
            label_ = "Buffer";
            name_ = "New Task";
            description_ = "New Task";

            numberOfNotes++;

        }

        Note(std::string name,
             std::string description = "New Note",
             std::string label = "Buffer") {
            label_ = label;
            name_ = name;
            description_ = description;

            numberOfNotes++;
        }


        Note(const Note& right) {
            label_ = right.getLabel();
            name_ = right.getName();
            description_ = right.getDescription();
            version_ = right.getVersion();
        }

        Note(Note&& right) {
            label_ = right.getLabel();
            name_ = right.getName();
            description_ = right.getDescription();
            version_ = right.getVersion();


            right.clearLabel();
            right.clearName();
            right.clearDescription();
        }
        //destructors
        ~Note() {
            numberOfNotes--;
        }
        //operators
        friend bool operator==(const Note& left, const Note& right);

        Note& operator=(const Note& other) {
            if (this == &other) {
                return *this;
            }
            label_ = other.getLabel();
            name_ = other.getName();
            description_ = other.getDescription();
            version_ = other.getVersion();

            return *this;
        }

        Note& operator=(Note&& right) {
            if (this == &right) {
                return *this;
            }
            label_ = right.getLabel();
            name_ = right.getName();
            description_ = right.getDescription();
            version_ = right.getVersion();

            right.clearLabel();
            right.clearName();
            right.clearDescription();

            return *this;
        }
        //getters
        std::string getLabel() const {
            return label_;
        }

        std::string getName() const {
            return name_;
        }

        std::string getDescription() const {
            return description_;
        }

        friend const std::size_t getNumberOfNotes();
        friend void Session::getDataFromLocalBase();
        //setters
        void setLabel(std::string label) {
            label_ = label;
            updateVersion();
        }

        void setName(std::string name) {
            name_ = name;
            updateVersion();
        }

        void setDescription(std::string description) {
            description_ = description;
            updateVersion();
        }

        void setAllFields(std::string name,
                          std::string description = "New Note",
                          std::string label = "Buffer") {
            name_ = name;
            description_ = description;
            label_ = label;
            updateVersion();
        }
        //clearing
        void clearName() {
            name_.clear();
        }

        void clearDescription() {
            description_.clear();
        }

        void clearLabel() {
            label_.clear();
        }
        //funcs
        void show() {
            std::cout << "#" << label_ << std::endl;
            std::cout << name_ << std::endl;
            std::cout << description_ << std::endl;
        }

        std::string concatenate() {
            return label_                    +SEPARATOR+
                   name_                     +SEPARATOR+
                   std::to_string(version_)  +SEPARATOR+
                   std::to_string(uniqueId_) +SEPARATOR+
                   description_;
        }

        void deconcatenate(const std::string& msg) {
            std::size_t counter = 0;
            std::size_t posBegin = 0;
            for (std::size_t i = 0; i != msg.size(); ++i) {
                if (msg.substr(i, i+SEPARATOR.size()-1) == SEPARATOR) {
                    if (counter == 0) {
                        counter++;
                        label_ = msg.substr(posBegin, i-1);
                        posBegin = i+SEPARATOR.size();
                    } else if (counter == 1) {
                        counter++;
                        name_ = msg.substr(posBegin, i-1);
                        posBegin = i+SEPARATOR.size();
                    } else if (counter == 2) {
                        counter++;
                        version_ = std::stoi(msg.substr(posBegin, i-1));
                        posBegin = i+SEPARATOR.size();
                    } else if (counter == 3) {
                        counter++;
                        uniqueId_ = std::stoi(msg.substr(posBegin, i-1));
                        posBegin = i+SEPARATOR.size();
                    }
                }
            }
            description_ = msg.substr(posBegin);
        }
    private:
        std::string label_;
        std::string name_;
        std::string description_;

        static std::size_t numberOfNotes;
};

std::size_t Note::numberOfNotes = 0;
const std::size_t getNumberOfNotes() {
            return Note::numberOfNotes;
}

bool operator==(const Note& left, const Note& right) {
    return (left.getLabel() == right.getLabel()) &&
           (left.getName() == right.getName()) &&
           (left.getDescription() == right.getDescription()) &&
           (left.getVersion() == right.getVersion());
}

#endif // NOTE_H
