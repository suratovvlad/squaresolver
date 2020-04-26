
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
#include <sstream>

#include "simpletaskgenerator.hpp"
#include "simpletaskconsumer.hpp"
#include "producer.hpp"
#include "consumer.hpp"

int main()
{
	//std::cout << "Hello CMake Solver." << std::endl;

//	int input = 0;
//	int count = 0;
//	int skippedCount = 0;
//
//	for (;;) {
//		std::cin >> input;
//
//		if (std::cin.eof() || std::cin.bad()) {
//			break;
//		}
//		else if (std::cin.fail()) {
//			++skippedCount;
//			std::cin.clear(); // unset failbit
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // skip bad input
//		}
//		else {
//			++count;
//			std::cout << input << std::endl;
//		}
//	}
//	std::cout << "\nEntered : " << count << "\nSkipped  : " << skippedCount;


    constexpr size_t capacity = 10;

    using Task = QuadricEquation;
    using TaskPtr = std::unique_ptr<Task>;
    using TasksQueue = BlockingQueue<TaskPtr>;
    using TasksQueuePtr = std::shared_ptr<TasksQueue>;

    auto tasksQueue = std::make_shared<TasksQueue>(capacity);

//    auto tasksQueue = std::make_shared<BlockingQueue<int>>(capacity);


    std::cout << "starting producer thread..." << std::endl;
    std::thread producerThread(&Producer::run, Producer{tasksQueue});

    std::cout << "starting consumer thread..." << std::endl;
    std::thread consumerThread(&Consumer::run, Consumer{tasksQueue});

//    std::cout << "starting consumer thread 2..." << std::endl;
//    std::thread consumerThread2(&SimpleTaskConsumer::run, SimpleTaskConsumer{tasksQueue});
//
//    std::cout << "starting consumer thread 3..." << std::endl;
//    std::thread consumerThread3(&SimpleTaskConsumer::run, SimpleTaskConsumer{tasksQueue});
//
//    std::cout << "starting consumer thread 3..." << std::endl;
//    std::thread consumerThread4(&SimpleTaskConsumer::run, SimpleTaskConsumer{tasksQueue});

    std::chrono::time_point<std::chrono::system_clock> start, end;


    std::cout << "waiting for threads to finish..." << std::endl;

    start = std::chrono::system_clock::now();

    producerThread.join();
    consumerThread.join();
//    consumerThread2.join();
//    consumerThread3.join();
//    consumerThread4.join();

    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    auto x = std::chrono::duration_cast<std::chrono::seconds>(elapsed_seconds);

    //to_string
    std::cout <<"Spent time (s): " << std::to_string(x.count()) << std::endl;


	return 0;
}
