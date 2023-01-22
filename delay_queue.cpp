#include "delay_queue.h"
#include "domain.h"
#include <iostream>

void DelayQueue::pushTask(std::shared_ptr<Task> task) {
	std::lock_guard<std::mutex> lock(Q_MUTEX);
	std::cout << getCurrentDatetime() << " : "s << task->d_name << " - " << task->d_delay << " : "s << "created."s << std::endl;
	pushed_task_ = task;
}

bool DelayQueue::hasTask() const {
	if (ready_to_perform_queue_.empty())
		return false;

	return true;
}

void DelayQueue::handlePushedTask() {
	if (pushed_task_ == nullptr)
		return;

	std::this_thread::sleep_for(std::chrono::seconds(pushed_task_->d_delay));
	ready_to_perform_queue_.push(pushed_task_);
	pushed_task_ = nullptr;
}

std::shared_ptr<Task> DelayQueue::popTask() {
	std::shared_ptr<Task> buff_task = ready_to_perform_queue_.front();
	ready_to_perform_queue_.pop();
	return buff_task;
}