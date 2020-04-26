
#include <iostream>
#include <limits>
#include <thread>
//#include <chrono>
//#include <sstream>

#include "producer.hpp"
#include "consumer.hpp"

int main(int argc, char* argv[])
{
    auto arguments = std::vector<std::string>{ argv + 1, argv + argc };

    constexpr size_t capacity = 10;

    using Task = QuadricEquation;
    using TaskPtr = std::unique_ptr<Task>;
    using TasksQueue = BlockingQueue<TaskPtr>;
    using TasksQueuePtr = std::shared_ptr<TasksQueue>;

    auto tasksQueue = std::make_shared<TasksQueue>(capacity);

    const auto n = std::thread::hardware_concurrency();
    //std::cout << n << " concurrent threads are supported.\n";

    auto threads = std::vector<std::thread>{};

    // push 1 producer
    threads.emplace_back(std::thread{ &Producer::run, Producer{ tasksQueue, std::move(arguments) } });

    // push at least 1 consumer 
    threads.emplace_back(std::thread{ &Consumer::run, Consumer{ tasksQueue } });

    // According to https://en.cppreference.com/w/cpp/thread/thread/hardware_concurrency
    // std::thread::hardware_concurrency returns number of concurrent threads supported.
    // If the value is not well defined or not computable, returns ​0​.
    if (n > 2)
    {
        for (unsigned int i = 0; i < n - 2; ++i)
        {
            threads.emplace_back(std::thread{ &Consumer::run, Consumer{ tasksQueue } });
        }
    }

    //std::chrono::time_point<std::chrono::system_clock> start, end;
    //std::cout << "waiting for threads to finish..." << std::endl;
    //start = std::chrono::system_clock::now();

    for (auto& thread : threads)
    {
        thread.join();
    }

    //end = std::chrono::system_clock::now();
    //std::chrono::duration<double> elapsed_seconds = end - start;
    //auto x = std::chrono::duration_cast<std::chrono::seconds>(elapsed_seconds);
    //std::cout <<"Spent time (s): " << std::to_string(x.count()) << std::endl;


	return 0;
}
