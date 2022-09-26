/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   proceso.h
 * Author: brayan08
 *
 * Created on 15 de septiembre de 2022, 09:02 AM
 */

#ifndef PROCESO_H
#define PROCESO_H

#include <bits/pthreadtypes.h>

#define LISTO 0
#define EJECUCION 1
#define ESPERA 2
#define DEFAULT_INT_VALUE -100;

typedef struct{
    char* nombre;
    int num_entrada;
    int siguiente;
    int prioridad;
    int estado;
    int tiempo_ejecucion;
    int tiempo_ES;
    pthread_t* hilo_ejecucion;
}proceso;

#endif /* PROCESO_H */

