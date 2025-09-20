# Chord Pico - Polaris Chord 风格的迷你控制器
[Click here for the English version of this guide.](README.md)

<img src="doc/main.jpg" width="70%">

特性：
* 全球第一个 Polaris Chord 控制器。
* 几乎所有部件均为 3D 打印。
* 霍尔效应传感器按键，可自定义触发行程。
* RGB 按键灯光，支持 HID 灯光。
* 和街机一致的推杆传感器设计；
* 完全开源。

感谢许多尊敬的爱好者和公司将他们的工具或材料免费或开源（KiCad，OnShape，InkScape，Raspberry 相关工具, 嘉立创等）。

特别感谢社区项目和开发者的帮助，还有如下项目：
* RP_Silicon_KiCad: https://github.com/HeadBoffin/RP_Silicon_KiCad
* Type-C: https://github.com/ai03-2725/Type-C.pretty

## 关于许可证
它是 CC-NC 授权。所以你只能给自己和你的朋友 DIY，不能利用这个项目赚钱，比如收费的代做，出售整机等，连源作者都提的抄袭或者稍微改改换个名字来打擦边球就更不可以了。注意团购和拼单订购原始元器件是合理的，非盈利的方式卖掉剩余的元器件也是可以接受的。

如果希望找我购买成品或者获取商用授权，请联系我（Discord，QQ 群，闲鱼）。
* Discord 服务器邀请：https://discord.gg/M8f2PPQFEA
* QQ 群：854535476
* 闲鱼：whowe12345

## 其他项目
你也可以查看我其他的酷炫项目。

<img src="https://github.com/whowechina/popn_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/iidx_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/iidx_teeny/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/chu_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/mai_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/diva_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/aic_pico/raw/main/doc/main.gif" height="100px"> <img src="https://github.com/whowechina/groove_pico/raw/main/doc/main.gif" height="100px">  <img src="https://github.com/whowechina/geki_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/musec_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/ju_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/bishi_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/nos_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/voltex_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/chord_pico/raw/main/doc/main.jpg" height="100px">

* Popn Pico: https://github.com/whowechina/popn_pico
* IIDX Pico: https://github.com/whowechina/iidx_pico
* IIDX Teeny: https://github.com/whowechina/iidx_teeny
* Chu Pico: https://github.com/whowechina/chu_pico
* Mai Pico: https://github.com/whowechina/mai_pico
* Diva Pico: https://github.com/whowechina/diva_pico
* AIC Pico: https://github.com/whowechina/aic_pico
* Groove Pico: https://github.com/whowechina/groove_pico
* Geki Pico: https://github.com/whowechina/geki_pico
* Musec Pico: https://github.com/whowechina/musec_pico
* Ju Pico: https://github.com/whowechina/ju_pico
* Bishi Pico: https://github.com/whowechina/bishi_pico
* Nos Pico: https://github.com/whowechina/nos_pico
* Voltex Pico: https://github.com/whowechina/voltex_pico
* Chord Pico: https://github.com/whowechina/chord_pico

## **声明** ##
我在个人业余时间内制作了这个项目，并将继续改进这个项目。我已尽我所能确保所有内容的准确性和功能性，但总有可能出现错误。如果你因使用这个开源项目而造成时间或金钱的损失，我不能负责。感谢你的理解。

### 如何制作
#### PCB 和元件
* 前往 JLCPCB 或你喜欢的任何 PCB 制造商，使用 gerber 压缩文件下单（最新的 `Production\PCB\chord_pico_xxx.zip`）。选择常规 FR-4 板材，黑色，**1.6mm** 厚度。

* 1x Raspberry Pi Pico 或针脚兼容的克隆板，推荐带 Type-C 接口的版本。  
  https://www.raspberrypi.com/products/raspberry-pi-pico
* 1x USB Type-C 插座（型号：918-418K2023S40001 或 KH-TYPE-C-16P）。
* 1x ADG706BRUZ (28-TSSOP) 16 对 1 模拟信号多路复用器 (U2)。  
  https://www.analog.com/en/products/adg706.html
