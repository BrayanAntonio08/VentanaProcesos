/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Algoritmos.h
 * Author: brayan08
 *
 * Created on 15 de septiembre de 2022, 10:20 AM
 */

#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "proceso.h"
#include <gtk/gtk.h>

typedef struct{
    proceso* arreglo;
    int cantidad_procesos;
}param;

void* FCFS(param* Parametros){
    int size = Parametros->cantidad_procesos;
    proceso* head = Parametros->arreglo;
    while(1){
        for (int i = 0; i < size; i++) {
            proceso* aux = head + i;
            if(aux->estado == LISTO)
                aux->estado = EJECUCION;
            while(aux->estado != ESPERA);
        }
    }
}//FCFS

void RR(proceso Procesos[]){
    //debe calcular el tiempo, saber cuánto debe ser el quantum preciso y reconocer si un proceso terminó el ciclo
    
}


#endif /* ALGORITMOS_H */

