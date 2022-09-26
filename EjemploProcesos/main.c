#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <bits/pthreadtypes.h>
#include <bits/types/sigevent_t.h>
#include "proceso.h"
#include "Algoritmos.h"

void generate_label(char* dest, int index);

int ejecutando_proceso = 0;



GtkWidget *et_process_quantity;
GtkWidget *et_quantum;

GtkWidget *running_process;


void *fcfs(){
    g_print("Hola mundo");
} 

void *accion_hilo_default(proceso* proceso_vigente){
    proceso proceso_actual = *proceso_vigente;
    
    g_print("Proceso %d creado\n Estado: %d\n",proceso_actual.num_entrada,proceso_actual.estado);
    while(1){
        switch(proceso_actual.estado){
            case LISTO:
                sleep(1);
                if(proceso_actual.num_entrada == 0) 
                    proceso_actual.estado = EJECUCION;
                break;
            case EJECUCION:
                generate_label(proceso_actual.nombre,proceso_actual.num_entrada);
                int ejecutando = 1;
                while(ejecutando){
                    g_print("Ejecutando proceso %d\n",proceso_actual.num_entrada);
                    sleep(1);
                    ejecutando = rand()%2;
                }
                proceso_actual.estado = ESPERA;
            case ESPERA:
                int esperando = 1;
                while(esperando){
                    g_print("Proceso %d en espera\n",proceso_actual.num_entrada);
                    sleep(1);
                    esperando = rand()%2;
                }
                proceso_actual.estado = LISTO;
                    
        }
    }
}


void run_execution(proceso arreglo_procesos[], int cantidad_procesos){
  
    
    param* par;
    par->arreglo = arreglo_procesos;
    par->cantidad_procesos = cantidad_procesos;
    
//    pthread_create(planificador, NULL, FCFS, &par);
////    pthread_join(planificador,NULL);
//    FCFS(arreglo_procesos);
}

void create_threads(proceso Procesos[],int cantidad){
    int i;
    for (i = 0; i < cantidad; i++) {
        pthread_create(Procesos[i].hilo_ejecucion, NULL, accion_hilo_default, &Procesos[i]); 
    }
}

void create_planificator(){
    pthread_t* plan;
    pthread_create(plan, NULL, fcfs, NULL);
}

void start_process ( )
{
    char *text_cantidad_hilos = gtk_entry_get_text(GTK_ENTRY(et_process_quantity));
    
    int cantidad_hilos = atoi(text_cantidad_hilos);
    g_print("Cantidad hilos: %d\n",cantidad_hilos);
    proceso arreglo_procesos[cantidad_hilos];
   
    for (int i = 0; i < cantidad_hilos; i++) { //for incializa los hilos
        
        g_print("ïndice del proceso en creación:  %d \n",i);
        arreglo_procesos[i].num_entrada = i;
        arreglo_procesos[i].prioridad = rand()%5+1;
        arreglo_procesos[i].estado = LISTO; 
        arreglo_procesos[i].tiempo_ES = rand()%10+1;
        if(i != cantidad_hilos-1)
            arreglo_procesos[i].siguiente = i+1;
        pthread_t* hilo;
        arreglo_procesos[i].hilo_ejecucion = hilo;
        
    }
    create_threads(arreglo_procesos,cantidad_hilos);
    
    create_planificator();
}//start_process


static void initialize(GtkApplication *app, gpointer user_data){
    
    //window that holds the components
    GtkWidget *window;
    
    //Container which can place child widgets at fixed positions 
    GtkWidget *fixed;
    
    //Labels for the three states of the process
    GtkWidget *lbl_running;
    GtkWidget *lbl_ready;
    GtkWidget *lbl_blocked;
    GtkWidget *lbl_process_quantity;
    GtkWidget *lbl_quantum;
    
    
    //Entry components
    
    
    //TextView components
    GtkWidget *tv_blocked_processes;
    GtkWidget *tv_ready_processes;
    
    //Button to start the simulation
    GtkWidget *btn_start;
    
    //Specializing the GtkWidget component and creating the window
    window = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_title(GTK_WINDOW(window), "Three state process model");
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //Specializing the GTKWidget fixed variable to create the container that holds the widgets of the window
    fixed = gtk_fixed_new();
    
    //Packing the container into the window
    gtk_container_add(GTK_CONTAINER(window), fixed);
    
    //Creating the entry widgets
    et_process_quantity = gtk_entry_new();
    
    et_quantum = gtk_entry_new();
    
    //Creating the button and the signal to call the function to start the process
    btn_start = gtk_button_new_with_label("Start");
    g_signal_connect(btn_start, "clicked", G_CALLBACK(start_process), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), btn_start, 200, 10);
     
    //Creating the labels
    lbl_process_quantity = gtk_label_new("Process quantity:");
    gtk_fixed_put(GTK_FIXED(fixed), lbl_process_quantity, 10, 10);
    
    lbl_quantum = gtk_label_new("Quantum:");
    gtk_fixed_put(GTK_FIXED(fixed), lbl_quantum, 10, 80);
    
    
    lbl_running = gtk_label_new("Running:");
    gtk_fixed_put(GTK_FIXED(fixed), lbl_running, 500, 80);
    
    running_process = gtk_label_new(" ");
    gtk_fixed_put(GTK_FIXED(fixed),running_process,510,100);
    
    lbl_ready = gtk_label_new("Ready:");
    gtk_fixed_put(GTK_FIXED(fixed), lbl_ready, 660, 250);
    
    lbl_blocked = gtk_label_new("Blocked:");
    gtk_fixed_put(GTK_FIXED(fixed), lbl_blocked, 350, 250);
    
  
    //Adding the entry widgets
    gtk_fixed_put(GTK_FIXED(fixed), et_process_quantity, 10, 30);
    
    gtk_fixed_put(GTK_FIXED(fixed), et_quantum, 10, 100);
    
    
    //showing all the widgets in the window
    gtk_widget_show_all(window);
    
}//initialize

void generate_label(char* dest, int index){
    int lenght = snprintf(NULL, 0,"%d",index);
    char* str = malloc(lenght+1);
    char* msj;
    msj = "Proceso ";
    snprintf(str, lenght+1, "%d",index);
    dest = (char*) malloc(1 + strlen(msj) + strlen(str));
    strcpy(dest, msj);
    strcat(dest, str);
    gtk_label_set_text(GTK_LABEL(running_process),dest);
}

int main(int argc, char **argv) {
     printf("Inicio \n");
    //Creating the app that contains the window

    GtkApplication *app;

    //return status of the app
    int status;

    //Creates the application
    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(initialize), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    
    
    return status;
    
}//main
