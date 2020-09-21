#include "visitor.h"


JoinedLabelSetter::JoinedLabelSetter(std::string&& msg) {
    this->msg_ = msg;
}
void JoinedLabelSetter::operator()(std::vector<Deal>::iterator it) {
    it->setLabel(msg_);
}
void JoinedLabelSetter::operator()(std::vector<Deal>::iterator it) {
    it->setLabel(msg_);
}

JoinedNameSetter::JoinedNameSetter(std::string&& msg) {
    this->msg_ = msg;
}
void JoinedNameSetter::operator()(std::vector<Deal>::iterator it) {
    it->setName(msg_);
}
void JoinedNameSetter::operator()(std::vector<Note>::iterator it) {
    it->setName(msg_);
}

JoinedDescriptionSetter::JoinedDescriptionSetter(std::string&& msg) {
    this->msg_ = msg;
}
void JoinedDescriptionSetter::operator()(std::vector<Deal>::iterator it) {
    it->setDescription(msg_);
}
void JoinedDescriptionSetter::operator()(std::vector<Task>::iterator it) {
    it->setDescription(msg_);
}
void JoinedDescriptionSetter::operator()(std::vector<Note>::iterator it) {
    it->setDescription(msg_);
}

JoinedPrioritySetter::JoinedPrioritySetter(std::string&& msg) {
    this->msg_ = msg;
}
void JoinedPrioritySetter::operator()(std::vector<Deal>::iterator it) {
   	it->setPriority(msg_);
}

JoinedTimeSetter::JoinedTimeSetter(std::string&& msg) {
    this->msg_ = msg;
}
void JoinedTimeSetter::operator()(std::vector<Deal>::iterator it) {
    it->setTime(msg_);
}

JoinedComplitedSetter::JoinedComplitedSetter(bool&& msg) {
    this->msg_ = msg;
}
void JoinedComplitedSetter::operator()(std::vector<Task>::iterator it) {
   	it->setComplited(msg_);
}

JoinedDateSetter::JoinedDateSetter(std::string&& msg) {
	this->msg_ = msg;
}
void JoinedDateSetter::operator()(std::vector<Day>::iterator it) {
   	it->setDate(msg_);
}