* 12x SS49E (SOT23) 线性霍尔效应传感器 (H1 到 H12)。
* 10x ITR1502SR40A/TR8 反射式光电开关 (IR1 到 IR10)。  
  https://www.lcsc.com/product-detail/C183793.html
* 1x TPS7A2042PDBVR (4.2V) 或 LP5907MFX-4.5 (4.5V) LDO (SOT23-5)，(U7)。
  https://www.ti.com/product/TPS7A20/part-details/TPS7A2042PDBVR
* 1x LM4040 3.0V 并联电压基准，SOT23-3 封装 (U6). 市场上有很多型号，确保它是 3.0V 并且是在 SOT23-3 即可。
* 1x 稳压二极管，3.0V 或 3.3V，SOD-123F 封装 (D1)。
* 42x WS2812B-3528 幻彩 LED (D1 to D42)。D1 到 D12 和 D35 到 D38 是必须的，其他的则是可选，多焊些灯光会更亮。
* 20x 到 30x 0603 0.1uF (0.1~1uF 都可以) 电容。CC1 到 CC3 是必须的，其他事可选的（见后面说明）。
* 3x 0603 5.1kohm 电阻, 2 颗用于 USB (R1, R2)，1 颗用于信号分压 (R4)。
* 1x 0603 2kohm 电阻，用于信号分压 (R3)。
* 10x 0603 200ohm 电阻，用作光电开关限流 (R5, R7, R9, ... R23)。
* 10x 0603 33kohm 电阻，用作光电开关下拉 (R6, R8, R10, ... R24)。
* 2x ALPS SKHHLWA010 6\*6\*7mm 或者兼容的轻触开关 (SW1, SW2)。  
  https://tech.alpsalpine.com/e/products/detail/SKHHLWA010/

* 板子焊接完成的样子。  
  <img src="doc/pico_pcb1.jpg" width="70%">  
  <img src="doc/pico_pcb2.jpg" width="70%">

### 说明
1. 请特别注意用于 USB 的两个引脚（孔），很容易忘记焊接，或者焊接时留有气泡。为避免这种情况，请从孔的一侧慢慢焊接。  
   <img src="doc/usb_txrx.jpg" width="20%">
2. 去耦电容的数量很多，你不需要全部焊接，可以选择焊接一部分，但尽量均匀分布。

### 测试 PCB
* 现在你可以测试 PCB 了，先将固件烧录进去。
* 很可能所有按键的 LED 会亮起并闪烁。
* 左推杆 LED 会呈现绿色，右推杆 LED 会呈现粉色。
* Chord Pico 应该会被电脑识别为一个 USB HID 设备，这里是测试页面：  
  https://greggman.github.io/html5-gamepad-test/
* 使用终端工具连接到 Chord Pico 的命令行接口：  
  https://googlechromelabs.github.io/serial-terminal/
* 使用 `debug hall` 命令来开关霍尔效应传感器调试模式。开启后，你可以看到实时的传感器数值。可以使用一块小磁铁逐个测试它们。当磁铁靠近对应的传感器时，数值应该会有明显变化。如果你注意到数值异常，请检查模拟信号多路复用器和对应霍尔效应传感器的焊接。
* 使用 `debug fader` 命令来开关推杆传感器调试模式。开启后，你可以看到实时的推杆传感器状态。你可以使用一块白色物体（例如纸张），在传感器上方 5mm 处挥动，看输出的变化。
* 只有当 PCB 完全正常后，才能进行组装。

### 3D 打印
#### 打印参数  
* 材料：PLA 或 PETG。
* 层高：0.2mm
* 支撑：不需要，除非特别说明。
* 文件始终以毫米为单位，而不是英寸。
* 所有部件都可以在 256mm\*256mm 的打印床上放下，不过有些部件需要旋转一下。

