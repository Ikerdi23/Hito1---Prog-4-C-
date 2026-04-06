#include <stdio.h>
#include "../include/sqlite3.h"
#include "../include/db.h"
#include "../include/logger.h"

static sqlite3 *db = NULL;

/**
 * @brief Implementa la creación de tablas con SQLite3
 */
int inicializarBD(const char* ruta_db) {
    int rc;
    char *err_msg = 0;

    // 1. Abrir conexión
    rc = sqlite3_open(ruta_db, &db);

    if (rc != SQLITE_OK) {
        char msg[120];
        sprintf(msg, "No se pudo abrir la base de datos: %s", sqlite3_errmsg(db));
        registrarLog("ERROR", msg);
        sqlite3_close(db);
        return 0;
    }

    registrarLog("INFO", "Conexion a SQLite establecida.");

    // 2. Esquema SQL
    const char *sql = 
        "PRAGMA foreign_keys = ON;"
        
        "CREATE TABLE IF NOT EXISTS MUNICIPIO ("
        "ID_Municipio INTEGER PRIMARY KEY,"
        "Nombre TEXT,"
        "Provincia TEXT);"

        "CREATE TABLE IF NOT EXISTS PARADA ("
        "ID_Parada INTEGER PRIMARY KEY,"
        "Nombre TEXT,"
        "Tipo TEXT,"
        "Accesible TEXT,"
        "ID_Municipio INTEGER,"
        "FOREIGN KEY (ID_Municipio) REFERENCES MUNICIPIO(ID_Municipio));"

        "CREATE TABLE IF NOT EXISTS LINEA ("
        "ID_Linea INTEGER PRIMARY KEY,"
        "Codigo TEXT,"
        "Nombre TEXT,"
        "Tipo TEXT);"

        "CREATE TABLE IF NOT EXISTS LINEA_PARADA ("
        "ID_Linea INTEGER,"
        "ID_Parada INTEGER,"
        "Orden_Trayecto INTEGER,"
        "PRIMARY KEY (ID_Linea, ID_Parada),"
        "FOREIGN KEY (ID_Linea) REFERENCES LINEA(ID_Linea),"
        "FOREIGN KEY (ID_Parada) REFERENCES PARADA(ID_Parada));"

        "CREATE TABLE IF NOT EXISTS HORARIO ("
        "ID_Horario INTEGER PRIMARY KEY,"
        "Hora_Paso TEXT,"
        "Tipo_Dia TEXT,"
        "ID_Linea INTEGER,"
        "ID_Parada INTEGER,"
        "FOREIGN KEY (ID_Linea) REFERENCES LINEA(ID_Linea),"
        "FOREIGN KEY (ID_Parada) REFERENCES PARADA(ID_Parada));"

        "CREATE TABLE IF NOT EXISTS INCIDENCIA ("
        "ID_Incidencia INTEGER PRIMARY KEY,"
        "Tipo TEXT,"
        "Descripcion TEXT,"
        "Fecha TEXT,"
        "Hora TEXT,"
        "Activa TEXT,"
        "ID_Linea INTEGER,"
        "FOREIGN KEY (ID_Linea) REFERENCES LINEA(ID_Linea));";

    // 3. Ejecutar creación
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        char msg[255];
        sprintf(msg, "Error creando tablas SQLite: %s", err_msg);
        registrarLog("ERROR", msg);
        sqlite3_free(err_msg);
        return 0;
    }

    registrarLog("INFO", "Tablas de la base de datos inicializadas correctamente.");
    return 1;
}

/**
 * @brief Obtiene el puntero a la conexión de base de datos activa.
 */
sqlite3* getBD() {
    return db;
}

/**
 * @brief Cierra la conexión si está abierta
 */
void cerrarBD() {
    if (db != NULL) {
        sqlite3_close(db);
        registrarLog("INFO", "Conexion a base de datos cerrada.");
    }
}
