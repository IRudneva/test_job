#pragma once
#include <string>
#include <functional>
#include <memory>

using namespace std::string_literals;

struct Task {
	Task(std::string dname, std::string dqueue, std::string sname, std::string squeue, int ddelay, int sdelay, int spriority)
		: d_name(dname), d_queue(dqueue), s_name(sname), s_queue(squeue), d_delay(ddelay), s_delay(sdelay), s_priority(spriority) {}
	std::string d_name = ""s;
	std::string d_queue = ""s;
	std::string s_name = ""s;
	std::string s_queue = ""s;
	int d_delay = 0;
	int s_delay = 0;
	int s_priority = 0;
};

struct PerformTask {
	std::shared_ptr<Task> task;
	std::function<void()> callback;
};

static inline bool operator <(const PerformTask& lhs, const PerformTask& rhs) {
	return lhs.task->s_priority > rhs.task->s_priority;
}