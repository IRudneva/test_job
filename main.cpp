#include "delay_queue.h"
#include "priority_queue.h"
#include "domain.h"
#include <future>

void performingLoop(PriorityQueue& p_queue) {
	while (true) {
		if (!p_queue.hasPerformingTask()) // Если в очереди с приоритетом нет выполняемой сейчас задачи
			p_queue.tryPerformTask(); // Попытаться выполнить первую в очереди с приоритетом задачу
	}
}

void delayLoop(DelayQueue& d_queue, PriorityQueue& p_queue, std::shared_ptr<Task> task) {
	d_queue.pushTask(task); // Добавить все задания в свои отложенные очереди
	auto return_task_back_to_delay_queue = [&p_queue, &d_queue]()
	{ d_queue.pushTask(p_queue.getTask()); }; // Вернуть выполненное задание в очередь для данного «отложенного» задания
	while(true) {
		if (d_queue.hasTask()) // Если в отложенной очереди есть задание, готовое к выполнению, добавить его в очередь с приоритетом
			p_queue.pushTask(d_queue.popTask(), return_task_back_to_delay_queue);

		d_queue.handlePushedTask(); // Слип в отложенной очереди для только что добавленного задания
	}
}

int main() {
	DelayQueue queueD1;
	std::shared_ptr<Task> taskD1 = std::make_shared<Task>("taskD1"s, "queueD1"s, "taskS1"s, "queueS1"s, 10, 2, 1);
	DelayQueue queueD2;
	std::shared_ptr<Task> taskD2 = std::make_shared<Task>("taskD2"s, "queueD2"s, "taskS2"s, "queueS1"s, 10, 2, 2);
	DelayQueue queueD3;
	std::shared_ptr<Task> taskD3 = std::make_shared<Task>("taskD3"s, "queueD3"s, "taskS3"s, "queueS1"s, 10, 2, 1);

	PriorityQueue queueS1;

	std::future<void> f1= std::async(std::launch::async, [&queueS1, &queueD1, &taskD1] {return delayLoop( queueD1, queueS1, taskD1); });
	std::future<void> f2 = std::async(std::launch::async, [&queueS1, &queueD2, &taskD2] {return delayLoop(queueD2, queueS1, taskD2); });
	std::future<void> f3 = std::async(std::launch::async, [&queueS1, &queueD3, &taskD3] {return delayLoop(queueD3, queueS1, taskD3); });
	std::future<void> f4 = std::async(std::launch::async, [&queueS1, &queueD3, &taskD3] {return performingLoop(queueS1); });

	f4.get();

	f1.get();
	f2.get();
	f3.get();

	return 0;
}
