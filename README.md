# Chord Pico - Polaris Chord Mini Controller
[点这里可以切换到中文版](README_CN.md)

<img src="doc/main.jpg" width="80%">
<img src="doc/main2.jpg" width="80%">

Features:
* World's first Polaris Chord controller.
* Two versions available: Chord Pico for 15.6 to 21 inches monitors, Chord Pico+ for 21.5 inches and above.
* Almost all parts are 3D printed.
* Hall effect keys with configurable travel distance.
* RGB key lights with HID light support.
* Fader sensors are arcade accurate.
* All open source.

Thanks to the many generous individuals and companies who made their tools or materials free or open source (KiCad, OnShape, InkScape, Raspberry things, JLCPCB and Jiepei).

Special thanks to community projects and developers. And also these projects:
* RP_Silicon_KiCad: https://github.com/HeadBoffin/RP_Silicon_KiCad
* Type-C: https://github.com/ai03-2725/Type-C.pretty

## About the License
It's CC-NC. So DIY for yourself and your friends, don't make money from it. Plagiarism, especially without crediting the original author, is not acceptable. Please note that pooling orders and group buying for raw materials are acceptable. Selling off any leftover components without profit is also acceptable.

If you're interested in buying from me, or in commercial use, please contact me (Discord, QQ group, Goofish).
* My Discord Invitation: https://discord.gg/M8f2PPQFEA
* QQ Group: 854535476
* Goofish: whowe12345

## My Other Projects
You can check out my other cool projects.

<img src="https://github.com/whowechina/popn_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/iidx_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/chu_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/mai_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/diva_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/aic_pico/raw/main/doc/main.gif" height="100px"> <img src="https://github.com/whowechina/groove_pico/raw/main/doc/main.gif" height="100px">  <img src="https://github.com/whowechina/geki_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/musec_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/ju_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/bishi_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/nos_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/voltex_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/chord_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/dance_pico/raw/main/doc/main.jpg" height="100px">
<img src="https://github.com/whowechina/arcade_pico/raw/main/doc/main.jpg" height="100px">

* Popn Pico: https://github.com/whowechina/popn_pico
* IIDX Pico: https://github.com/whowechina/iidx_pico
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
* Dance Pico: https://github.com/whowechina/dance_pico
* Arcade Pico: https://github.com/whowechina/arcade_pico

## **Disclaimer** ##
I made this project in my personal time without any sponsorship. I will continue to improve the project. I have done my best to ensure that everything is accurate and functional, but there's always a chance that mistakes may occur. I cannot be held responsible for any loss of time or money that may result from using this open source project. Thank you for your understanding.

## HOW TO BUILD
### PCB and Components
* Go to JLCPCB or any PCB vendor you like, and place an order with the gerber zip files (latest `Production\PCB\chord_pico_xxx.zip` for Chord Pico or `Production\PCB\chord_plus_xxx.zip` for Chord Pico+), regular FR-4 board, black color, **1.6mm** thickness.

* 1x Raspberry Pi Pico or pin-to-pin compatible clones, those with type-C port are strongly recommended.  
  https://www.raspberrypi.com/products/raspberry-pi-pico
* 1x USB Type-C socket (918-418K2023S40001 or KH-TYPE-C-16P)
* 1x ADG706BRUZ (28-TSSOP) 16 to 1 analog multiplexer (U2).  
  https://www.analog.com/en/products/adg706.html
* 12x SS49E (SOT23) linear Hall effect sensors (H1 to H12).
* 10x ITR1502SR40A/TR8 reflective photosensors (IR1 to IR10).  
  https://www.lcsc.com/product-detail/C183793.html
* 1x TPS7A2042PDBVR (4.2V) or LP5907MFX-4.5 (4.5V) LDO (SOT23-5), (U7).  
  https://www.ti.com/product/TPS7A20/part-details/TPS7A2042PDBVR
* 1x LM4040 3.0V Shunt Voltage Reference, in SOT23-3 (U6). There're many models; make sure it's 3.0V and in an SOT23-3 package.
* Optional: 1x Zener diode 3.0 or 3.3V, in SOD-123F (Z1). It's for extra protection for the GPIO, but the risk is very low.
* 42x WS2812B-3528 RGB LEDs (D1 to D42). D1 to D12 and D35 to D38 are mandatory; others are for better lighting.
* 20x to 30x 0603 0.1uF (0.1~1uF all fine) capacitors. CC1 to CC3 are mandatory; others are optional (see notes below).
* 3x 0603 5.1kohm resistors, 2 for USB (R1, R2) and 1 for signal divider (R4).
* 1x 0603 2kohm resistor for signal divider (R3).
* 10x 0603 200ohm resistors as photosensor current limiters (R5, R7, R9, ... R23).
* 10x 0603 22kohm resistors as photosensor pull-downs (R6, R8, R10, ... R24) (see notes below).
* 2x ALPS SKHHLWA010 6\*6\*7mm or compatible tactile switches (SW1, SW2).  
  https://tech.alpsalpine.com/e/products/detail/SKHHLWA010/

