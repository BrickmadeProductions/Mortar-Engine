#include "ThreadPool.h"

namespace MortarCore
{
    
    ThreadPool::ThreadPool(size_t numThreads) : stop(false), activeThreads(0) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.push_back(std::thread(&ThreadPool::Worker, this));
        }
    }
    
    ThreadPool::~ThreadPool() {
        //Stop();
    }

    void ThreadPool::Worker() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
    
                // Wait for tasks or stop signal
                condition.wait(lock, [this] { return stop.load() || !tasks.empty(); });
    
                // If stopping and no tasks left, exit the worker thread
                if (stop && tasks.empty()) return;
    
                // Get and remove the task from the queue
                task = std::move(tasks.front());
                tasks.pop();
            }
            activeThreads.fetch_add(1, std::memory_order_relaxed);

            // Execute the task
            task();

            activeThreads.fetch_sub(1, std::memory_order_relaxed);

            // Notify the wait condition
            waitCondition.notify_all();
        }
    }

    void ThreadPool::Wait() {
        std::unique_lock<std::mutex> lock(queueMutex);
        waitCondition.wait(lock, [this] { 
            return tasks.empty() && activeThreads.load() == 0; 
        });
    }

    void ThreadPool::Stop() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }

        // Notify all threads to stop
        condition.notify_all();

        // Wait for all threads to finish processing
        for (std::thread& worker : workers) {
            if (worker.joinable()) {
                worker.join();  // Join each thread to ensure completion
            }
        }
    }
    

}
