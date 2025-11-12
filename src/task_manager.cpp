#include "todo/task_manager.hpp"
#include <fstream>
#include <sstream>

namespace todo {

std::vector<Task> TaskManager::load_tasks(const std::string& filename) {
	std::vector<Task> tasks;
	std::ifstream file(filename);

	if (!file.is_open()) {
		return tasks;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string status_str;
		std::string description;

		if (std::getline(ss, status_str, '|') && std::getline(ss, description)) {
			Task task(description);
			if (status_str == "1") {
				task.mark_as_done();
			}
			tasks.push_back(task);
		}
	}

	return tasks;
}

void TaskManager::save_tasks(const std::string& filename, const std::vector<Task>& tasks) {
	std::ofstream file(filename);

	for (const auto& task : tasks) {
		file << (task.is_done() ? "1" : "0") << "|" << task.get_description() << "\n";
	}
}

}
