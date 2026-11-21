# Group 9 单轴拉伸仪补充资料

对照 [项目主页](../README.md) 筛选。仓库已有最终设计、实验报告、海报、演示文稿、夹具 STL 和代码 PDF。这里补充报告背后的早期测量记录、传感器检查方法和开发阶段的曲线工作表。以下来源路径均相对于课程文件夹 `ECE 442`。

## 1. 从原始数据复核早期丁腈手套试验

优先打开 [161 行的原始采集 CSV](experiments/baseline/nitrile_baseline_mm.csv)。两列依次为力（N）和传感器距离（mm），每个字段自带单位，没有表头。与 `milestone1/milestone1.xlsx` 的 A2:B162 按 CSV 的记录精度逐行一致（力保留一位小数，距离为整毫米）。该工作簿 D2 记录试样宽 20 mm、厚 76.2 μm。

峰值力为 19.4 N，初始截面积为 20 × 0.0762 = 1.524 mm²。峰值工程应力为 **19.4 ÷ 1.524 = 12.73 MPa**，与 `milestone1/Team Milestone #1.pdf` 的团队答复一致。报告指出早期曲线的弹性段难以辨认，因此没有给出可靠的杨氏模量。距离读数需要参考起始位置和标距，才能换算为应变。

[另一份 314 行采集 CSV](experiments/baseline/force_distance_cm.csv) 使用 N 和 **cm**，原始记录未标明样品身份。它保留为独立采集，便于检查距离读数的变化。两份 CSV 均按原字节复制，来源分别为 `milestone1/minestone_1.csv` 和 `milestone1/milestone_1.csv`。

## 2. 检查两路传感器

| 文件 | 来源 | 能核对什么 |
| --- | --- | --- |
| [超声测距对照](calibration/ultrasonic_distance.csv) | `HW1/sensorData.csv.xlsx`，Sheet1 B4:D10 | 7 个已知距离。残差定义为实际距离换算为 cm 后减去测量距离。450 mm 对应的读数为 35 cm，相差 10 cm。 |
| [称重对照](calibration/load_cell.csv) | `HW1/sensorData.xlsx`，Sheet1 B2:D17 | 16 个标称重量，范围为 0–3000 g。测量列按原表记为 kg，残差列为 kg。它记录的是一次个人作业中的读数，应用到最终装置时仍需重新校准。 |
| [可编辑 Arduino 采样草图](firmware/control_and_sampling/control_and_sampling.ino) | `milestone4/control_and_sampling/control_and_sampling.ino` | 独立检查 HX711 与超声测距模块。打开同名草图目录，安装 `HX711.h` 对应的 HX711 库；串口为 9600 baud。原始代码按字节保留。 |

两份校准 CSV 从工作簿数值列导出，表头写明单位。它们针对早期传感器，最终报告给出的每种材料试验次数为 1。

草图使用 D4 接 HX711 DOUT，D5 接 SCK，D2 接超声 Echo，D3 接 Trig；输出原始均值、标为 g 的载荷和以 cm 计的距离。草图的默认系数为斜率 1、截距 0，第二列要在标定后才能解释为克数。源码取 11 个距离样本的中位值、10 次称重读数的平均值，且排序时用整数暂存距离，可能损失小数精度。这份采样草图不包含最终系统的 LCD、手机或电机控制；此次整理仅核查源文件和接线定义，未连接实物。

## 3. 查看开发阶段的数据处理

[蓝、白两组实验工作簿](experiments/development/blue_white_trials.xlsx) 来自 `milestone4/milestone4.xlsx`。两张图和公式均保留，可在 Excel 中直接查看图表所引用的数据。图名里的 `Bule one` 是原文件的拼写。

| 原图标签 | 输入列、行 | 图的 X / Y 列 | 成对数据 |
| --- | --- | --- | ---: |
| Bule one | D3:E23 | I / H | 21 |
| white one | D29:E62 | H / I | 34 |

两段的应力、应变派生列交换了位置，不能用同一列顺序拼接。原工作簿只给颜色标签。已检查的文件中没有最终 MATLAB 代码所读取的 `data2.xlsx`，也缺少从颜色标签到最终胶种和试次的对应记录。该表保留了两张开发曲线的计算过程；最终乳胶、丁腈结果请引用仓库里的实验报告。整理副本已移除 Excel 保存路径和文档属性中的编辑者信息，工作表及图表 XML 均与原件逐字节一致。

## 4. 追溯早期选件

[四项方案估价](design/proposed_parts.csv) 来自 `milestone3/parts list.xlsx` 的 Sheet1 D2:E5。原表列出绳、绞盘、螺钉和 LCD，金额沿用表中的美元估价。绞盘属于早期选项；最终物理设计报告描述的是伺服电机。此表适合解释方案演变，不能当作最终采购清单或已付金额。

## 取舍记录

最终目录中的设计 PDF、实验 PDF、STL、海报及演示已与远端同名文件的 Git blob 哈希比对。课堂讲义、课表、花名册、作业模板、参考论文和跨版本的重复报告均未收入。另一份夹具 STL 位于参考资料旁，缺少与团队最终版本的修订记录。名为 `milestone1/milestone_1.ino` 的文件是 macOS 书签，实际可读的采样源码来自上文列出的 Milestone 4 目录。
