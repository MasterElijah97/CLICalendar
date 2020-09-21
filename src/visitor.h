#ifndef VISITOR_H
#define VISITOR_H

#include <variant>
#include <string>
#include <vector>
#include <iterator>

#include "deal.h"
#include "day.h"
#include "task.h"
#include "note.h"

struct JoinedLabelSetter {
	JoinedLabelSetter(std::string&&);

    std::string msg_;

    static void operator()(std::vector<Deal>::iterator);
    static void operator()(std::vector<Deal>::iterator);
};

struct JoinedNameSetter {
	JoinedNameSetter(std::string&&);

    std::string msg_;

	static void operator()(std::vector<Deal>::iterator);
    static void operator()(std::vector<Note>::iterator);
};

struct JoinedDescriptionSetter {
	JoinedDescriptionSetter(std::string&&);

    std::string msg_;
    
	static void operator()(std::vector<Deal>::iterator);
    static void operator()(std::vector<Task>::iterator);
    static void operator()(std::vector<Note>::iterator);
};

struct JoinedPrioritySetter {
	JoinedPrioritySetter(std::string&&)

    std::string msg_;

	static void operator()(std::vector<Deal>::iterator);
};

struct JoinedTimeSetter {
	JoinedTimeSetter(std::string&&)

    std::string msg_;

	static void operator()(std::vector<Deal>::iterator)

struct JoinedComplitedSetter {
	JoinedComplitedSetter(bool&&)

    bool msg_;
	static void operator()(std::vector<Task>::iterator)
}

struct JoinedDateSetter {
	JoinedDateSetter(std::string&&)

    std::string msg_;

	static void operator()(std::vector<Day>::iterator);
};

#endif // VISITOR_H
