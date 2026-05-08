# EDA_PF_AlvarezPablo_QuinteroSamuel-

## Integrantes
- Pablo Alvarez Restrepo
- Samuel Quintero Quintero

## Descripción
Análisis de redes de transporte reales usando el dataset roadNet-PA 
(Pennsylvania Road Network) de la colección SNAP de Stanford.
El programa implementa algoritmos clásicos de grafos en C++:
BFS, Dijkstra con heap mínimo, Kruskal (MST) y detección de DAG.

## Dataset
- Fuente: https://snap.stanford.edu/data/roadNet-PA.html
- Nodos: 1,088,092 intersecciones viales
- Aristas: 1,541,898 tramos viales (no dirigidas)
- Citación: Leskovec, J. & Krevl, A. (2014). SNAP Datasets: 
  Stanford Large Network Dataset Collection.

## Requisitos
- Compilador g++ con soporte C++17
- Mínimo 512 MB de RAM disponible
- Sistema operativo: Windows, Linux o Mac

## Estructura del repositorio
EDA_PF_AlvarezPablo_QuinteroSamuel/

## Estructura del repositorio
```
EDA_PF_AlvarezPablo_QuinteroSamuel/
├── data/
│   └── roadNet-PA.txt
├── src/
│   ├── graph.hpp
│   ├── loader.cpp
│   ├── bfs.cpp
│   ├── dijkstra.cpp
│   ├── structural.cpp
│   ├── subgraph.cpp
│   └── main.cpp
├── results/
│   ├── analisis_estructural.txt
│   ├── consultas_p2p.csv
│   ├── path_Q1.txt
│   ├── path_Q6.txt
│   ├── subgrafo_caminos.txt
│   ├── analisis_subgrafo.txt
│   └── tiempos.csv
├── report/
│   └── Informe.pdf
└── README.md
```

## Compilación
Desde la carpeta raíz del proyecto ejecutar:
g++ -std=c++17 -O2 -o eda_pf src/main.cpp src/loader.cpp src/bfs.cpp src/structural.cpp src/dijkstra.cpp src/subgraph.cpp

El flag `-O2` es obligatorio para tiempos realistas con el dataset completo.

## Ejecución

### Módulo A — Análisis estructural
.\eda_pf.exe A
Calcula y verifica contra SNAP: nodos, aristas, grado promedio,
nodo de mayor grado, diámetro aproximado y componentes conexas.
Genera: `results/analisis_estructural.txt`

### Módulo B — Consultas punto a punto
.\eda_pf.exe B
Ejecuta 10 consultas P2P con Dijkstra ponderado y BFS no ponderado.
Reconstruye y guarda los caminos de Q01 y Q06.
Genera: `results/consultas_p2p.csv`, `results/path_Q1.txt`, `results/path_Q6.txt`

### Módulo C — Subgrafo, MST y DAG
.\eda_pf.exe C
Construye el subgrafo inducido por los caminos Q01 y Q06.
Calcula el MST con Kruskal y verifica si es DAG.
Genera: `results/subgrafo_caminos.txt`, `results/analisis_subgrafo.txt`

### Todos los módulos + tiempos
.\eda_pf.exe ALL
Ejecuta A, B y C en secuencia y genera el resumen de tiempos.
Genera: todos los archivos anteriores + `results/tiempos.csv`

## Nota importante
El Módulo C depende de los archivos generados por el Módulo B.
Ejecutar siempre en orden: A → B → C, o usar directamente ALL.

## Reindexación de nodos
Los IDs originales del dataset no son consecutivos (van hasta 1,090,919).
El programa los traduce a índices internos 0..1,088,091 usando un
unordered_map. Los archivos de resultados usan índices internos.

## Verificación de resultados
Propiedad          SNAP        Obtenido
Nodos              1,088,092   1,088,092  ✓
Aristas            1,541,898   1,541,898  ✓
Grado promedio     ~2.83       2.83413    ✓
Nodos WCC          1,087,562   1,087,562  ✓
Diámetro           782         592 (est.) ~
El diámetro es una estimación desde el nodo de mayor grado.
El valor exacto requeriría BFS desde todos los nodos.
