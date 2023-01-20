#pragma once
#include "task.h"
#include <queue>
#include <memory>

class PriorityQueue {
public:
	PriorityQueue() = default;

	void pushTask(const Task& task);

	void performTask() const;

	void completeTask();

	std::shared_ptr<Task> getTask() const;

	~PriorityQueue() = default;

private:
	std::priority_queue<Task> queue_;
};

