# 传感器数据实时波形（原始值 vs 滤波值）
# 用法：1) 烧录 code/14-filter（串口输出：原始值,滤波值）
#       2) 关掉串口监视器，改下面的 COM 号
#       3) python sensor_waveform.py

import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque

# 解决中文显示问题
plt.rcParams['font.sans-serif'] = ['Microsoft YaHei', 'SimHei']
plt.rcParams['axes.unicode_minus'] = False

ser = serial.Serial('COM10', 115200, timeout=0)

raws = deque(maxlen=300)
filters = deque(maxlen=300)

fig, ax = plt.subplots()
line_raw, = ax.plot([], [], label='原始值', lw=1)
line_filtered, = ax.plot([], [], label='滤波值', lw=1)
ax.set_ylim(0, 4095)
ax.set_xlim(0, 300)
ax.legend()
ax.set_title('传感器数据（原始 vs 滤波）')

def update(frame):
    if ser.in_waiting:
        data = ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
        for s in data.split('\n'):
            if ',' in s:
                try:
                    r, f = s.split(',')
                    raws.append(int(r))
                    filters.append(int(f))
                except ValueError:
                    pass

    line_raw.set_data(range(len(raws)), list(raws))
    line_filtered.set_data(range(len(filters)), list(filters))
    return line_raw, line_filtered,

ani = animation.FuncAnimation(fig, update, interval=30)
plt.show()
