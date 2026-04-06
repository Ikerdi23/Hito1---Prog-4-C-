#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../include/logger.h"

/**
 * @brief Implementa el registro de logs con timestamp [dd-mm-yyyy hh:mm:ss]
 */
void registrarLog(const char* nivel, const char* mensaje) {
    FILE *f = fopen("logs/admin.log", "a");
    if (f == NULL) {
        printf("[ERROR] No se pudo escribir en el archivo de log.\n");
        return;
    }

    // Obtener tiempo actual
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[25];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Formatear timestamp: [18-02-2026 10:15:00]
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);

    // Escribir en el archivo
    fprintf(f, "[%s] [%s] %s\n", buffer, nivel, mensaje);

    fclose(f);
}
