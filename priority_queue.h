#pragma once
#include "task.h"
#include <queue>

class PriorityQueue {
public:
	PriorityQueue() = default;

	void pushTask(std::shared_ptr<Task> task, std::function<void()> callback);

	bool hasPerformingTask() const { return perform_task_.task != nullptr; }

	void tryPerformTask();

	std::shared_ptr<Task> getTask() const;

	~PriorityQueue() = default;

private:
	PerformTask  perform_task_;
	std::priority_queue<PerformTask> queue_;

	void completeTask();
};

