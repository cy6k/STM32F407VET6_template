# STM32F407VET6 标准库工程模板 (非阻塞 TIM6 时基)

本项目是一个基于 STM32F407VET6 微控制器的标准外设库（SPL）工程模板。旨在为开发者提供一个干净、结构清晰的底层开发框架。

最大的亮点是：**内置了基于 TIM6 的非阻塞时基（类似 Arduino 的 `millis()`）**，彻底告别 `HAL_Delay()` 或阻塞式 `delay_ms()`，让你的 MCU 能够轻松实现多任务时间片轮询。

## ✨ 特性

- **芯片型号**：STM32F407VET6 (Flash: 512KB, RAM: 192KB)
- **库支持**：STM32F4xx 标准外设库 (Standard Peripheral Library)
- **非阻塞延时**：利用 TIM6 产生 1ms 中断，实现 `get_tick()` 与 `delay_ms()` 的非阻塞版本。
- **工程管理**：结构清晰的目录划分，方便添加外设驱动。
- **一键清理**：附带 `keilkill.bat`，方便清理 Keil 编译产生的临时文件，减少 Git 仓库体积。
- **IDE支持**：Keil MDK (uvprojx)

## 📁 目录结构

```text
├── Hardware        # 外设驱动存放区（如 LED、按键、串口、OLED 等）
├── Libraries       # STM32 标准库文件 (CMSIS 和 STM32F4xx_StdPeriph_Driver)
├── Start           # 启动文件 (startup_stm32f40_41xxx.s) 及系统时钟配置
├── User            # 用户应用代码 (main.c, stm32f4xx_it.c 等)
├── Project.uvprojx # Keil MDK 工程文件
├── Project.uvoptx  # Keil MDK 工程选项文件
├── keilkill.bat    # 清理 Keil 编译中间文件的批处理脚本
└── .gitignore      # Git 忽略文件配置
