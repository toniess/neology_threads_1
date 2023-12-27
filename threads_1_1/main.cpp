#include <iostream>
#include <thread>
#include <chrono>


// функция прибавляет клиентов
void f1(int& line, int max) {
    while (true) {
        if (line < max)
            ++line;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Длина очереди: " << line << "\n";
    }
}


// функция обслуживает клиентов
void f2(int& line) {
    while (true) {
        if (line > 0)
            --line;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main()
{
    int line = 0;
    int maxLineCount = 10;
    std::cout << "Введите максимальное число людей в очереди: ";
    std::cin >> maxLineCount;
    std::thread t1(f1, std::ref(line), maxLineCount);
    std::thread t2(f2, std::ref(line));

    t1.join();
    t2.join();
    return 0;
}
