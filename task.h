#pragma once
#include <string>

using namespace std::string_literals;

struct Task {
	std::string d_name = ""s;
	std::string d_queue = ""s;
	std::string s_name = ""s;
	std::string s_queue = ""s;
	int d_delay = 0;
	int s_delay = 0;
	int s_priority = 0;
};

static inline bool operator< (const Task& lhs, const Task& rhs) {
	return lhs.s_priority > rhs.s_priority;
}