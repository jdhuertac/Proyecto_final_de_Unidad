# Comparación Empírica de Algoritmos de Ordenamiento (Selection Sort vs. Merge Sort)

## Descripción
Este repositorio contiene el código fuente, la ejecución experimental, los datos y el artículo científico correspondientes a la comparación empírica de dos algoritmos de ordenamiento en C++, evaluando su complejidad temporal, número de comparaciones, intercambios y profundidad de recursión bajo diversos patrones de entrada.

## Estructura del Repositorio
* **src/** : Contiene el código fuente en C++ de los algoritmos y la instrumentación del benchmark.
* **results/** : Archivos CSV con los datos crudos de las ejecuciones experimentales y gráficos generados.
* **docs/** : Documentación del proyecto, incluyendo el manuscrito del artículo científico (`manuscrito.pdf`).

## Algoritmos Seleccionados
* **Método Directo:** Selection Sort
* **Método Logarítmico:** Merge Sort

## Entorno de Pruebas
* **CPU:** AMD Ryzen 5 7520U with Radeon Graphics
* **RAM:** 16GB
* **Sistema Operativo:** Windows 
* **Compilador:** MSYS2 UCRT64 (g++)
* **Semilla utilizada:** 42 (con incremento dinámico por repetición)

## Cómo Compilar y Ejecutar
1. Clona el repositorio en tu equipo local.
2. Abre tu terminal en la carpeta raíz del proyecto y compila el archivo principal con optimización:
   ```bash
   g++ -O2 src/main.cpp -o benchmark
