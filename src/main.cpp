#include "todo/task.hpp"
#include <iostream>

int main() {
	todo::Task my_first_task("Learn C++ classes");

	std::cout << "Task: " << my_first_task.get_description() << std::endl;
	std::cout << "Status: " << (my_first_task.is_done() ? "Done" : "Pending") << std::endl;
	
	std::cout << "\n...marking task as done ...\n\n";
	my_first_task.mark_as_done();

	std::cout << "Task: " << my_first_task.get_description() << std::endl;
	std::cout << "Status: " << (my_first_task.is_done() ? "Done" : "Pending") << std::endl;

	return 0;
}
