#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "circular_queue.h"
#include "memory_manager.h"

#define MAX_PROCESOS 200

// Estructura local para guardar los atributos extendidos de los procesos
typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
    int priority;
    int memory_required;
    int ram_address;
} ProcessAttr;

int main() {
    printf("=== INICIANDO SIMULADOR MINI-OS (ENTORNO N-PROCESOS) ===\n");

    // Instanciar estructuras globales usando el esqueleto modular
    Queue* jobQueue = queue_create();               // Disco Duro (Largo Plazo)
    CircularQueue* readyQueue = cq_create(MAX_PROCESOS); // RAM CPU (Corto Plazo)
    MemoryManager* RAM = mm_create(1000);           // RAM de 1000 MB
    
    ProcessAttr tablaProcesos[MAX_PROCESOS + 1];

    // 1. LEER LOS PROCESOS DESDE LA RUTA DE ENTRADA OFICIAL
    FILE* csv_in = fopen("data/inputs/processes.csv", "r");
    if (!csv_in) {
        printf("❌ Error: No se encontro 'data/inputs/processes.csv'. Corre primero el generador.\n");
        return 1;
    }

    char buffer[128];
    if (fgets(buffer, sizeof(buffer), csv_in) == NULL) { // Brincar encabezado
        fclose(csv_in);
        return 1;
    }

    int totalProcesos = 0;
    while (fgets(buffer, sizeof(buffer), csv_in)) {
        int pid, burst, priority, mem;
        sscanf(buffer, "%d,%d,%d,%d", &pid, &burst, &priority, &mem);
        
        tablaProcesos[pid].pid = pid;
        tablaProcesos[pid].burst_time = burst;
        tablaProcesos[pid].remaining_time = burst;
        tablaProcesos[pid].priority = priority;
        tablaProcesos[pid].memory_required = mem;
        tablaProcesos[pid].ram_address = -1;

        enqueue(jobQueue, pid); // Metemos el PID al disco duro
        totalProcesos++;
    }
    fclose(csv_in);
    printf("✔ Carga exitosa: %d procesos en la Cola de Trabajos (Disco).\n\n", totalProcesos);

    // 2. CICLO DE SIMULACIÓN ASÍNCRONA
    int currentTime = 0;
    int quantum = 2;
    int procesosTerminados = 0;

    // Arreglos temporales para escribir el historial ordenado al final
    int historial_pid[MAX_PROCESOS];
    int historial_completion[MAX_PROCESOS];
    int historial_waiting[MAX_PROCESOS];

    while (procesosTerminados < totalProcesos) {
        
        // Intentar pasar procesos del Disco (jobQueue) a la RAM (readyQueue)
        while (jobQueue->front != NULL) {
            int proximo_pid = jobQueue->front->data;
            int tamano_req = tablaProcesos[proximo_pid].memory_required;

            // Intentar alojar en memoria RAM usando First Fit
            int dir_asignada = mm_allocate_first_fit(RAM, tamano_req);
            
            if (dir_asignada != -1) {
                // Si cupo, lo sacamos del disco y lo mandamos a la cola circular de la CPU
                dequeue(jobQueue);
                tablaProcesos[proximo_pid].ram_address = dir_asignada;
                cq_enqueue(readyQueue, proximo_pid);
                printf("[RELOJ: %d u] -> P%d entro a la RAM (Direccion base: %d, Tamaño: %d MB).\n", 
                       currentTime, proximo_pid, dir_asignada, tamano_req);
            } else {
                // Si el proceso del frente no cabe, detenemos la busqueda transitoria
                break;
            }
        }

        // Ejecutar el Round Robin en la CPU si hay procesos listos en RAM
        if (readyQueue->size > 0) {
            int current_pid = cq_dequeue(readyQueue);
            
            int tiempo_ejecucion = (tablaProcesos[current_pid].remaining_time > quantum) ? quantum : tablaProcesos[current_pid].remaining_time;
            tablaProcesos[current_pid].remaining_time -= tiempo_ejecucion;
            currentTime += tiempo_ejecucion;

            if (tablaProcesos[current_pid].remaining_time > 0) {
                // No ha terminado, regresa al final de la cola circular
                cq_enqueue(readyQueue, current_pid);
            } else {
                // ¡El proceso termino!
                int comp_time = currentTime;
                int wait_time = comp_time - tablaProcesos[current_pid].burst_time;

                // Guardar en el historial para el reporte CSV
                historial_pid[procesosTerminados] = current_pid;
                historial_completion[procesosTerminados] = comp_time;
                historial_waiting[procesosTerminados] = wait_time;

                // Liberar memoria RAM
                mm_free(RAM, tablaProcesos[current_pid].ram_address);
                procesosTerminados++;
                
                printf("[RELOJ: %d u] -> ✔ P%d FINALIZO. RAM liberada en direccion %d.\n", 
                       currentTime, current_pid, tablaProcesos[current_pid].ram_address);
            }
        } else {
            // Prevenir bloqueos si un proceso excede el tamaño total de la memoria
            if (jobQueue->front != NULL) {
                int pid_colgado = dequeue(jobQueue);
                printf("[ALERTA] -> P%d requiere %d MB. Supera la capacidad de la RAM. Cancelado.\n", 
                       pid_colgado, tablaProcesos[pid_colgado].memory_required);
                procesosTerminados++;
            }
        }
    }

    // 3. EXPORTAR RESULTADOS ORDENADOS POR PID (Insertion Sort)
    for (int i = 1; i < procesosTerminados; i++) {
        int key_pid = historial_pid[i];
        int key_comp = historial_completion[i];
        int key_wait = historial_waiting[i];
        int j = i - 1;
        while (j >= 0 && historial_pid[j] > key_pid) {
            historial_pid[j + 1] = historial_pid[j];
            historial_completion[j + 1] = historial_completion[j];
            historial_waiting[j + 1] = historial_waiting[j];
            j--;
        }
        historial_pid[j + 1] = key_pid;
        historial_completion[j + 1] = key_comp;
        historial_waiting[j + 1] = key_wait;
    }

    FILE* csv_out = fopen("data/outputs/resultados.csv", "w");
    if (!csv_out) {
        printf("❌ Error al crear el archivo de salida.\n");
        return 1;
    }
    fprintf(csv_out, "pid,completion_time,waiting_time\n");
    for (int i = 0; i < procesosTerminados; i++) {
        if (historial_pid[i] > 0) {
            fprintf(csv_out, "%d,%d,%d\n", historial_pid[i], historial_completion[i], historial_waiting[i]);
        }
    }
    fclose(csv_out);
    printf("\n✔ [C] Resultados consolidados en 'data/outputs/resultados.csv'\n");

    // Limpieza de memoria dinamica
    queue_destroy(jobQueue);
    cq_destroy(readyQueue);
    mm_destroy(RAM);

    return 0;
}