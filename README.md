# Todo-CLI

A simple, brutal, command-line todo list manager written in C++.

## Features

- Add a new task to the todo list.
- List all tasks with their ID and status (pending/done).
- Mark a task as complete using its ID.
- The task list is persisted to a file named `tasks.txt` in the same directory.


## Usage

### 1. Add a Task
To add a new task, use the `add` command followed by the task description in quotes.

`./todo add "Learn how to write a README"`

### 2. List all Tasks

To see all tasks, use the `list` command.

`./todo list`

Example output:

### 3. Mark a Task as Done

To complete a task, use the `done` command followed by the task's ID.

`./todo done 1`

The list will now show:

## Data Storage

The application reads from and writes to a simple text file named `tasks.txt`. Each line in the file represents one task and will be stored in the format: `status|task_description`.

Example `tasks.txt` content:

(Where `0` is for pending and `1` is for done).
