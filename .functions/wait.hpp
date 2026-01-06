#ifndef WAIT
#define WAIT
#include <thread>
#include <chrono>

static void wait(unsigned seconds) { std::this_thread::sleep_for(std::chrono::seconds(seconds)); }

#endif