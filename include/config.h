#ifndef CONFIG_H
#define CONFIG_H

/**
 * @file config.h
 * @brief Gestión de la configuración del sistema leyendo desde config.txt.
 */

#define MAX_CONFIG_LEN 100

typedef struct {
    char db_path[MAX_CONFIG_LEN];
    // Se pueden añadir más parámetros en el futuro (ej: LOG_LEVEL)
} Config;

/**
 * @brief Carga los parámetros de configuración desde un archivo persistente.
 * @param ruta Ruta del archivo config.txt.
 * @return Estructura con los valores cargados.
 */
Config cargarConfiguracion(const char* ruta);

#endif // CONFIG_H
