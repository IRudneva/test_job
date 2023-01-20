#include "delay_queue.h"
#include "domain.h"
#include <iostream>

void DelayQueue::pushTask(const Task& task) {
	if (!queue_.empty())
	{
		queue_.pop();
	}
	queue_.push(task);
	{
		std::lock_guard<std::mutex> lock(Q_MUTEX);
		std::cout << getCurrentDatetime() << " : "s << task.d_name << " - " << task.d_delay << " : "s << "created."s << std::endl;
	}
	std::this_thread::sleep_for(std::chrono::seconds(task.d_delay));
}

std::shared_ptr<Task> DelayQueue::popTask() {
	if (queue_.empty())
	{
		throw empty_queue();
	}
	std::shared_ptr<Task> const buff_task(std::make_shared<Task>(queue_.front()));
	queue_.pop();
	return buff_task;
}