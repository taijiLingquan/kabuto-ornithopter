# python/ 上位机说明

ESP32 通过串口发数据，电脑上用 Python 画实时波形。两个脚本：

| 脚本 | 配合的课 | 串口格式 | 画什么 |
|---|---|---|---|
| `sensor_waveform.py` | 第 10~13 课（`code/14-filter`） | `原始值,滤波值` | 两条线：原始 vs 滤波 |
| `angle_waveform.py` | 第 15~16 课（`code/16` / `code/17`） | `pitch,roll` | 两条线：俯仰 / 横滚 |

## 用法

1. 烧录对应课的 `main.cpp`（确认串口在发数据）。
2. **关掉串口监视器**（串口一次只能被一个程序占用）。
3. 把脚本里的 `COM10` 改成实际串口号。
4. 运行：`python 脚本名.py`

## 依赖

```bash
pip install pyserial matplotlib
```

## 中文显示

脚本里已加：

```python
plt.rcParams['font.sans-serif'] = ['Microsoft YaHei', 'SimHei']
plt.rcParams['axes.unicode_minus'] = False
```

否则中文会显示成方块。
