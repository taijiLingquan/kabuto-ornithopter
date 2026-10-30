# 仿生扑翼甲斗王 · Beetle Ornithopter

> 基于国产甲斗王合金腰带的**仿生扑翼独角仙飞行体**研究原型。
> 灵感来源：假面骑士甲斗王 · 甲斗昆虫仪（Kamen Rider Kabuto Zecter）

**最终目标**：大四毕业前完成 V1.0 —— 扑翼飞行 + 磁吸对接 + 音效/灯效 + AI 语音交互。
**现实定位**：分阶段交付"有数据、有代码、有视频"的子系统，非一步到位的科幻版。

---

## 当前进度（2026-10）

**大一上**，已完成 ESP32-S3-Zero 入门 9 课 + 1 个小综合项目（C++ / Arduino 框架）：

| 课 | 内容 | 学到的核心 |
|---|---|---|
| 1 | 环境跑通 + 串口 Hello | `Serial` 对象、`setup()/loop()`、烧录流程 |
| 2 | 点灯（WS2812 + 外接 LED） | 库、GPIO、`pinMode`/`digitalWrite` |
| 3 | PWM 呼吸灯 | 占空比、`analogWrite` |
| 4 | 非阻塞闪烁 | `millis()` vs `delay()` |
| 5 | 串口指令控制 | `Serial.read`、命令解析 |
| 6 | 类封装 | `Blinker.h/.cpp/main.cpp` |
| 7 | 按键输入 | `digitalRead`、消抖 |
| 8 | 蜂鸣器发声 | 输出外设、SOS 声音 |
| 9 | 模拟输入 | `analogRead`、`map`、光敏传感器 |
| 🎯 | 小综合：光控报警器 | 多模块整合、`else if` 链、状态灯 |

**下一个里程碑**：2027-08 单翅测试台 + 第一组升力-频率数据。

---

## 硬件

- 主控：**微雪 ESP32-S3-Zero**（芯片 ESP32-S3FH4R2：4MB Flash + 2MB PSRAM）
- 板载：WS2812 RGB 彩灯（GPIO21）
- 外设：面包板、LED、按键、有源蜂鸣器模块（S/V/G 三脚）
- 开发环境：VS Code + PlatformIO（Arduino 框架）

> ⚠️ 这块板子的两个"脾气"（踩坑记录，详见 `docs/`）：
> 1. **没有 USB 转串口芯片**——串口走芯片自带 USB，需 `-DARDUINO_USB_CDC_ON_BOOT=1`；
> 2. 烧录要**按住 BOOT 再插线**进下载模式（COM9），烧完按 RESET 回运行模式（COM10）。

---

## 快速上手（复现）

1. 装 VS Code + PlatformIO 插件。
2. 新建项目，`platformio.ini` 用：

```ini
[env:esp32s3]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino
monitor_speed = 115200
board_build.flash_size = 4MB
board_build.arduino.memory_type = qio_qspi
board_build.flash_mode = qio
board_build.psram_type = qio
board_upload.flash_size = 4MB
board_upload.maximum_size = 4194304
board_build.partitions = default.csv
board_build.extra_flags = 
  -DBOARD_HAS_PSRAM
  -DARDUINO_USB_CDC_ON_BOOT=1
lib_deps = adafruit/Adafruit NeoPixel
```

3. 把 `code/` 里对应课的 `main.cpp` 复制进项目的 `src/`。
4. 烧录：**拔线 → 按住 BOOT → 插线 → 松手 → 点 Upload**。
5. 看串口输出：按 **RESET** 回运行模式，用**出现的那个 COM 口**（不是烧录的口）。

---

## 目录

- `docs/` —— 学习路线周计划、分阶段采购清单、课程笔记
- `code/` —— 课程代码（C++ / Arduino，按课分目录）
- `logs/` —— 每周进展记录（每周日更新）

## 技术路线

- 飞控：ESP32-S3（后续视精度需求加 STM32）
- 语音：ESP-SR + INMP441；音效：DFPlayer Mini
- 对接：磁吸 + 霍尔检测；定位：AprilTag → UWB

## 安全说明

宿舍只做无桨测试；装桨测试在室外；锂电池用防爆袋。
