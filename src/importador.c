#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/importador.h"
#include "../include/db.h"
#include "../include/logger.h"

/**
 * @brief Implementación del importador desde CSV
 */

void importarTodosLosCSV() {
    registrarLog("INFO", "Iniciando importación masiva de datos...");
    
    importarMunicipiosCSV("data/municipios.csv");
    importarParadasCSV("data/paradas.csv");
    
    // Aquí se añadirían el resto de llamadas para Líneas, Horarios, etc.
    
    registrarLog("INFO", "Fin de la importación masiva.");
}

int importarMunicipiosCSV(const char* ruta) {
    sqlite3 *db = getBD();
    FILE *f = fopen(ruta, "r");
    if (!f) {
        char msg[120];
        sprintf(msg, "No se pudo abrir el archivo de municipios: %s", ruta);
        registrarLog("ERROR", msg);
        return 0;
    }

    sqlite3_stmt *stmt;
    const char *sql = "INSERT OR IGNORE INTO MUNICIPIO (ID_Municipio, Nombre, Provincia) VALUES (?, ?, ?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    // Iniciar Transacción para rendimiento
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

    char linea[256];
    int count = 0;
    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;

        // Parsear: ID;Nombre;Provincia
        int id;
        char nombre[100], provincia[100];
        
        if (sscanf(linea, "%d;%[^;];%[^;]", &id, nombre, provincia) == 3) {
            sqlite3_bind_int(stmt, 1, id);
            sqlite3_bind_text(stmt, 2, nombre, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, provincia, -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_DONE) {
                count++;
            }
            sqlite3_reset(stmt);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
    fclose(f);

    char msg[120];
    sprintf(msg, "Importados %d municipios desde %s", count, ruta);
    registrarLog("INFO", msg);
    return 1;
}

int importarParadasCSV(const char* ruta) {
    sqlite3 *db = getBD();
    FILE *f = fopen(ruta, "r");
    if (!f) {
        char msg[120];
        sprintf(msg, "No se pudo abrir el archivo de paradas: %s", ruta);
        registrarLog("ERROR", msg);
        return 0;
    }

    sqlite3_stmt *stmt;
    const char *sql = "INSERT OR IGNORE INTO PARADA (ID_Parada, Nombre, Tipo, Accesible, ID_Municipio) VALUES (?, ?, ?, ?, ?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

    char linea[256];
    int count = 0;
    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;

        // Parsear: ID;Nombre;Tipo;Accesible;ID_Municipio
        int id, id_muni;
        char nombre[100], tipo[50], accesible[10];
        
        if (sscanf(linea, "%d;%[^;];%[^;];%[^;];%d", &id, nombre, tipo, accesible, &id_muni) == 5) {
            sqlite3_bind_int(stmt, 1, id);
            sqlite3_bind_text(stmt, 2, nombre, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, tipo, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 4, accesible, -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 5, id_muni);

            if (sqlite3_step(stmt) == SQLITE_DONE) {
                count++;
            }
            sqlite3_reset(stmt);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
    fclose(f);

    char msg[120];
    sprintf(msg, "Importadas %d paradas desde %s", count, ruta);
    registrarLog("INFO", msg);
    return 1;
}