* This is what the Chord Pico board looks like after soldering. Chord Pico+ looks a little different, but the components are the same.  
  <img src="doc/pico_pcb1.jpg" width="70%">  
  <img src="doc/pico_pcb2.jpg" width="70%">

### Notes
1. Be careful of 2 USB pins (holes) for the Pi Pico. It's a common oversight to either forget to solder them or to leave air bubbles during the process. To avoid this, solder slowly from only one side of the hole.  
   <img src="doc/usb_txrx.jpg" width="20%">
2. There are many capacitors for decoupling. You don't need to solder them all. You can solder only some of them; just distribute them evenly.
3. If you find a photosensor oversensitive, you need to use a lower resistance, e.g. 15kohm; otherwise, if it's not sensitive enough, you can use a higher resistance, e.g. 27kohm or 33kohm. Also you can measure the idle voltage across the pull-down resistor (R6, R8, ...) when nothing is above the photosensor. Higher resistance gives higher idle voltage, 0.1v to 0.2v is a good range.

### Test the PCB
* You can test the PCB now, put the firmware in.
* Most likely all key LEDs will light up and flash.
* Left fader LEDs will light up green, right fader LEDs will light up pink.
* Chord Pico should be recognized as a USB HID device. Here's the test page.  
  https://whowechina.github.io/iidx_pico/Tools/gamepad_test.html
* Use a terminal tool to connect to Chord Pico's command line interface.
  https://whowechina.github.io/iidx_pico/Tools/cli_tool.html
* Use `debug hall` to toggle hall effect sensor debug mode. When it's on, you can see the real-time sensor values. Use a small magnet to test them one by one. The value should change significantly when a magnet is close to the corresponding sensor. If you notice strange values, check the soldering of the multiplexer and the corresponding hall effect sensor.
* Use `debug fader` to toggle fader sensor debug mode. When it's on, you can see real-time fader sensor status. You can use a white object (e.g. paper), waving it 5mm above the sensor to see the response.
* Only when PCB is fully functional, you can proceed to the assembly.

### 3D Printing
#### Printing parameters  
* PLA or PETG.
* Layer height: 0.2mm
* Support: No, unless explicitly mentioned.
* Files are always in millimeter units, not inches.
* Parts can fit on a 256mm\*256mm bed, you may need to rotate them to fit.

#### Parts
* All files are in `Production\3DPrint` folder.
* Use files with `+` for Chord Pico+, including `Chord Pico+`, `Key+` and `Fader+`.
* Keys: `Key Combo - All Keys`, clear or transparent.
* Rear Base: `Chord Pico - Rear.stl`, black. Enable support and use support material to have better screw holes.
* Front Base: `Chord Pico - Front.stl`, black. Enable support and use support material to have better screw holes. Note that for Chord Pico+ version, the front base is split into two parts: `Chord Pico+ - Left` and `Chord Pico+ - Right`.
* Panel: `Chord Pico - Panel Combo.3mf`, a multi-color system is highly recommended, make the "Panel White Layer" white, others black. Print upside down.
* Brim (Key Stopper): `Chord Pico - Brim Insert.stl` is recommended, but if you can't use heat-set inserts, use `Chord Pico - Brim.stl` instead (see notes below). Use black filament. Print upside down. Note that for Chord Pico+ version, the brim is split into two parts: `Chord Pico+ - BrimLeft` and `Chord Pico+ - BrimRight`, both use heat-set inserts.
* Fader parts for Chord Pico only:
  * 2x Fader Slider: `Slider PTFE.stl` is recommended, but if you can't find proper PTFE tube, use `Slider Thruhole.stl` instead (see notes below). Must be white.  
  * 2x Fader Seal: `Slider Seal.stl`, white.
  * 4x Rail Fixers: `Chord Pico - Rail Fixer.stl`, color doesn't matter.
  * 2x Fader Knobs: `Fader - Knob.stl`, one in green, one in red.
