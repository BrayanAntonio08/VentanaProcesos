/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.h
 * Author: brayan08
 *
 * Created on 15 de septiembre de 2022, 08:55 AM
 */

#ifndef NODO_H
#define NODO_H
#include "proceso.h"

typedef struct{
    proceso proceso;
    nodo * siguiente;
}nodo;

#endif /* NODO_H */

