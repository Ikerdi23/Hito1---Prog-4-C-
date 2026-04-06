#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/importador.h"
#include "../include/db.h"
#include "../include/logger.h"

void importarTodosLosCSV() {
    registrarLog("INFO", "Iniciando importacion masiva de datos...");
    importarMunicipiosCSV("data/municipios.csv");
    importarParadasCSV("data/paradas.csv");
    importarLineasCSV("data/lineas.csv");
    importarLineaParadaCSV("data/linea_parada.csv");
    importarHorariosCSV("data/horarios.csv");
    importarIncidenciasCSV("data/incidencias.csv");
    registrarLog("INFO", "Fin de la importacion masiva.");
}

int importarMunicipiosCSV(const char* ruta) {
    sqlite3 *db = getBD();
    FILE *f = fopen(ruta, "r");
    if (!f) { registrarLog("ERROR", "No se pudo abrir municipios.csv"); return 0; }
    sqlite3_stmt *stmt;
    const char *sql = "INSERT OR IGNORE INTO MUNICIPIO (ID_Municipio, Nombre, Provincia) VALUES (?, ?, ?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    char linea[256]; int count = 0;
    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;
        int id; char nombre[100], provincia[100];
        if (sscanf(linea, "%d;%[^;];%[^;]", &id, nombre, provincia) == 3) {
            sqlite3_bind_int(stmt, 1, id);
            sqlite3_bind_text(stmt, 2, nombre, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 3, provincia, -1, SQLITE_TRANSIENT);
            if (sqlite3_step(stmt) == SQLITE_DONE) count++;
            sqlite3_reset(stmt);
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
    fclose(f);
    char msg[120]; sprintf(msg, "Importados %d municipios", count);
    registrarLog("INFO", msg);
    return 1;
}

int importarParadasCSV(const char* ruta) {
    sqlite3 *db = getBD();
    FILE *f = fopen(ruta, "r");
    if (!f) { registrarLog("ERROR", "No se pudo abrir paradas.csv"); return 0; }
    sqlite3_stmt *stmt;
    const char *sql = "INSERT OR IGNORE INTO PARADA (ID_Parada, Nombre, Tipo, Accesible, ID_Municipio) VALUES (?, ?, ?, ?, ?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    char linea[256]; int count = 0;
    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;
        int id, id_muni; char nombre[100], tipo[50], accesible[10];
        if (sscanf(linea, "%d;%[^;];%[^;];%[^;];%d", &id, nombre, tipo, accesible, &id_muni) == 5) {
            sqlite3_bind_int(stmt, 1, id);
            sqlite3_bind_text(stmt, 2, nombre, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 3, tipo, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 4, accesible, -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 5, id_muni);
            if (sqlite3_step(stmt) == SQLITE_DONE) count++;
            sqlite3_reset(stmt);
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
    fclose(f);
    char msg[120]; sprintf(msg, "Importadas %d paradas", count);
    registrarLog("INFO", msg);
    return 1;
}

int importarLineasCSV(const char* ruta) {
    sqlite3 *db = getBD();
    FILE *f = fopen(ruta, "r");
    if (!f) { registrarLog("ERROR", "No se pudo abrir lineas.csv"); return 0; }
    sqlite3_stmt *stmt;
    const char *sql = "INSERT OR IGNORE INTO LINEA (ID_Linea, Codigo, Nombre, Tipo) VALUES (?,?,?,?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    char linea[256]; int count = 0;
    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;
        int id; char codigo[20], nombre[50], tipo[10];
        if (sscanf(linea, "%d;%[^;];%[^;];%[^;]", &id, codigo, nombre, tipo) == 4) {
            sqlite3_bind_int(stmt, 1, id);
            sqlite3_bind_text(stmt, 2, codigo, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 3, nombre, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 4, tipo, -1, SQLITE_TRANSIENT);
            if (sqlite3_step(stmt) == SQLITE_DONE) count++;
            sqlite3_reset(stmt);
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
    fclose(f);
    char msg[120]; sprintf(msg, "Importadas %d lineas", count);
    registrarLog("INFO", msg);
    return 1;
}

int importarLineaParadaCSV(const char* ruta) {
    sqlite3 *db = getBD();
    FILE *f = fopen(ruta, "r");
    if (!f) { registrarLog("ERROR", "No se pudo abrir linea_parada.csv"); return 0; }
    sqlite3_stmt *stmt;
    const char *sql = "INSERT OR IGNORE INTO LINEA_PARADA (ID_Linea, ID_Parada, Orden_Trayecto) VALUES (?,?,?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    char linea[256]; int count = 0;
    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;
        int id_linea, id_parada, orden;
        if (sscanf(linea, "%d;%d;%d", &id_linea, &id_parada, &orden) == 3) {
            sqlite3_bind_int(stmt, 1, id_linea);
            sqlite3_bind_int(stmt, 2, id_parada);
            sqlite3_bind_int(stmt, 3, orden);
            if (sqlite3_step(stmt) == SQLITE_DONE) count++;
            sqlite3_reset(stmt);
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
    fclose(f);
    char msg[120]; sprintf(msg, "Importadas %d relaciones linea-parada", count);
    registrarLog("INFO", msg);
    return 1;
}

int importarHorariosCSV(const char* ruta) {
    sqlite3 *db = getBD();
    FILE *f = fopen(ruta, "r");
    if (!f) { registrarLog("ERROR", "No se pudo abrir horarios.csv"); return 0; }
    sqlite3_stmt *stmt;
    const char *sql = "INSERT OR IGNORE INTO HORARIO (ID_Horario, Hora_Paso, Tipo_Dia, ID_Linea, ID_Parada) VALUES (?,?,?,?,?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    char linea[256]; int count = 0;
    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;
        int id, id_linea, id_parada; char hora[6], tipo_dia[20];
        if (sscanf(linea, "%d;%[^;];%[^;];%d;%d", &id, hora, tipo_dia, &id_linea, &id_parada) == 5) {
            sqlite3_bind_int(stmt, 1, id);
            sqlite3_bind_text(stmt, 2, hora, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 3, tipo_dia, -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 4, id_linea);
            sqlite3_bind_int(stmt, 5, id_parada);
            if (sqlite3_step(stmt) == SQLITE_DONE) count++;
            sqlite3_reset(stmt);
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
    fclose(f);
    char msg[120]; sprintf(msg, "Importados %d horarios", count);
    registrarLog("INFO", msg);
    return 1;
}

int importarIncidenciasCSV(const char* ruta) {
    sqlite3 *db = getBD();
    FILE *f = fopen(ruta, "r");
    if (!f) { registrarLog("ERROR", "No se pudo abrir incidencias.csv"); return 0; }
    sqlite3_stmt *stmt;
    const char *sql = "INSERT OR IGNORE INTO INCIDENCIA (ID_Incidencia, Tipo, Descripcion, Fecha, Hora, Activa, ID_Linea) VALUES (?,?,?,?,?,?,?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    char linea[512]; int count = 0;
    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;
        int id, id_linea; char tipo[20], desc[255], fecha[11], hora[6], activa[5];
        if (sscanf(linea, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d",
                   &id, tipo, desc, fecha, hora, activa, &id_linea) == 7) {
            sqlite3_bind_int(stmt, 1, id);
            sqlite3_bind_text(stmt, 2, tipo, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 3, desc, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 4, fecha, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 5, hora, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 6, activa, -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 7, id_linea);
            if (sqlite3_step(stmt) == SQLITE_DONE) count++;
            sqlite3_reset(stmt);
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
    fclose(f);
    char msg[120]; sprintf(msg, "Importadas %d incidencias", count);
    registrarLog("INFO", msg);
    return 1;
}
