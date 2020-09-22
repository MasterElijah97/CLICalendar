#include "visitor.h"


JoinedLabelSetter::JoinedLabelSetter(std::string&& msg) {
    this->msg_ = std::move(msg);
}
void JoinedLabelSetter::operator()(std::vector<Deal>::iterator it) {
    it->setLabel(msg_);
}
void JoinedLabelSetter::operator()(std::vector<Deal>::iterator it) {
    it->setLabel(msg_);
}

JoinedNameSetter::JoinedNameSetter(std::string&& msg) {
    this->msg_ = std::move(msg);
}
void JoinedNameSetter::operator()(std::vector<Deal>::iterator it) {
    it->setName(msg_);
}
void JoinedNameSetter::operator()(std::vector<Note>::iterator it) {
    it->setName(msg_);
}

JoinedDescriptionSetter::JoinedDescriptionSetter(std::string&& msg) {
    this->msg_ = std::move(msg);
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
    this->msg_ = std::move(msg);
}
void JoinedPrioritySetter::operator()(std::vector<Deal>::iterator it) {
   	it->setPriority(msg_);
}

JoinedTimeSetter::JoinedTimeSetter(std::string&& msg) {
    this->msg_ = std::move(msg);
}
void JoinedTimeSetter::operator()(std::vector<Deal>::iterator it) {
    it->setTime(msg_);
}

JoinedComplitedSetter::JoinedComplitedSetter(bool&& msg) {
    this->msg_ = std::move(msg);
}
void JoinedComplitedSetter::operator()(std::vector<Task>::iterator it) {
   	it->setComplited(msg_);
}

JoinedDateSetter::JoinedDateSetter(std::string&& msg) {
	this->msg_ = std::move(msg);
}
void JoinedDateSetter::operator()(std::vector<Day>::iterator it) {
   	it->setDate(msg_);
}

CopyablePaster::CopyablePaster(Session& session) {
    this->session_ = session;
}
void CopyablePaster::operator()(std::vector<Day>::iterator copyable) {
    std::vector<Day>::iterator joined = session_.getJoined();

    this->session_.getDays().insert((joined + 1), copyable);
}
void CopyablePaster::operator()(std::vector<Deal>::iterator copyable) {
    std::vector<Deal>::iterator joined = session_.getJoined();

    this->session_.getJoined()->getDeals().insert((joined + 1), copyable);
}
void CopyablePaster::operator()(std::vector<Task>::iterator copyable) {
    std::vector<Task>::iterator joined = session_.getJoined();

    this->session_.getTasks().insert((joined + 1), copyable);
}
void CopyablePaster::operator()(std::vector<Note>::iterator copyable) {
    std::vector<Note>::iterator joined = session_.getJoined();

    this->session_.getNotes().insert((joined + 1), copyable);
}


JoinedDecrementAllower::JoinedDecrementAllower(Session& session) {
    this->session_ = session;
}
void JoinedDecrementAllower::operator()(std::vector<Day>::iterator it) {
    if (it != (session_.getDays().begin())) {
        session_.decrementJoined();
    }
}
void JoinedDecrementAllower::operator()(std::vector<Deal>::iterator it) {
    if (it != (session_.getDays().begin())) {
        session_.decrementJoined();
    }
}
void JoinedDecrementAllower::operator()(std::vector<Task>::iterator it) {
    if (it != (session_.getTasks().begin())) {
        session_.decrementJoined();
    }
}
void JoinedDecrementAllower::operator()(std::vector<Note>::iterator it) {
    if (it != (session_.getNotes().begin())) {
        session_.decrementJoined();
    }
}

JoinedIncrementAllower::JoinedIncrementAllower(Session& session) {
    this->session_ = session;
}
void JoinedIncrementAllower::operator()(std::vector<Day>::iterator it) {
    if ((it + 1) != (session_.getDays().end())) {
        session_.incrementJoined();
    }
}
void JoinedIncrementAllower::operator()(std::vector<Deal>::iterator it) {
    if ((it + 1) != (session_.getDays().end())) {
        session_.incrementJoined();
    }
}
void JoinedIncrementAllower::operator()(std::vector<Task>::iterator it) {
    if ((it + 1) != (session_.getTasks().end())) {
        session_.incrementJoined();
    }
}
void JoinedIncrementAllower::operator()(std::vector<Note>::iterator it) {
    if ((it + 1) != (session_.getNotes().end())) {
        session_.incrementJoined();
    }
}