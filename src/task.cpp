#include "todo/task.hpp"

namespace todo {

Task::Task(const std::string& description)
	: description_(description), done_(false) {
}

bool Task::is_done() const {
	return done_;
}

const std::string& Task::get_description() const {
	return description_;
}

void Task::mark_as_done() {
	done_ = true;
}

}
