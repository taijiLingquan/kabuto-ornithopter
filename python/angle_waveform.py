# MPU6050 角度实时波形（上位机）
# 用法：1) 烧录 code/16 或 17 的 main.cpp（串口输出 pitch,roll）
#       2) 关掉串口监视器，改下面的 COM 号
#       3) python angle_waveform.py

import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque

# 解决中文显示问题
plt.rcParams['font.sans-serif'] = ['Microsoft YaHei', 'SimHei']
plt.rcParams['axes.unicode_minus'] = False

ser = serial.Serial('COM10', 115200, timeout=0)

pitches = deque(maxlen=300)
rolls = deque(maxlen=300)

fig, ax = plt.subplots()
line_pitch, = ax.plot([], [], label='pitch(俯仰)', lw=1)
line_roll,  = ax.plot([], [], label='roll(横滚)', lw=1)
ax.set_ylim(-100, 100)
ax.set_xlim(0, 300)
ax.axhline(0, color='gray', lw=0.5)   # 0° 参考线
ax.legend()
ax.set_title('MPU6050 角度')

def update(frame):
    if ser.in_waiting:
        data = ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
        for s in data.split('\n'):
            if ',' in s:
                try:
                    p, r = s.split(',')
                    pitches.append(float(p))
                    rolls.append(float(r))
                except ValueError:
                    pass

    line_pitch.set_data(range(len(pitches)), list(pitches))
    line_roll.set_data(range(len(rolls)), list(rolls))
    return line_pitch, line_roll,

ani = animation.FuncAnimation(fig, update, interval=30)
plt.show()
