<<<<<<< HEAD
import csv
import os
import random

def generar_lote_procesos(num_procesos=50, ruta_salida="data/inputs/processes.csv"):
    # Asegurar que el directorio de destino exista
    os.makedirs(os.path.dirname(ruta_salida), exist_ok=True)
    
    columnas = ["pid", "burst_time", "priority", "memory_required"]
    
    with open(ruta_salida, mode="w", newline="", encoding="utf-8") as file:
        writer = csv.writer(file)
        writer.writerow(columnas)
        
        for pid in range(1, num_procesos + 1):
            burst_time = random.randint(1, 15)       # Ráfaga de CPU (1-15 u)
            priority = random.randint(1, 5)          # Prioridades (1-5)
            memory_required = random.randint(20, 300) # Memoria RAM (20-300 MB)
            writer.writerow([pid, burst_time, priority, memory_required])
            
    print(f"✔ [Python] Generados {num_procesos} procesos en '{ruta_salida}'.")

if __name__ == "__main__":
    generar_lote_procesos(40)       
=======
import random

for i in range(10):

    process = {

        "pid": i,

        "burst": random.randint(1, 20),

        "memory": random.randint(10, 500)
    }

    print(process)
>>>>>>> 6ca838b20c0ca67b15a8b7b98d01f6a6281f7c5c
