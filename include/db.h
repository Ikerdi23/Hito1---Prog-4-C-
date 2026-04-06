#ifndef DB_H
#define DB_H

#include "sqlite3.h"

/**
 * @file db.h
 * @brief Gestión de la base de datos SQLite3.
 */

/**
 * @brief Inicializa la base de datos, abre la conexión y crea las tablas si no existen.
 * @param ruta_db Ruta del archivo .db
 * @return 1 si tiene éxito, 0 en caso de error.
 */
int inicializarBD(const char* ruta_db);

/**
 * @brief Obtiene el puntero a la conexión de base de datos activa.
 */
sqlite3* getBD();

void cerrarBD();

#endif // DB_H
