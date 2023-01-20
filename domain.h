#pragma once
#include <string>
#include <ctime>
#include <mutex>
#pragma warning(disable : 4996)

inline std::mutex Q_MUTEX;

static inline std::string getCurrentDatetime() {
	std::time_t now = std::time(NULL);

	std::tm* time_info = std::localtime(&now);

	std::string cur_time = std::string(std::asctime(time_info));

	return { cur_time.begin(), cur_time.end() - 1 };
}

struct empty_queue :std::exception {
	const char* what() const throw() {
		return "empty queue";
	}
};