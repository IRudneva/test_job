#include "priority_queue.h"
#include "domain.h"
#include <iostream>
#include <mutex>

void PriorityQueue::pushTask(std::shared_ptr<Task> task, std::function<void()> callback) {
	std::lock_guard<std::mutex> lock(Q_MUTEX);
	queue_.push({ task, callback });
	std::cout << getCurrentDatetime() << " : "s << task->d_name << " - "s << task->d_delay << " : "s << "( "s << task->s_name << " : "s << task->s_queue << " )"s << " pushed."s << std::endl;
}

void PriorityQueue::tryPerformTask() {
	if (queue_.empty())
		return;
	{
		std::lock_guard<std::mutex> lock(Q_MUTEX);
		perform_task_ = queue_.top();
		queue_.pop();
		std::cout << getCurrentDatetime() << " : "s << perform_task_.task->s_queue << " : " << perform_task_.task->s_name << " - "s << perform_task_.task->s_delay << " running..."s << std::endl;
	}
	std::this_thread::sleep_for(std::chrono::seconds(perform_task_.task->s_delay));
	completeTask();
}

void PriorityQueue::completeTask() {
	perform_task_.callback();
	std::lock_guard<std::mutex> lock(Q_MUTEX);
	std::cout << getCurrentDatetime() << " : "s << perform_task_.task->s_queue << " : " << perform_task_.task->s_name << " - "s << perform_task_.task->s_delay << " completed."s << std::endl;
	perform_task_.task = nullptr;
	perform_task_.callback = nullptr;
}

std::shared_ptr<Task> PriorityQueue::getTask() const {
	return perform_task_.task;
}