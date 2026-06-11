import os
import pandas as pd
import matplotlib.pyplot as plt

def generar_reporte_visual():
    ruta_entrada = "data/inputs/processes.csv"
    ruta_salida = "data/outputs/resultados.csv"
    carpeta_reportes = "reports/png"
    
    try:
        # 1. Carga e integración de datos
        df_in = pd.read_csv(ruta_entrada)
        df_out = pd.read_csv(ruta_salida)
        df = pd.merge(df_in, df_out, on="pid")
        
        os.makedirs(carpeta_reportes, exist_ok=True)
        plt.style.use('seaborn-v0_8-whitegrid' if 'seaborn-v0_8-whitegrid' in plt.style.available else 'default')

        # ---- GRÁFICA 1: Ciclo de Vida ----
        plt.figure(figsize=(10, 5))
        plt.bar(df['pid'].astype(str), df['waiting_time'], color='#3498db', alpha=0.7, label='Tiempo de Espera')
        plt.plot(df['pid'].astype(str), df['completion_time'], color='#e74c3c', marker='o', linewidth=2, label='Tiempo de Finalización')
        plt.title('Rendimiento Individual por Proceso', fontsize=12, fontweight='bold')
        plt.xlabel('ID del Proceso (PID)')
        plt.ylabel('Unidades de Reloj')
        plt.legend()
        plt.tight_layout()
        plt.savefig(f"{carpeta_reportes}/1_rendimiento_individual.png", dpi=300)
        plt.close()

        # ---- GRÁFICA 2: Histograma de Equidad ----
        plt.figure(figsize=(10, 5))
        plt.hist(df['waiting_time'], bins=5, color='#2ecc71', edgecolor='black', alpha=0.7)
        plt.title('Distribución de Tiempos de Espera (Equidad Round Robin)', fontsize=12, fontweight='bold')
        plt.xlabel('Rango de Espera')
        plt.ylabel('Cantidad de Procesos')
        plt.tight_layout()
        plt.savefig(f"{carpeta_reportes}/2_distribucion_equidad.png", dpi=300)
        plt.close()

        # ---- GRÁFICA 3: Dispersión Greedy ----
        plt.figure(figsize=(10, 5))
        plt.scatter(df['memory_required'], df['waiting_time'], color='#9b59b6', s=120, edgecolor='black', alpha=0.8)
        for i, txt in enumerate(df['pid']):
            plt.annotate(f"P{txt}", (df['memory_required'][i]+2, df['waiting_time'][i]), fontsize=8)
        plt.title('Correlación Memoria vs Tiempo de Espera (First Fit)', fontsize=12, fontweight='bold')
        plt.xlabel('Memoria RAM Requerida (MB)')
        plt.ylabel('Tiempo de Espera')
        plt.tight_layout()
        plt.savefig(f"{carpeta_reportes}/3_correlacion_greedy.png", dpi=300)
        plt.close()

        # ---- GRÁFICA 4: Tendencia de Líneas ----
        plt.figure(figsize=(10, 5))
        plt.plot(df['pid'].astype(str), df['waiting_time'], label='Tendencia de Espera', color='#4CAF50', marker='D', markersize=6, linewidth=2, linestyle='--')
        plt.plot(df['pid'].astype(str), df['burst_time'], label='Carga de Trabajo (Burst)', color='#FFC107', marker='s', markersize=6, linewidth=2)
        plt.title('Tendencia Secuencial de Tiempos (Orden de PID)', fontsize=12, fontweight='bold')
        plt.xlabel('ID del Proceso (PID)')
        plt.ylabel('Unidades de Reloj')
        plt.grid(True, linestyle='-', alpha=0.3)
        plt.legend()
        plt.tight_layout()
        plt.savefig(f"{carpeta_reportes}/4_tendencia_lineas.png", dpi=300)
        plt.close()

        print(f"✔ [Python] Las 4 gráficas analíticas fueron exportadas con éxito en '{carpeta_reportes}/'.")

    except FileNotFoundError:
        print("❌ Error: Faltan archivos de datos en 'data/'. Ejecuta primero la simulación.")

if __name__ == "__main__":
    generar_reporte_visual()