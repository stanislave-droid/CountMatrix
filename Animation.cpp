#include "Animation.h"

void timeout() {
	std::this_thread::sleep_for(std::chrono::seconds(1));
};

void Animation::showProgress() {
	std::cout << "Progress: |";
	for (int i = 0; i < 10; i++) {
		timeout();
		std::cout << "-";
	}
	std::cout << "|" << std::endl;
	timeout();
};