#### 部件
* 所有文件都在 `Production\3DPrint` 文件夹中。
* 按键：`Key Combo - All Keys`，无色透明。
* 后底座：`Chord Pico - Rear.stl`，黑色。启用支撑并使用支撑材料以获得更好的螺丝孔表面。
* 前底座：`Chord Pico - Front.stl`，黑色。启用支撑并使用支撑材料以获得更好的螺丝孔表面。
* 面板：`Chord Pico - Panel Combo.3mf`，强烈推荐使用多色系统，其中 “Panel White Layer" 子部件使用白色材料，其他子部件设为黑色。倒置打印。
* 按键挡板：推荐用 `Chord Pico - Brim Insert.stl`，但如果你无法使用热熔螺母，可以改用 `Chord Pico - Brim.stl`（见下文说明）。使用黑色耗材。倒置打印。
* 2x 推杆滑块：推荐用 `Slider PTFE.stl`，但如果你找不到合适 PTFE 管，可以改用 `Slider Thruhole.stl`（见下文说明）。必须使用白色耗材。
* 2x 滑块盖：`Slider Seal.stl`，白色。
* 4x 导轨固定器: `Chord Pico - Rail Fixer.stl`, 颜色不重要。
* 2x 推杆把手: `Fader - Knob.stl`, 一个绿色，一个红色。

#### Notes
1. 对于按键挡板，推荐使用热熔螺母，它比自攻螺纹好用。但如果你买不到或者没有合适工具，请改用自攻版本打印件，注意要慢慢拧，小心别拧过头。
2. 对于推杆滑块，推荐使用 PTFE 管以获得更顺滑的手感。如果找不到合适的 PTFE 管，则可以使用通孔版本。

### 组装
#### 所需其他组件
* 13x M3\*8mm 螺丝用于将 PCB 和前后底座固定在一起。
* 7x M3\*12mm 螺丝用于将面板固定到后底座。
* 7x M2\*10mm 螺丝用于将按键挡板固定到前底座。
* 24x M2\*7mm 或 M2\*6mm 螺丝用于滑块。
* 2x M2\*16~18mm 螺丝用于推杆把手。

* 7x M2\*3mm\*3mm (外径\*高度) 热熔螺母（如果你选这个方案）。

* 1x 2mm\*240mm 钢轴用于按键，如果找不到，可以使用 3x 2mm\*80mm 或 4x 4mm\*60mm，甚至 6x 2mm\*40mm 来组合。

* 4x 2mm\*70mm (直径\*长度) 钢轴用作推杆导轨。

* 12x 0.4\*5\*10\*6N (0.4mm 线径, 5mm 外径, 10mm 自由长度, 6 圈) 弹簧。
* 12x 3mm\*2mm (直径\*高度) 轴向磁化的圆柱形磁铁。
* 一些 2.2mm\*4mm 或 2.3mm\*4mm (内径\*外径) PTFE 管。
* 一些白色硅胶粘合剂，例如 K-704 硅胶工业粘合剂。
* 一些低粘度的阻尼润滑脂，例如润赛的 Type-2。

* 4x 0.3mm\*5mm\*15mm (线径\*外径\*长度) 紧密卷绕的拉簧，用于推杆。

* 一些 0.5~0.8mm 厚的自粘泡棉胶带 (Poron 或 EVA) 用于减震。

* 一些 10mm\*2mm 或 10mm\*2mm (直径\*高度) 硅胶自粘防滑垫。

#### 步骤
请注意，设计未来可能会有所更改，但组装步骤应该会基本不变。所以请忽略某些细节上的小差异。

1. 使用 M3\*6mm 螺丝将 PCB 固定到前后底座上。  
   <img src="doc/assembly_1.jpg" width="70%">

2. 将磁铁嵌入到按键前部的槽位里，并使用一些粘合剂（比如白色 704 硅橡胶）将其固定。
3. 安装按键。使用钢轴穿过所有按键，然后将钢轴嵌入后底座的铰链槽中。  
   <img src="doc/assembly_2.jpg" width="70%">

4. 裁切一些 PTFE 管并将其嵌入到滑块里。它们在滑动推杆时提供顺滑感。如果不使用 PTFE 管，请使用通孔滑块并跳过此步骤。  
   <img src="doc/assembly_3.jpg" width="40%">

