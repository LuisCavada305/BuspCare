import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

plt.style.use('fivethirtyeight')

def animate(i):
    # Leitura de dados
    data = pd.read_csv('PdM_telemetry.csv', index_col='datetime')
    
    # Limita o número de pontos de dados mostrados (opcional)
    data = data[-100:]
    
    # Obtém dados de cada coluna
    x = data.index
    y2 = data['volt']
    y3 = data['rotate']
    y4 = data['pressure']
    y5 = data['vibration']

    plt.cla()

    # Plota os dados
    plt.plot(x, y2, label='Volt')
    plt.plot(x, y3, label='Rotate')
    plt.plot(x, y4, label='Pressure')
    plt.plot(x, y5, label='Vibration')

    # Adiciona título e legendas
    plt.title('Machine Telemetry Data')
    plt.ylabel('Values')
    plt.legend(loc='upper left')
    plt.tight_layout()

ani = FuncAnimation(plt.gcf(), animate, interval=1000)

plt.tight_layout()
plt.show()