* Fader parts for Chord Pico+ only:
  * 2x Fader seats: `Fader+ - Seat`, black, embed heat-set inserts after printing.
  * 2x Fader curtains: `Fader+ - Curtain`, black.
  * 2x Reflectors: `Fader+ - Reflector`, **MUST** be white.
  * 2x Fader Knobs: `Fader+ - Knob+.stl`, one in green, one in red.

#### Notes
1. For the Brim (Key Stopper), heat-set inserts are recommended; they provide a better solution than self-tapping threads. But if you can't find them or don't have the tools, you can use self-tapping version instead, just be careful when screwing, do it slowly and don't overtighten.
2. For the Fader Slider, a PTFE tube is recommended for smoother feel. If you can't find proper PTFE tube, you can use the through-hole version.

### Assembly
#### Other components needed
* 13x M3\*6mm screws for the PCB to the front and rear base. For Chord Pico+ version, 18x are needed.
* 7x M3\*10mm screws for the panel to the rear base.
* 7x M2\*10mm screws for the front base to the brim. For Chord Pico+ version, 9x are needed.

* Fader components for Chord Pico only:
  * 4x 2mm\*70mm (diameter\*length) steel shafts for the fader rails.
  * Some 2.2mm\*4mm or 2.3mm\*4mm (inner diameter\*outer diameter) PTFE tubes.
  * 4x 0.3mm\*5mm\*15mm (wire diameter\*outer diameter\*length) close-wound tension springs, for the faders.
  * 24x M2\*7mm screws for the slider.
  * 2x M2\*16~18mm screws for the fader knobs.

* Fader components for Chord Pico+ only:
  * 2x MGN7 100mm linear rails.
  * 2x MGN7C sliders.
  * 4x 0.4mm\*5mm\*30mm (wire diameter\*outer diameter\*length) close-wound tension springs, for the faders.
  * 8x M2\*8mm screws for securing the rails to the base.
  * 8x M2 washers, for the screws that secure the tension springs. Metal or plastic both work.
  * 4x M2\*4mm screws for securing the tension springs on the slider side.
  * 4x M2\*6mm screws for securing the tension springs on the spring posts at both ends of the rails.
  * 8x M2\*8mm screws for securing the curtains and fader seats to the sliders.
  * 2x M2.5\*18mm screws for securing the fader knobs to the fader seats.
  
* 7x M2\*3mm\*3mm (outer diameter\*height) heat-set inserts for Chord Pico brim. For Chord Pico+, 9x are needed.
* 7x M3\*4mm\*4mm (outer diameter\*height) heat-set inserts for Chord Pico panel. For Chord Pico+, 9x are needed.
* Only for Chord Pico+: 2x M2.5\*3.5mm\*6mm (outer diameter\*height) heat-set inserts for the fader seats.

* 1x 2mm diameter steel shaft. 250mm length for Chord Pico, 340mm length for Chord Pico+.

* 12x 0.4\*5\*10\*6N (0.4mm wire diameter, 5mm outer diameter, 10mm free length, 6 turns) springs. For Chord Pico+, 24x are needed.
* 12x 3mm\*2mm (diameter\*height) axial magnetized cylinder magnets.
* Some white silicone adhesive, such as K-704 silicone industrial adhesive.
* Some damping grease, low viscosity, such as Runsai's type-2.

* Some 0.5~0.8mm thick self-adhesive foam tape (Poron or EVA) for damping.

* Some 10mm\*2mm or 10mm\*2mm (diameter\*height) black silicone self-adhesive anti-slip pads.

#### Steps
Please note that the design may change in the future, but the assembly steps will remain the same. So ignore minor differences in some details.

1. Please install heat-set inserts into the parts that require them.

2. Use the M3\*6mm screws to fix the PCB to the front and rear base part. Note that for Chord Pico+ version, the base is assembled from three parts and needs more screws.  
   <img src="doc/assembly_1.jpg" width="70%">

3. Insert the magnets into the slots at the front of the keys and secure them with adhesive (such as white RTV 704 silicone glue).

4. Install the keys. Use the steel shaft to go through all keys, and then embed the steel shaft into the hinge sockets in the rear base.  
   <img src="doc/assembly_2.jpg" width="70%">

