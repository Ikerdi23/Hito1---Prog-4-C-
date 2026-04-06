#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/config.h"

/**
 * @brief Implementa la carga de parámetros desde config.txt
 */
Config cargarConfiguracion(const char* ruta) {
    Config cfg;
    FILE *f;
    char linea[120];

    // Valores por defecto
    strcpy(cfg.db_path, "data/transporte_bizkaia.db");

    f = fopen(ruta, "r");
    if (f == NULL) {
        printf("[WARNING] No se encontro %s. Usando valores por defecto.\n", ruta);
        return cfg;
    }

    while (fgets(linea, sizeof(linea), f)) {
        // Eliminar saltos de línea
        linea[strcspn(linea, "\r\n")] = 0;

        // Ignorar comentarios o líneas vacías
        if (linea[0] == '#' || strlen(linea) == 0) continue;

        char *clave = strtok(linea, "=");
        char *valor = strtok(NULL, "=");

        if (clave != NULL && valor != NULL) {
            if (strcmp(clave, "DB_PATH") == 0) {
                strncpy(cfg.db_path, valor, MAX_CONFIG_LEN - 1);
            }
            // Añadir futuros parámetros de configuración aquí
        }
    }

    fclose(f);
    return cfg;
}
