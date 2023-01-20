#include "priority_queue.h"
#include "domain.h"
#include <iostream>

void PriorityQueue::pushTask(const Task& task) {
	std::lock_guard<std::mutex> lock(Q_MUTEX);
	queue_.push(task);
	std::cout << getCurrentDatetime() << " : "s << task.d_name << " - "s << task.d_delay << " : "s << "( "s << task.s_name << " : "s << task.s_queue << " )"s << " pushed."s << std::endl;
}

void  PriorityQueue::performTask() const {
	if (queue_.empty())
	{
		throw empty_queue();
	}
	{
		std::lock_guard<std::mutex> lock(Q_MUTEX);
		std::cout << getCurrentDatetime() << " : "s << queue_.top().s_queue << " : " << queue_.top().s_name << " - "s << queue_.top().s_delay << " running..."s << std::endl;
	}
		std::this_thread::sleep_for(std::chrono::seconds(queue_.top().s_delay));
}

void  PriorityQueue::completeTask() {
	if (queue_.empty())
	{
		throw empty_queue();
	}

	std::lock_guard<std::mutex> lock(Q_MUTEX);
	std::cout << getCurrentDatetime() << " : "s << queue_.top().s_queue << " : " << queue_.top().s_name << " - "s << queue_.top().s_delay << " completed."s << std::endl;
	queue_.pop();
}

std::shared_ptr<Task>  PriorityQueue::getTask() const {
	if (queue_.empty())
	{
		throw empty_queue();
	}

	return std::make_shared<Task>(queue_.top());
}