5. Fader assembly for Chord Pico only:
   1. Cut some pieces of PTFE tube and embed them into the slider. They provide smoothness while sliding the faders. If you do not use PTFE tube, please use the through-hole slider and skip this step.  
      <img src="doc/assembly_3a.jpg" width="40%">

   2. Insert the close-wound tension springs into the slider, then use M2 screws to secure the slider seal to the slider.  
      <img src="doc/assembly_3b.jpg" width="36%"> <img src="doc/assembly_3c.jpg" width="40%">

   3. While the steel shafts are inserted, put the slider combo into the rear base. Then hook the springs to the base and finally use M2 screws and the rail fixers to secure the slider combo. You can apply a little bit of damping grease to the steel shafts to make the slider less bouncy.  
      <img src="doc/assembly_3d.jpg" width="30%"> <img src="doc/assembly_3e.jpg" width="50%">
6. Fader assembly for Chord Pico+ only:
   1. Secure the two linear rails to the rear base using M2 screws.  
      <img src="doc/assembly_4a.jpg" width="70%">
   2. Insert the reflectors into the fader seats, paying attention to their orientation.  
      <img src="doc/assembly_4b.jpg" width="50%">
   3. Install the springs onto the fader seats using M2 screws and washers. Note that the screws for the fixed side and the moving side are different, and don’t overtighten them. The seats are floating on the sliders for now.  
      <img src="doc/assembly_4c.jpg" width="70%">
   4. Place the curtains onto the sliders, push them firmly against the sliders, then use M2 screws to secure them.  
      <img src="doc/assembly_4d.jpg" width="70%">

7. Install the springs for the keys. Chord Pico+ has two springs per key.  
   <img src="doc/assembly_5.jpg" width="70%">

8. Now do another test. Power on and calibrate the keys. Keys and faders should work properly. If everything is fine, proceed to the next step.

9. Optional but highly recommended: use some foam tape to dampen the key noise. You need to stick the foam tape to the PCB (right below the Hall sensors) and the key stopper (brim) part. They reduce the key down and key up noise significantly.  
   <img src="doc/assembly_6.jpg" width="80%">

10. Chord Pico only. If the area of the panel above the sensors is printed with white material, use a black marker to color it. This helps reduce the risk of sensor interference.  
    <img src="doc/assembly_7.jpg" width="70%">

11. Chord Pico+ only. Apply thin PTFE/UHMW tape to the inner top surface of the panel so the slider curtains don’t squeak when sliding.  
    <img src="doc/assembly_8.jpg" width="70%">

12. Put the panel onto the base. The two auxiliary switches can interfere with the panel during installation, so move the right slider to the left and gently flex the panel to snap it into place. Then use the M3\*10mm screws to secure the panel to the base.  
    <img src="doc/assembly_11.jpg" width="70%">

13. Perform another test. Power on and calibrate. Make sure everything still works.

14. Install the knobs. The left is green and the right one is red. Secure them using the long screws (M2 for Chord Pico, M2.5 for Chord Pico+).
    <img src="doc/assembly_12.jpg" width="70%">

15. Install the brim (key stopper) part. If you use heat-set inserts, use the proper tools to install them into the brim first. Use M2\*10mm screws to secure the brim to the front base.  
    <img src="doc/assembly_13.jpg" width="70%">

16. Attach the anti-slip pads to the bottom of the controller.

17. Power on and recalibrate the keys.

18. Enjoy!  
    <img src="doc/assembly_14.jpg" width="80%">

### Firmware
* UF2 file is in `Production\Firmware` folder.
* For the new build, hold the BOOTSEL button while connecting the USB to a PC, a disk named "RPI-RP2" will appear. Drag the UF2 firmware binary file into it. Note that there is a small hole on the bottom side of the controller, aligned with the BOOTSEL button.
* If it's already running the firmware, you can either use `update` in the command line or hold down the two auxiliary switches while connecting to USB to enter update mode.
* To access the command line, you can use this Web Serial Terminal to connect to the controller's command line port. (Note: "?" is for help)  
  https://whowechina.github.io/iidx_pico/Tools/cli_tool.html

### Usage
* Just plug and play.
* Keys are mapped to HID buttons.
* Faders are mapped to the HID axes X and Y.
* Use the `calibrate` command to calibrate the Hall effect keys.
* Use the `trigger` command to set the trigger and reset distances.

## CAD Source File
I'm using OnShape free subscription. It's powerful, but it can't archive original designs locally, so I can only share the link here. STL/DXF/DWG files are exported from this online document.  
  https://cad.onshape.com/documents/6bb6f9e65a79e122747d4a2d/w/1074c535f59b2616ddc9d820/e/61a1d98d42199565d2d1adba
