//Задание 1
#include <iostream>
#include <omp.h>
#include <thread>

using namespace std;

const int array_size = 10000;
const int threads_num = 5;
const int processor_count = thread::hardware_concurrency();

int main() {

    setlocale(LC_ALL, "Russian");

    int array1[5] = {7, 5, 4, 3, 2};
    //21

    int array[array_size];
    srand(time(0));
    for (int i = 0; i < array_size; ++i) {
        array[i] = rand() % 100;
    }

    int thread_sum1[threads_num] = {0};
    int thread_sum[threads_num] = {0};

#pragma omp parallel num_threads(threads_num)
    {

        int thread_id = omp_get_thread_num();

        if (thread_id == 0) {
            for (int i = 0; i < 5; ++i) {
                thread_sum1[thread_id] += array1[i];
            }
        }

        int part_size = array_size / threads_num;
        int start_index = thread_id * part_size;
        int end_index = (thread_id == threads_num - 1) ? array_size : start_index + part_size;

        for (int i = start_index; i < end_index; ++i) {
            thread_sum[thread_id] += array[i];
        }
    }

    int total_sum1 = 0;
    for (int i = 0; i < threads_num; ++i) {
        total_sum1 += thread_sum1[i];
    }

    int total_sum = 0;
    for (int i = 0; i < threads_num; ++i) {
        total_sum += thread_sum[i];
    }

    cout << "Количество потоков: " << threads_num;
    cout << "\nМассив 1: " << endl;
    cout << array1[0] << " ";
    cout << array1[1] << " ";
    cout << array1[2] << " ";
    cout << array1[3] << " ";
    cout << array1[4] << " ";
    cout << "\nОбщая сумма элементов массива 1: " << total_sum1 << endl;
    cout << "Общая сумма элементов массива: " << total_sum << endl;
    //cout << processor_count << endl;

    return 0;
}
