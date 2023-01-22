#pragma once
#include "task.h"
#include <queue>
#include <memory>

class DelayQueue {
public:
	DelayQueue() = default;

	void pushTask(std::shared_ptr<Task> task);

	bool hasTask() const;

	void handlePushedTask();

	std::shared_ptr<Task> popTask();

	~DelayQueue() = default;

private:
	std::shared_ptr<Task> pushed_task_;
	std::queue<std::shared_ptr<Task>> ready_to_perform_queue_;
};

