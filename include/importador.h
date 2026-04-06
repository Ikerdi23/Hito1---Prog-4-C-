#ifndef IMPORTADOR_H
#define IMPORTADOR_H

#include "sqlite3.h"

/**
 * @file importador.h
 * @brief Funciones para importar datos desde CSV hacia la base de datos SQLite.
 */

/**
 * @brief Orquestador para importar todos los archivos CSV predefinidos.
 */
void importarTodosLosCSV();

/**
 * @brief Importa el catálogo de municipios desde CSV.
 */
int importarMunicipiosCSV(const char* ruta);

/**
 * @brief Importa el catálogo de paradas desde CSV.
 */
int importarParadasCSV(const char* ruta);

int importarLineasCSV(const char* ruta);
int importarLineaParadaCSV(const char* ruta);
int importarHorariosCSV(const char* ruta);
int importarIncidenciasCSV(const char* ruta);

#endif // IMPORTADOR_H
