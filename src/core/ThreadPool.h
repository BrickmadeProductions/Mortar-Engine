#pragma once

#include "Utils.h"

namespace MortarCore
{
    class ThreadPool {
        public:
            ThreadPool(size_t numThreads);
            ~ThreadPool();
        
            // Submit a task to the thread pool
            template <typename Func>
            void Submit(Func&& task);
        
            // Wait for all tasks to finish
            void Wait();
        
            // Stop the thread pool
            void Stop();
    
            uint32_t GetThreadCount() { return (uint32_t)workers.size(); }
        
        private:
            // Worker thread function
            void Worker();
        
            // Queue of tasks
            std::queue<std::function<void()>> tasks;
        
            // Synchronization objects
            std::mutex queueMutex;
            std::condition_variable condition;

        
            // List of worker threads
            std::vector<std::thread> workers;
        
            // Atomic flag to stop threads gracefully
            std::atomic<bool> stop;
    
            std::atomic<size_t> activeThreads;
        };

        template <typename Func>
        void ThreadPool::Submit(Func&& task)
        {
            if (stop.load(std::memory_order_acquire)) {
                std::cerr << "Error: Cannot submit task after stopping the thread pool." << std::endl;
                return;
            }

            {
                std::unique_lock<std::mutex> lock(queueMutex);
                tasks.push(std::forward<Func>(task));  // Add task to the queue
            }
            condition.notify_one();  // Notify one worker thread that a task is available
        }
            
}
