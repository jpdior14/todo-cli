#include "todo/app.hpp"
#include "todo/task_manager.hpp"
#include <iostream>
#include <vector>

namespace todo {

App::App(int argc, char* argv[]) {
	for (int i = 0; i < argc; i++) {
		args_.push_back(argv[i]);
	}
}

int App::run() {
	if (args_.size() < 2) {
		print_usage();
		return 1;
	}
	process_command();
	return 0;
}

void App::process_command() {
	const std::string& command = args_[1];

	if (command == "list") {
		do_list();
	} else if (command == "add") {
		do_add();
	} else if (command == "done") {
		do_done();
	} else if (command == "remove") {
		do_remove();
	} else {
		std::cerr << "ERROR: Unknown command '" << command << "'.\n";
		print_usage();
	}
}

void App::do_list() {
	auto tasks = TaskManager::load_tasks(filename_);
	std::cout << "ID	STATUS	TASK\n";
	std::cout << "--	------	----\n";
	for (size_t i = 0; i < tasks.size(); i++) {
		std::cout << (i + 1) << "	"
				<< "[" << (tasks[i].is_done() ? "x": " ") << "]	"
				<< tasks[i].get_description() << std::endl;
	}
}

void App::do_add() {
	if (args_.size() < 3) {
		std::cerr << "ERROR: 'add' command requires a task description.\n";
		return;
	}
	auto tasks = TaskManager::load_tasks(filename_);
	tasks.emplace_back(args_[2]);
	TaskManager::save_tasks(filename_, tasks);
	std::cout << "Task added.\n";
	do_list();
}

void App::do_done() {
	if (args_.size() != 3) {
		std::cerr << "ERROR: 'done' command requires an existing task.\n";
		return;
	}
	auto tasks = TaskManager::load_tasks(filename_);
	try {
		size_t task_id = std::stoul(args_[2]);
		if (task_id == 0 || task_id > tasks.size()) {
			std::cerr << "ERROR: Invalid task ID.\n";
			return;
		}
		tasks[task_id-1].mark_as_done();
		TaskManager::save_tasks(filename_, tasks);
		std::cout << "Task " << task_id << " marked as done.\n";
		do_list();
	} catch (const std::exception& e) {
		std::cerr << "ERROR: Invalid task ID. Please provide a number.\n";
	} catch (const std::out_of_range& e) {
		std::cerr << "ERROR: Task ID is too large.\n";
	}
}

void App::do_remove() {
	if (args_.size() < 3) {
		std::cerr << "ERROR: 'remove' command requires a task ID.\n";
		return;
	}
	auto tasks = TaskManager::load_tasks(filename_);
	try {
		size_t task_id = std::stoul(args_[2]);
		if (task_id == 0 || task_id > tasks.size()) {
			std::cerr << "ERROR: Invalid task ID.\n";
			return;
		}
		tasks.erase(tasks.begin() + (task_id - 1));
		TaskManager::save_tasks(filename_, tasks);
		std::cout << "Task " << task_id << "removed.\n";
		do_list();
	} catch(const std::exception& e) {
		std::cerr << "ERROR: Invalid task ID. Please provide a number.\n";
	}
}

void App::print_usage() {
	std::cerr << "Usage:\n";
	std::cerr << "	" << args_[0] << " list\n";
	std::cerr << "	" << args_[0] << " add \"<task description>\"\n";
	std::cerr << "	" << args_[0] << " done <task_id>\n";
	std::cerr << "	" << args_[0] << " remove <task_id>\n";
}

}
