//Задание 3
#include <iostream>
#include <omp.h>

using namespace std;

int main() {

    setlocale(LC_ALL, "Russian");

    omp_set_num_threads(5);

    int points = 1000000;
    int points_in_circle = 0;

    srand(time(NULL));

#pragma omp parallel for reduction(+:points_in_circle)
    for (int i = 0; i < points; i++) {
        double x = (double)rand() / RAND_MAX; 
        double y = (double)rand() / RAND_MAX; 

        if ((x - 0.5) * (x - 0.5) + (y - 0.5) * (y - 0.5) <= 0.25) {
            points_in_circle++;
        }
    }

    double pi = 4.0 * points_in_circle / points;

    cout << "Приближенное значение числа Пи: " << pi << endl;

    return 0;
}
