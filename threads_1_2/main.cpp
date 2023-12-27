#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <numeric>

void parallelVectorSum(const std::vector<int>& v1, const std::vector<int>& v2, int numThreads) {
    std::vector<std::thread> threads(numThreads);
    std::vector<int> result(v1.size());

    auto start = std::chrono::high_resolution_clock::now();

    int chunkSize = v1.size() / numThreads;
    int remainder = v1.size() % numThreads;

    int index = 0;
    for (int i = 0; i < numThreads; ++i) {
        int blockSize = (i < remainder) ? chunkSize + 1 : chunkSize;
        threads[i] = std::thread([i, blockSize, &v1, &v2, &result] {
            int start = i * blockSize;
            int end = start + blockSize;
            for (int j = start; j < end; ++j) {
                result[j] = v1[j] + v2[j];
            }
        });
    }

    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Время занятое " << numThreads << " потоками: " << elapsed.count() << " секунд" << std::endl;
}


int main() {
    std::vector<int> arraySizes = {1000, 10000, 100000, 1000000};
    std::vector<int> hardwareThreads = {2, 4, 8, 16};

    std::cout << "Количество аппаратных ядер: " << std::thread::hardware_concurrency() << "\n\n";

    for (auto size : arraySizes) {
        std::vector<int> vec1(size, 1);
        std::vector<int> vec2(size, 2);

        std::cout << "Размер массива: " << size << std::endl;


        for (int threads : hardwareThreads)
            parallelVectorSum(vec1, vec2, threads);

        std::cout << std::endl;
    }

    return 0;
}
