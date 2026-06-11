<<<<<<< HEAD
import pandas as pd

def ejecutar_benchmarking():
    ruta_res = "data/outputs/resultados.csv"
    try:
        df = pd.read_csv(ruta_res)
        num_procesos = len(df)
        
        espera_promedio = df['waiting_time'].mean()
        max_espera = df['waiting_time'].max()
        tiempo_total_ejecucion = df['completion_time'].max()
        
        print("\n=======================================================")
        print("         BENCHMARK GLOBAL DEL SISTEMA OPERATIVO        ")
        print("=======================================================")
        print(f" Total de procesos evaluados : {num_procesos}")
        print(f" Tiempo total de simulación  : {tiempo_total_ejecucion} unidades de reloj")
        print(f" Tiempo de espera promedio   : {espera_promedio:.2f} unidades")
        print(f" Tiempo de espera máximo     : {max_espera} unidades")
        print("=======================================================\n")
        
    except FileNotFoundError:
        print("❌ Error: No se encontró 'resultados.csv' para realizar el Benchmark.")

if __name__ == "__main__":
    ejecutar_benchmarking()
=======
import subprocess
import time
import pandas as pd

results = []

sizes = [100, 500, 1000, 5000]

for size in sizes:
    start = time.time()

    subprocess.run([
        "./bin/main",
        str(size)
    ])

    end = time.time()

    results.append({
        "size": size,
        "time": end - start
    })

pd.DataFrame(results).to_csv(
    "reports/csv/benchmark.csv",
    index=False
)
>>>>>>> 6ca838b20c0ca67b15a8b7b98d01f6a6281f7c5c
