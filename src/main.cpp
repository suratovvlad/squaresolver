
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
#include <sstream>

#include "producer.hpp"
#include "consumer.hpp"

int main(int argc, char* argv[])
{
    // Use some aliases for convinience
    using Task = QuadricEquation;
    using TaskPtr = std::unique_ptr<Task>;
    using TasksQueue = BlockingQueue<TaskPtr>;
    using TasksQueuePtr = std::shared_ptr<TasksQueue>;

    // Frankly I didn't find any recommendations about optimal capacity for Blocking Queue
    // but I think it should be tuned accoding to task requirements and execution environment.
    // I hope, 1000 is not overkill and enough for this programm
    constexpr size_t queueCapacity = 1000;

    // Use shared Blocking Queue between producer and concumers.
    // According to https://en.cppreference.com/w/cpp/memory/shared_ptr
    // All member functions (including copy constructor and copy assignment) can be called by 
    // multiple threads on different instances of shared_ptr without additional synchronization 
    // even if these instances are copies and share ownership of the same object.
    auto tasksQueue = std::make_shared<TasksQueue>(queueCapacity);

    // As explained here https://stackoverflow.com/a/3126400/8369974
    // we could have more threads than logical cpus, 
    // especially when task on the thread is not heavy.
    // In each specific case it should be tuned, 
    // but I hope 4x could be enough for this program
    const auto n = 4 * std::thread::hardware_concurrency();

    // Use vector for threads, but probably thread pull is better.
    auto threads = std::vector<std::thread>{};

    {
        // Copy arguments to vector, it would be moved to Producer
        auto arguments = std::vector<std::string>{ argv + 1, argv + argc };

        // push 1 producer
        threads.emplace_back(std::thread{ &Producer::run, Producer{ tasksQueue, std::move(arguments) } });
    }

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

    // Special code for measuring time, not needed in production
#if 0
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::cout << "waiting for threads to finish..." << std::endl;
    start = std::chrono::system_clock::now();
#endif //  0

    // Join all joinable threads
    for (auto& thread : threads)
    {
        if (thread.joinable())
            thread.join();
    }

    // Special code for measuring time, not needed in production
#if 0
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    auto x = std::chrono::duration_cast<std::chrono::seconds>(elapsed_seconds);
    std::cout <<"Spent time (s): " << std::to_string(x.count()) << std::endl;
#endif //  0

	return 0;
}
