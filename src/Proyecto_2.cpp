#include <iostream> //para imprimir en consola
#include <vector> //necesario para cambiar de tamaño a los arreglos con (n = 1.000, 10.000)
#include <chrono> //para calcular los milisegundos (ms) de ejecución de cada algoritmo
#include <algorithm> //para intercambiar la posición de dos números en el arreglo y voltear el arreglo en patron descendente
#include <random> //Para generar números aleatorios y configurar las semillas que exige el proyecto para la reproducibilidad de los resultados
#include <numeric> //Nos permite usar la función iota para generar arreglos ascendentes y descendentes de manera más eficiente
#include <fstream> //Para ejecutar las 30 repeticiones para cada tamaños del arreglo, para cada uno de los 5 patrones y guardar todo directamente en un archivo CSV.

using namespace std;

// Estructura para almacenar las métricas por cada ejecución
struct Metricas {
    double tiempo_ms = 0.0;
    unsigned long long comparaciones = 0;
    unsigned long long intercambios = 0;
    size_t max_profundidad_recursion = 0;
};

// Metodo de Selección (Método Directo)
Metricas selectionSort(vector<int>& arr) {
    Metricas m;
    m.max_profundidad_recursion = 0; // Algoritmo iterativo
    
    auto start = chrono::steady_clock::now();

    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; ++j) {
            m.comparaciones++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(arr[i], arr[min_idx]);
            m.intercambios++; // Cuenta el intercambio de elementos
        }
    }

    auto end = chrono::steady_clock::now();
    m.tiempo_ms = chrono::duration<double, milli>(end - start).count();

    return m;
}

// Mergesort (Método Logarítmico)
void merge(vector<int>& arr, int left, int mid, int right, Metricas& m) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        m.comparaciones++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        m.intercambios++; // Movimiento de elementos al fusionar
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        m.intercambios++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        m.intercambios++;
    }
}

void mergeSortRec(vector<int>& arr, int left, int right, Metricas& m, size_t profundidad_actual) {
    if (profundidad_actual > m.max_profundidad_recursion) {
        m.max_profundidad_recursion = profundidad_actual;
    }

    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortRec(arr, left, mid, m, profundidad_actual + 1);
        mergeSortRec(arr, mid + 1, right, m, profundidad_actual + 1);
        merge(arr, left, mid, right, m);
    }
}

Metricas mergeSort(vector<int>& arr) {
    Metricas m;
    if (arr.empty()) return m;

    auto start = chrono::steady_clock::now();
    mergeSortRec(arr, 0, static_cast<int>(arr.size()) - 1, m, 1);
    auto end = chrono::steady_clock::now();
    
    m.tiempo_ms = chrono::duration<double, milli>(end - start).count();
    return m;
}

// Generador de patrones de entrada
enum class Patron { Aleatorio, Ascendente, Descendente, CasiOrdenado, Duplicados };

string patronToString(Patron p) {
    switch (p) {
        case Patron::Aleatorio: return "Aleatorio";
        case Patron::Ascendente: return "Ascendente";
        case Patron::Descendente: return "Descendente";
        case Patron::CasiOrdenado: return "CasiOrdenado";
        case Patron::Duplicados: return "Duplicados";
    }
    return "Desconocido";
}

vector<int> generarDatos(size_t n, Patron patron, unsigned int semilla) {
    vector<int> arr(n);
    mt19937 rng(semilla); //para los numeros aleatorios y reproducibilidad de los resultados

    switch (patron) {
        case Patron::Aleatorio: {
            uniform_int_distribution<int> dist(1, 1000000);
            for (auto& x : arr) x = dist(rng);
            break;
        }
        case Patron::Ascendente: {
            iota(arr.begin(), arr.end(), 1);
            break;
        }
        case Patron::Descendente: {
            iota(arr.begin(), arr.end(), 1);
            reverse(arr.begin(), arr.end());
            break;
        }
        case Patron::CasiOrdenado: {
            iota(arr.begin(), arr.end(), 1);
            size_t cambios = n * 0.05; 
            uniform_int_distribution<size_t> dist(0, n - 1);
            for (size_t i = 0; i < cambios; ++i) {
                swap(arr[dist(rng)], arr[dist(rng)]);
            }
            break;
        }
        case Patron::Duplicados: {
            uniform_int_distribution<int> dist(1, 20); 
            for (auto& x : arr) x = dist(rng);
            break;
        }
    }
    return arr;
}

// Función principal (Automatización del Experimento)
int main() {
    ofstream archivo("resultados_experimento.csv");
    // Cabecera del CSV solicitada por la guía
    archivo << "algoritmo,n,patron,repeticion,tiempo_ms,comparaciones,intercambios,profundidad_recursion,semilla\n";

    vector<size_t> tamanios = {1000, 10000}; // Se puede agregar 100000 si se desea probar límites
    vector<Patron> patrones = {Patron::Aleatorio, Patron::Ascendente, Patron::Descendente, Patron::CasiOrdenado, Patron::Duplicados};
    int num_repeticiones = 30; 
    unsigned int semilla_base = 42;

    cout << "Iniciando experimentos automatizados...\n";

    int contador_semilla = 1;
    for (size_t n : tamanios) {
        for (Patron p : patrones) {
            for (int rep = 1; rep <= num_repeticiones; ++rep) {
                unsigned int semilla_actual = semilla_base + contador_semilla++;
                
                // Generar datos base idénticos
                vector<int> datos_base = generarDatos(n, p, semilla_actual);

                // Copia 1 para Selection Sort
                vector<int> datos_sel = datos_base;
                Metricas m_sel = selectionSort(datos_sel);
                archivo << "SelectionSort," << n << "," << patronToString(p) << "," << rep << ","
                        << m_sel.tiempo_ms << "," << m_sel.comparaciones << "," << m_sel.intercambios << ","
                        << m_sel.max_profundidad_recursion << "," << semilla_actual << "\n";

                // Copia 2 para Merge Sort
                vector<int> datos_merge = datos_base;
                Metricas m_merge = mergeSort(datos_merge);
                archivo << "MergeSort," << n << "," << patronToString(p) << "," << rep << ","
                        << m_merge.tiempo_ms << "," << m_merge.comparaciones << "," << m_merge.intercambios << ","
                        << m_merge.max_profundidad_recursion << "," << semilla_actual << "\n";
            }
        }
    }

    archivo.close();
    cout << "¡Experimentos finalizados con exito! Archivo 'resultados_experimento.csv' generado correctamente.\n";

    return 0;
}