#include <stdio.h>
#include <stdlib.h>
#include "../include/menu.h"
#include "../include/importador.h"
#include "../include/gestion_red.h"
#include "../include/incidencias.h"
#include "../include/logger.h"

#define RESET      "\033[0m"
#define BOLDBLUE   "\033[1m\033[34m"
#define BOLDGREEN  "\033[1m\033[32m"
#define BOLDRED    "\033[1m\033[31m"
#define BOLDWHITE  "\033[1m\033[37m"

void lanzarMenuPrincipal() {
    int opcion = 0;
    do {
        printf("\n" BOLDBLUE "=========================================\n" RESET);
        printf(BOLDWHITE "   SISTEMA DE TRANSPORTE BIZKAIA         \n" RESET);
        printf(BOLDBLUE "=========================================\n" RESET);
        printf(" 1. Importar datos desde CSV\n");
        printf(" 2. Gestionar Red (líneas y paradas)\n");
        printf(" 3. Panel de Incidencias\n");
        printf(BOLDRED " 4. Salir\n" RESET);
        printf(BOLDBLUE "-----------------------------------------\n" RESET);
        printf("Seleccione una opción: ");

        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion = -1;
        }

        switch (opcion) {
            case 1:
                printf("\n" BOLDGREEN "[PROCESO] Ejecutando importación masiva...\n" RESET);
                importarTodosLosCSV();
                printf(BOLDGREEN "[OK] Carga finalizada.\n" RESET);
                break;
            case 2:
                menuGestionRed();
                break;
            case 3:
                menuIncidencias();
                break;
            case 4:
                printf("\nSaliendo...\n");
                break;
            default:
                printf("\n" BOLDRED "[!] Opción inválida.\n" RESET);
                break;
        }
    } while (opcion != 4);
}
