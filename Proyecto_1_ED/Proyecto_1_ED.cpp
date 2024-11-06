#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>

// Metodos prueba
void exampleMethod1() {
    Sleep(10);
}

void exampleMethod2() {
    Sleep(12);
}

void exampleMethod3() {
    Sleep(8);
}

//Se mide el tiempo en milisegundos
double measureTime(void(*func)()) {
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&start);
    func();
    QueryPerformanceCounter(&end);

    return static_cast<double>((end.QuadPart - start.QuadPart) * 1000.0) / frequency.QuadPart;
}

int main() {
    const int repetitions = 100;
    double timesMethod1[repetitions];  // Static arrays for storing times ]
    double timesMethod2[repetitions];
    double timesMethod3[repetitions];

    for (int i = 0; i < repetitions; ++i) {
        // Measure each method and store the time in its respective array
        timesMethod1[i] = measureTime(exampleMethod1);
        timesMethod2[i] = measureTime(exampleMethod2);
        timesMethod3[i] = measureTime(exampleMethod3);
    }

    // Se escribe en un .csv
    std::ofstream file("timing_comparison.csv");
    if (file.is_open()) {
        // Nombre de cada columna
        file << "Iteracion,Method1 (milisegundos),Method2 (milisegundos),Method3 (milisegundos)\n";

        for (int i = 0; i < repetitions; ++i) {
            file << (i + 1) << ","
                << timesMethod1[i] << ","
                << timesMethod2[i] << ","
                << timesMethod3[i] << "\n";
        }

        file.close();
        std::cout << "Tiempos guardados en el archivo timing_comparison.csv" << std::endl;
    }
    else {
        std::cerr << "Error para abrir el archivo" << std::endl;
    }

    return 0;
}