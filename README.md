# Analisis Experimental de la Complejidad Temporal del Algoritmo Selection Sort frente a Merge

## 1. Descripción del Proyecto
Este proyecto evalúa el rendimiento empirico y la complejidad temporal de algoritmos de ordenamiento (Selection Sort vs. Merge Sort) mediante pruebas automatizadas en C++.

**Estudiante:** Joshua David Huerya Choque 
**Asignatura:** Programación Avanzada | Ciclo II - Sección B (2026-II)  
**Universidad Nacional Jorge Basadre Grohmann**

---

## 2. Algoritmos Seleccionados
- Selection Sort (`O(n^2)`)

- Merge Sort (`O(n \log n)`)

## 3. Requisitos de Compilación y Ejecución
Hardware y Sistema Operativo
Sistema Operativo: Windows 11 (compatible con terminal BASH).   
Componentes:[Procesador AMD Ryzen 5 7520U with Radeon Graphics, 16 GB de ram]
Software y Herramientas:
Compilador: g++ con soporte completo para el estándar C++17.   
Banderas de compilación: Optimización -O2 habilitada.   
Librerías de C++ utilizadas: chrono steady_clock, random std::mt19937, fstream, vector, iostream.   
Entorno para Análisis de Datos: Python 3 (Google Colab / Jupyter Notebook) con las librerías pandas, matplotlib y seaborn.

## 4. Instrucciones para reproducir los experimentos 
1. Clonar el repositorio o navegar hasta la carpeta con el código fuente en C++:

cd src/


2. Compilar el archivo de C++ con el flag de optimización -O2:

g++ -O2 Proyecto_2.cpp -o benchmark


3. Ejecutar el ejecutable para iniciar la prueba automatizada:

./benchmark


4. El programa procesará todas las iteraciones y guardará automáticamente los datos en: resultados_experimento.csv.

## 5. Tamaño, patrones y semillas utilizados
Tamaños de entrada 
($n$):$n = 1,000$ elementos   
$n = 10,000$ elementos
(Nota: Se omitió $n = 100,000$ debido a la inviabilidad temporal que genera la cota $O(n^2)$ de Selection Sort).   
Patrones de datos evaluados (5 tipos):
   Aleatorio: Distribución uniforme no ordenada.   
   Ascendente: Arreglo totalmente ordenado de menor a mayor.   
   Descendente: Arreglo totalmente invertido de mayor a menor.   
   Casi Ordenado: Arreglo con un porcentaje mínimo de elementos desordenados.   
   Con Duplicados: Arreglo con alto porcentaje de valores repetidos.   
   
Generador pseudoaleatorio: std::mt19937 con semillas fijas para garantizar reproducibilidad exacta.   
Repeticiones: 30 ejecuciones independientes por cada combinación (Algoritmo × $n$ × Patrón). 

## 6. Descripción de los archivos de Resultados
results/resultados_experimento.csv: Contiene la recolección cruda de las mediciones experimentales de las 30 repeticiones. Incluye las columnas: algoritmo, n, patron, repeticion, tiempo_ms, comparaciones e intercambios.   

analysis/graficos_y_estadistica.ipynb: Script de Python que lee el archivo CSV, calcula la media, mediana, desviación estándar, mínimo y máximo.

## 7. Principales Resultados y Conclusiones
1. Selection Sort (`O(n^2)`): Mantuvo un comportamiento rígido e inalterable ante cualquier patrón de datos, realizando exactamente $C(n) = \frac{n(n-1)}{2}$ comparaciones. Para $n = 10,000$, superó promedios de 360 ms.
2. Merge Sort (`O(n \log n)`): Demostró una superioridad drástica en eficiencia, manteniendo tiempos por debajo de los 6 ms incluso para $n = 10,000$ y conservando la estabilidad de los datos.
4. Rigurosidad: La media de 30 repeticiones neutralizó eficazmente la variabilidad e interferencias causadas por los procesos del sistema operativo.

## 8. Link del video de youtube   

## 9. ID del commit final
