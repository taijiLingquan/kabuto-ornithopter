# code/ 目录说明

按课分目录，每课一个 `main.cpp`（第 6 课是类封装，含 `.h` / `.cpp`）。

**所有课共用同一份 `platformio.ini`**（见仓库根目录 README「快速上手」），不同课只是 `src/main.cpp` 内容不同。

## 目录对照

| 目录 | 内容 | 外设 / 引脚 |
|---|---|---|
| `01-hello/` | 串口 Hello | 无 |
| `02-led/` | 点灯 | WS2812(GPIO21) + 外接 LED(GPIO8) |
| `03-pwm-breathing/` | PWM 呼吸灯 | 外接 LED(GPIO8) |
| `04-millis-nonblocking/` | 非阻塞双定时器 | LED(GPIO8) + WS2812(GPIO21) |
| `05-serial-command/` | 串口指令控制 | LED(GPIO8) + WS2812(GPIO21) |
| `06-blinker-class/` | 类封装（Blinker） | LED(GPIO8) |
| `07-button/` | 按键输入 + 消抖 | 按键(GPIO2) + LED(GPIO8) |
| `08-buzzer/` | 蜂鸣器（SOS 声音） | 蜂鸣器模块 S 脚(GPIO9) |
| `09-light-sensor/` | 模拟输入（夜灯） | 光敏模块 S 脚(GPIO9) + LED(GPIO7) |
| `10-light-alarm/` | 小综合：光控报警器 | 光敏(GPIO9) + LED(GPIO7) + 蜂鸣器(GPIO8) + WS2812(GPIO21) |
| `11-serial-csv/` | 串口数据流（CSV） | 光敏(GPIO9) |
| `12-i2c-scanner/` | I2C 扫描器 | SDA(GPIO4) + SCL(GPIO5) |
| `13-interrupt/` | 中断（按键计数） | 按键(GPIO2) |
| `14-filter/` | 滤波（移动平均） | 光敏(GPIO9) |
| `15-state-machine/` | 状态机（光控报警） | 光敏(GPIO9) + LED(GPIO7) + 蜂鸣器(GPIO8) |

## 使用方法

1. 建一个 PlatformIO 项目（Arduino 框架，board = esp32-s3-devkitc-1）。
2. 用根目录 README 里的 `platformio.ini`。
3. 把对应课的 `main.cpp` 复制到项目的 `src/` 下（第 6 课把三个文件都复制）。
4. 烧录：拔线 → 按住 BOOT → 插线 → 松手 → Upload。
