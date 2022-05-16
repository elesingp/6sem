#include <iostream>
#include <queue>
#include <mutex>
#include <thread>

template<typename T>
class ThreadSafeQueue {
    std::queue<T> queue;
    std::mutex mutex;
public:
    void Push(const T& elem) {
        std::lock_guard<std::mutex> mutex_(mutex);
        queue.push(elem);
    }
    void Push(T&& elem) {
        std::lock_guard<std::mutex> mutex_(mutex);
        queue.push(elem);
    }
    void Pop() {
        std::lock_guard<std::mutex> mutex_(mutex);
        queue.pop();
    }
    T Back() {
        std::lock_guard<std::mutex> mutex_(mutex);
        return queue.back();
    }
    T Front() {
        std::lock_guard<std::mutex> mutex_(mutex);
        return queue.front();
    }
    bool Empty() {
        std::lock_guard<std::mutex> mutex_(mutex);
        return queue.empty();
    }
    size_t Size() {
        std::lock_guard<std::mutex> mutex_(mutex);
        return queue.size();
    }
};

int main() {
    ThreadSafeQueue<int> queue;
    std::thread first([&]() {
        for (int i = 0; i < 10; ++i) {
            queue.Push(i);
        }
        std::cout << queue.Size() << std::endl;
        for (int i = 0; i < 10; ++i) {
            std::cout << queue.Back() << std::endl;
            queue.Pop();
        }
    });
    std::thread second([&]() {
        for (int i = 0; i < 10; ++i) {
            queue.Push(i);
        }
        std::cout << queue.Size() << std::endl;
        for (int i = 0; i < 10; ++i) {
            std::cout << queue.Front() << std::endl;
            queue.Pop();
        }
    });
    first.join();
    second.join();
    if (queue.Empty()) {
        std::cout << "All successful!" << std::endl;
    }
    else {
        std::cout << "All bad(" << std::endl;
    }
    return 0;
}