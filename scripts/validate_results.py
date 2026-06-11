import pandas as pd

def validar_consistencia_datos():
    try:
        df_in = pd.read_csv("data/inputs/processes.csv")
        df_out = pd.read_csv("data/outputs/resultados.csv")
        df = pd.merge(df_in, df_out, on="pid")
        
        errores = 0
        print("Iniciando auditoría lógica de la simulación en C...")
        
        for idx, row in df.iterrows():
            # Regla fundamental: El tiempo de finalización no puede ser menor al burst
            if row['completion_time'] < row['burst_time']:
                print(f"❌ Inconsistencia en P{row['pid']}: Finalización ({row['completion_time']}) menor que Ráfaga ({row['burst_time']})")
                errores += 1
                
            # Regla fundamental: Relación matemática Turnaround / Waiting
            if row['completion_time'] - row['burst_time'] != row['waiting_time']:
                print(f"❌ Inconsistencia matemática en P{row['pid']}: Espera inválida.")
                errores += 1
                
        if errores == 0:
            print("✔ [VALIDACIÓN PASADA]: Los resultados de la simulación en C son matemáticamente consistentes.")
        else:
            print(f"❌ [FALLO]: Se encontraron {errores} anomalías en los resultados.")
            
    except Exception as e:
        print(f"❌ No se pudo completar la validación: {e}")

if __name__ == "__main__":
    validar_consistencia_datos()