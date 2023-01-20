#include "delay_queue.h"
#include "priority_queue.h"
#include "domain.h"
#include <future>
#include <iostream>

inline std::mutex R_MUTEX;

void runTaskLoop(PriorityQueue& queueS1, DelayQueue& queueD, const Task& task) {
	try {
		queueD.pushTask(task);                              // Вывести в консоль "< текущее время > : < имя «отложенного» задания > - < слип в «отложенном» задании > : created"
		while (true) {
			queueS1.pushTask(std::move(*queueD.popTask())); // Создать "простое" задание в очереди с приоритетом queueS1
			std::future<void> async_push;
			std::future<void> async_complete;
			{
				std::lock_guard<std::mutex> lock(R_MUTEX);  // Заблокировать мьютекс для всех потоков, кроме текущего
				queueS1.performTask();                      // Вывести в консоль "< текущее время > : < имя текущей очереди > : < имя «простого» задания > - < слип в «простом» задании > running..."

				async_push = std::async([&queueD, &queueS1] {return queueD.pushTask(std::move(*queueS1.getTask())); });
				async_complete = std::async([&queueS1] {return queueS1.completeTask(); });
				async_complete.wait();
			}	                  // Следующий поток начинает выполнять queueS1.performTask(); 
			                      //                                             И
			async_push.get();     // Текущий поток создаёт "отложенное" задание в соответствующей очереди, которым было создано текущее «простое» задание 
			                      //                                             И
			async_complete.get(); // Выводится в консоль в "< текущее время > : < имя текущей очереди > : < имя «простого» задания > - < слип в «простом» задании > complited."
		}
	}
	catch (empty_queue& ex) {
		std::cout << ex.what() << std::endl;
	}
}


int main() {
	DelayQueue queueD1;
	Task taskD1 = { "taskD1"s, "queueD1"s, "taskS1"s,"queueS1"s, 10, 2, 1 };
	DelayQueue queueD2;
	Task taskD2 = { "taskD2"s, "queueD2"s, "taskS2"s, "queueS1"s, 10,  2,  2 };
	DelayQueue queueD3;
	Task taskD3 = { "taskD3"s, "queueD3"s,"taskS3"s, "queueS1"s, 10, 2,  1 };

	PriorityQueue queueS1;

	std::thread tr1(runTaskLoop, std::ref(queueS1), std::ref(queueD1), std::ref(taskD1));

	std::thread tr2(runTaskLoop, std::ref(queueS1), std::ref(queueD2), std::ref(taskD2));

	std::thread tr3(runTaskLoop, std::ref(queueS1), std::ref(queueD3), std::ref(taskD3));

	tr1.join();
	tr2.join();
	tr3.join();

	return 0;
}
