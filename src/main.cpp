#include "todo/task_manager.hpp" // Include our new manager
#include <iostream>
#include <vector>

int main() {
	const std::string filename = "tasks.txt";

	// --- PROOF OF SAVE ---
	std::cout << "Creating initial tasks and saving to file...\n";
	std::vector<todo::Task> my_tasks;
	my_tasks.emplace_back("Task 1: Learn vectors"); // emplace_>
	my_tasks.emplace_back("Task 2: Learn file I/O");
	my_tasks[1].mark_as_done(); // Mark the second task as done

	todo::TaskManager::save_tasks(filename, my_tasks);
	std::cout << "Saved.\n\n";


	// --- PROOF OF LOAD ---
	std::cout << "Loading tasks from file...\n";
	std::vector<todo::Task> loaded_tasks = todo::TaskManager::load_tasks(filename);

	std::cout << "Loaded " << loaded_tasks.size() << " tasks:\n";
	for (const auto& task : loaded_tasks) {
		std::cout << "- [" << (task.is_done() ? "x" : " ") << "] "
			<< task.get_description() << std::endl;
	}

	return 0;
}
