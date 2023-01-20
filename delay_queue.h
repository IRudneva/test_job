#pragma once
#include "task.h"
#include <queue>
#include <memory>

class DelayQueue {
public:
	DelayQueue() = default;

	void pushTask(const Task& task);

	std::shared_ptr<Task> popTask();

	~DelayQueue() = default;

private:
	std::queue<Task> queue_;
};

