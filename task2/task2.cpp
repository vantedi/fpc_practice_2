//Задание 2
#include <iostream>
#include <omp.h>
#include <thread>

using namespace std;

const int array_size = 100000;

void merge(int* arr, int start, int middle, int end) {
    int left_size = middle - start + 1;
    int right_size = end - middle;

    int* left = new int[left_size];
    int* right = new int[right_size];

    for (int i = 0; i < left_size; ++i) {
        left[i] = arr[start + i];
    }
    for (int j = 0; j < right_size; ++j) {
        right[j] = arr[middle + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = start;

    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            ++i;
        }
        else {
            arr[k] = right[j];
            ++j;
        }
        ++k;
    }

    while (i < left_size) {
        arr[k] = left[i];
        ++i;
        ++k;
    }

    while (j < right_size) {
        arr[k] = right[j];
        ++j;
        ++k;
    }

    delete[] left;
    delete[] right;
}

void merge_sort(int* arr, int start, int end) {
    if (start < end) {
        int middle = (start + end) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            {
                merge_sort(arr, start, middle);
            }

#pragma omp section
            {
                merge_sort(arr, middle + 1, end);
            }
        }

        merge(arr, start, middle, end);
    }
}

int main() {

    setlocale(LC_ALL, "Russian");

    omp_set_num_threads(5);
    int num_threads = 5;

    int* array = new int[array_size];
    srand(time(0));
    for (int i = 0; i < array_size; ++i) {
        array[i] = rand() % 100;
    }

    double start_time = omp_get_wtime();
    merge_sort(array, 0, array_size - 1);
    double end_time = omp_get_wtime();

    /*for (int i = 0; i < array_size; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
    */
    cout << "Количество тредов: " << num_threads << endl;
    cout << "Время выполнения: " << round((end_time - start_time)*1000) << " миллисекунд" << endl;

    delete[] array;

    return 0;
}
