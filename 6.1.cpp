#include <iostream>
#include <thread>
#include <atomic>
#include <numeric>
#include <vector>
#include <algorithm>
#include <random>

template <typename Iterator, typename T>
void accumulate_block(Iterator first, Iterator last, T init, std::atomic<T>& result) {
    result += std::accumulate(first, last, init);
}

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    auto length = std::distance(first, last);
    auto num_workers = std::thread::hardware_concurrency();
    if (length < 32) {
        return std::accumulate(first, last, init);
    }
    auto size_per_worker = length / num_workers;
    std::vector<std::thread> threads;
    std::vector<T> results(num_workers - 1);
    std::atomic<T> main_result = init;
    for(auto i = 0u; i < num_workers - 1; i++) {
        auto beginning = std::next(first, i * size_per_worker);
        auto ending = std::next(first, (i + 1) * size_per_worker);
                threads.push_back(std::thread(accumulate_block<Iterator, T>,
                                      beginning, ending, 0, std::ref(main_result)));
    }

    main_result += std::accumulate(std::next(first, (num_workers - 1) * size_per_worker), last, 0);
    std::for_each(std::begin(threads),std::end(threads),std::mem_fn(&std::thread::join));

    return main_result;
}

int main() {
    std::vector<int> test_sequence(100);
    std::iota(test_sequence.begin(), test_sequence.end(), 0);
    for(auto &item:test_sequence) std::cout << item << ' ';
    std::cout << std::endl;
    auto result = parallel_accumulate(std::begin(test_sequence),
                                std::end(test_sequence), 0);
    std::cout << "Result is " << result << std::endl << std::endl;


    std::vector<int> random_seq(50);
    for(auto &item: random_seq){
        item = std::rand()%101;
        std::cout << item << ' ';
    }

    std::cout << std::endl;
    std::cout << "Result is "
              << parallel_accumulate(std::begin(random_seq),
                                     std::end(random_seq),
                                     0)
              << std::endl;
}
