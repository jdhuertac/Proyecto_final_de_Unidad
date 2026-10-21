# Proyecto_final_de_Unidad

## Descripción
Este repositorio contiene el código fuente, la ejecución experimental, los datos y el artículo científico correspondientes a la comparación empírica de dos algoritmos de ordenamiento en C++, evaluando su complejidad temporal, número de comparaciones, intercambios y profundidad de recursión bajo diversos patrones de entrada.

## Estructura del Repositorio
- `src/`: Contiene el código fuente en C++ de los algoritmos y la instrumentación del benchmark.
- `results/`: Archivos CSV con los datos crudos de las ejecuciones experimentales.
- `docs/`: Documentación del proyecto, incluyendo el manuscrito del artículo científico (`manuscrito.pdf`) y las diapositivas de sustentación (`diapositiva.pdf`).

## Algoritmos Seleccionados
- **Método Directo:** [Ej. Inserción]
- **Método Logarítmico:** [Ej. Quicksort]

## Entorno de Pruebas
- **CPU:** 
- **RAM:** 16GB 
- **Sistema Operativo:** Windows
- **Compilador:** MSYS32 UCRT64
- **Semilla utilizada:**

## Cómo Compilar y Ejecutar
1. Clona el repositorio.
2. Compila el archivo principal en la carpeta `src`:
   ```bash
   g++ -O2 src/main.cpp -o benchmark
3. Compila el archivo principal en la carpeta `src`:
   ```bash
   g++ -O2 src/main.cpp -o benchmark
