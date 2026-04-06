#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/modelos.h"
#include "../include/config.h"
#include "../include/logger.h"
#include "../include/db.h"
#include "../include/menu.h"

// Prototipos locales (mantenemos Auth en main por ahora segun enunciado)
int autenticarUsuario(char *usuario_logeado);

int main() {
    char usuario_actual[50] = "";
    
    // 1. Cargar configuración
    Config cfg = cargarConfiguracion("data/config.txt");
    
    // 2. Log e inicialización de sistema
    registrarLog("INFO", "Sistema de Transporte Público Bizkaia iniciado.");

    // 3. Inicializar Base de Datos
    if (!inicializarBD(cfg.db_path)) {
        printf("\n[FATAL] Error de inicializacion de base de datos. Saliendo...\n");
        return 1;
    }

    printf("=========================================\n");
    printf("   SISTEMA DE TRANSPORTE PUBLICO BIZKAIA \n");
    printf("=========================================\n");

    // 4. Autenticación
    if (autenticarUsuario(usuario_actual)) {
        char mensaje_log[100];
        sprintf(mensaje_log, "Login exitoso: Usuario '%s'", usuario_actual);
        registrarLog("INFO", mensaje_log);
        
        // 5. Lanzar Interfaz de Usuario (Nuevo Modulo)
        lanzarMenuPrincipal();
        
        registrarLog("INFO", "Sesion finalizada por el usuario.");
    } else {
        registrarLog("WARN", "Fallo de autenticacion tras 3 intentos.");
        printf("\n[ERROR] Demasiados intentos fallidos. Acceso denegado.\n");
    }

    // 6. Cierre de recursos
    cerrarBD();
    registrarLog("INFO", "Sistema detenido correctamente.");
    
    return 0;
}

/**
 * @brief Gestiona el inicio de sesión leyendo administradores.txt
 */
int autenticarUsuario(char *usuario_logeado) {
    char usuario_input[50], password_input[50];
    char linea[120], user_file[50], pass_file[50];
    int intentos = 0, autenticado = 0;
    FILE *f;

    while (intentos < 3 && !autenticado) {
        printf("\nIntento %d/3 - Identificacion Requerida\n", intentos + 1);
        printf("Usuario: ");
        scanf("%49s", usuario_input);
        printf("Contrasena: ");
        scanf("%49s", password_input);

        f = fopen("data/administradores.txt", "r");
        if (!f) {
            registrarLog("ERROR", "Archivo 'administradores.txt' no encontrado.");
            return 0;
        }

        while (fgets(linea, sizeof(linea), f)) {
            linea[strcspn(linea, "\r\n")] = 0;
            if (strlen(linea) == 0) continue;

            if (sscanf(linea, "%[^;];%s", user_file, pass_file) == 2) {
                if (strcmp(usuario_input, user_file) == 0 && strcmp(password_input, pass_file) == 0) {
                    autenticado = 1;
                    strcpy(usuario_logeado, usuario_input);
                    break;
                }
            }
        }
        fclose(f);

        if (!autenticado) {
            printf("[!] Acceso denegado.\n");
            intentos++;
        }
    }
    return autenticado;
}
