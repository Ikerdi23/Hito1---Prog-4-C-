#ifndef MODELOS_H
#define MODELOS_H

/**
 * @file modelos.h
 * @brief Definición de las estructuras de datos para el Sistema de Transporte de Bizkaia.
 */

// Entidad Municipio
typedef struct {
    int id;
    char nombre[50];
} Municipio;

// Entidad Parada
typedef struct {
    int id;
    char nombre[100];
    int municipio_id;
} Parada;

// Entidad Linea
typedef struct {
    int id;
    char nombre[50];
} Linea;

// Entidad Horario (Relación Linea - Parada con tiempo)
typedef struct {
    int id_linea;
    int id_parada;
    char hora[6]; // Formato "HH:MM"
} Horario;

// Entidad Incidencia
typedef struct {
    int id;
    char descripcion[255];
    char fecha[11]; // Formato "YYYY-MM-DD"
    int estado;     // 0: Activa, 1: Resuelta
} Incidencia;

#endif // MODELOS_H