5. 将拉簧嵌入到推杆滑块里，然后使用 M2 螺丝将滑块盖固定到推杆滑块上。  
   <img src="doc/assembly_4.jpg" width="36%"> <img src="doc/assembly_5.jpg" width="40%">

6. 确保钢轴已经插入推杆滑块，把滑块组合体放入后底座中。然后将弹簧挂到底座上，最后使用 M2 螺丝和导轨固定器将其固定。你可以在钢轴上涂抹一些阻尼脂来减少滑块的回弹。  
   <img src="doc/assembly_6.jpg" width="30%"> <img src="doc/assembly_7.jpg" width="50%">

7. 安装按键的弹簧。  
   <img src="doc/assembly_8.jpg" width="70%">

8. 现在进行另一次测试。通电并校准按键。按键和推杆应该正常工作。如果一切正常，请继续下一步。

9. 可选但强烈推荐：使用一些泡棉胶带来减小按键噪音。你需要将泡棉胶带粘贴到 PCB（霍尔传感器正下方）以及按键挡板部分。它们可以显著减少按键下压和抬起时的噪音。  
   <img src="doc/assembly_9.jpg" width="80%">

10. 如果面板在传感器的上方部位是白色材料打印的，请使用黑色马克笔将其涂黑，可以减少传感器被干扰的风险。  
   <img src="doc/assembly_10.jpg" width="70%">

11. 将面板放置到底座上。两个辅助开关在安装过程中可能会干涉面板，因此需要将右侧推杆向左移动，并轻轻弯曲面板以将其卡入到位。然后使用 M3\*12mm 螺丝将面板固定到底座上。在拧紧时，面板可能会稍微被顶起，这时候你需要松开螺丝，然后在按下面板的同时重新拧紧，以确保其完全就位。  
    <img src="doc/assembly_11.jpg" width="70%">

12. 现在进行另一次测试。通电并校准。确保一切正常工作。

13. 安装旋钮把手。左侧是绿色，右侧是红色。使用最长的 M2 螺丝将它们固定。  
    <img src="doc/assembly_12.jpg" width="70%">

14. 安装按键挡板部分。如果你使用热熔螺母，请先使用合适的工具将其安装到按键挡板中。使用 M2\*10mm 螺丝将按键挡板固定到前底座上。  
    <img src="doc/assembly_13.jpg" width="70%">

15. 将防滑垫粘贴到底部。

16. 通电并重新校准按键。

17. 搞定！  
    <img src="doc/assembly_14.jpg" width="80%">


### 固件
* UF2 文件位于 `Production\Firmware` 文件夹中。
* 对于新设备，按住 BOOTSEL 按钮的同时将 USB 连接到电脑，会出现一个名为 "RPI-RP2" 的磁盘。将 UF2 固件二进制文件拖入其中即可完成烧录。提醒：控制器底部有一个小孔，正对着 BOOTSEL 按钮。
* 如果设备已经有固件，你可以通过命令行使用 `update` 命令，或者在连接 USB 时按住两个辅助按钮进入更新模式。
* 要访问命令行接口，可以使用这个 Web Serial Terminal 工具连接到控制器的命令行端口。（注意：输入 "?" 可以查看帮助）  
  https://googlechromelabs.github.io/serial-terminal/

### 使用方法
* 即插即用。
* 按键映射为 HID 按钮。
* 推杆映射为 HID 的 X 轴 和 Y 轴。
* 使用 `calibrate` 命令校准霍尔效应按键。
* 使用 `trigger` 命令设置触发和恢复距离。

## CAD 源文件
我使用的是 OnShape 的免费订阅。它很强大，但不能将原始设计存档到本地，所以我只能在这里分享链接。STL/DXF/DWG 文件是从这个在线文档导出的。
  https://cad.onshape.com/documents/6bb6f9e65a79e122747d4a2d/w/1074c535f59b2616ddc9d820/e/61a1d98d42199565d2d1adba
