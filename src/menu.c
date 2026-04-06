#include <stdio.h>
#include <stdlib.h>
#include "../include/menu.h"
#include "../include/importador.h"
#include "../include/logger.h"

// Colores ANSI para una consola moderna
#define RESET   "\033[0m"
#define BOLDBLUE "\033[1m\033[34m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDRED "\033[1m\033[31m"
#define BOLDWHITE "\033[1m\033[37m"

/**
 * @brief Implementación del sistema de menús.
 */

void lanzarMenuPrincipal() {
    int opcion = 0;

    do {
        printf("\n" BOLDBLUE "=========================================" RESET "\n");
        printf(BOLDWHITE "     SISTEMA DE TRANSPORTE BIZKAIA       " RESET "\n");
        printf(BOLDBLUE "=========================================" RESET "\n");
        printf(" 1. Importar paradas y lineas (CSV)\n");
        printf(" 2. " BOLDWHITE "Gestionar Red" RESET " (Proximamente)\n");
        printf(" 3. " BOLDWHITE "Panel de Incidencias" RESET " (Proximamente)\n");
        printf(BOLDRED " 4. Salir" RESET "\n");
        printf(BOLDBLUE "-----------------------------------------" RESET "\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            // Limpiar buffer en caso de error
            while (getchar() != '\n');
            opcion = -1;
        }

        switch (opcion) {
            case 1:
                printf("\n" BOLDGREEN "[PROCESO] Ejecutando importacion masiva..." RESET "\n");
                importarTodosLosCSV();
                printf(BOLDGREEN "[OK] El proceso de carga ha finalizado." RESET "\n");
                break;
            case 2:
                printf("\n[INFO] Modulo de gestion de red no disponible en esta fase.\n");
                break;
            case 3:
                printf("\n[INFO] El panel de incidencias requiere conexion a SQLite activa.\n");
                break;
            case 4:
                printf("\nSaliendo y cerrando modulos con seguridad...\n");
                break;
            default:
                printf("\n" BOLDRED "[!] Opcion invalida. Intente de nuevo." RESET "\n");
                break;
        }

    } while (opcion != 4);
}
