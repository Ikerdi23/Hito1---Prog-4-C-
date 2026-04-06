#ifndef LOGGER_H
#define LOGGER_H

/**
 * @file logger.h
 * @brief Sistema de registro de eventos (logs).
 */

/**
 * @brief Registra un mensaje en el archivo admin.log con timestamp.
 * @param nivel Nivel del log (INFO, ERROR, WARN).
 * @param mensaje Texto desriptivo del evento.
 */
void registrarLog(const char* nivel, const char* mensaje);

#endif // LOGGER_H
