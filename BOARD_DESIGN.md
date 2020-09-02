# ESP32 Board Design

## Table of Contents

- [ESP Pictures](#esp-pictures)
- [Technical Information about ESP32](#Technical-Information-about-ESP32)
- [Advanced Troubleshooting and Programming](#Advanced-Troubleshooting-and-Programming)
- [Encoder](#encoders)
- [Display](#display)
- [LED Signaling](#LED-Signaling)
- [Case / Enclosure](#case-/-enclosure)


## ESP Pictures

![ESP32 1](/images/docs/board_design/esp32_1.png)

![ESP32 2](/images/docs/board_design/esp32_2.png)

![ESP32 Wroom PinOut](/images/docs/board_design/esp32_wroom_pinout.png)


## Technical Information about ESP32


  - [Data Sheet](https://www.mouser.com/datasheet/2/891/esp32-wroom-32d_esp32-wroom-32u_datasheet_en-1365844.pdf)

    
  - [Strapping Pins and Boot Mode Selection](https://github.com/espressif/esptool/wiki/ESP32-Boot-Mode-Selection)

    - USB Serial Monitor - PuTTY on Serial Port at 115200 baud
      - This will report which boot mode is selected based on strapping Pins
  - [Multicore](https://randomnerdtutorials.com/esp32-dual-core-arduino-ide/)


  ## Advanced Troubleshooting and Programming       

  - [ESP Tool](https://github.com/espressif/esptool) (Requires Python)
    - Once Python is installed open an elevated command prompt and navigate to the extracted files
    - To get board information:
      - `py espefuse.py --port COM3 summary`
    - Flash Information:
      - `py esptool.py flash_id`
    - You’ll find you have missing packages. Use the structure below to install them
      - `python -m pip install pyserial`


## Encoders

  - [Encoder Library](https://www.pjrc.com/teensy/td_libs_Encoder.html)
    - This library is able to attach inputs to interrupt pins. This prevents constant polling.
  - Wiring / Pins

    ![Encoder Wiring Pins](/images/docs/board_design/encoder_wiring_pins.png)

## Display

  - SSD1106 based OLED (128 x 64 pixels)

    ![OLED Display](/images/docs/board_design/oled_display.png)

    ![OLED Display 2](/images/docs/board_design/oled_display_2.png)


    - Available in White or Blue
    - Library: [U8g2lib](https://github.com/olikraus/u8g2)
      - I2C address: 0x3C
      - #define OLED_RESET -1
    - Wiring / Pins
      - SCL   GPIO 22   (hardware I2C SCL)
      - SDA   GPIO 21   (hardware I2C SDA)

    ![OLED Display 3](/images/docs/board_design/oled_display_3.png)

    - Usage
      - [Custom Images](https://www.online-utility.org/image/convert/to/XBM)
      - [Custom Font](https://github.com/olikraus/u8g2/wiki/fntlistall)
      - [Custom Shapes / Drawing](https://github.com/olikraus/u8g2/wiki/u8g2reference)


## LED Signaling

  - [FastLED Library](https://github.com/FastLED/FastLED/)
    - [FastLED Wiki](https://github.com/FastLED/FastLED/wiki/Overview)
      - [Controlling LEDS](https://github.com/FastLED/FastLED/wiki/Controlling-leds)
      - [Pixel Reference](https://github.com/FastLED/FastLED/wiki/Pixel-reference)
      - [HSV Colors](https://github.com/FastLED/FastLED/wiki/FastLED-HSV-Colors)
      - [Gradient Color Palettes](https://github.com/FastLED/FastLED/wiki/Gradient-color-palettes)
    - Technical
      - [Clockless RMT ESP32](https://github.com/FastLED/FastLED/blob/master/platforms/esp/32/clockless_rmt_esp32.h)
      - [Temporal Dithering](https://github.com/FastLED/FastLED/wiki/FastLED-Temporal-Dithering)
      - [High Performance Math](https://github.com/FastLED/FastLED/wiki/High-performance-math)
      - [Experimental Hardware SPI](https://github.com/FastLED/FastLED/pull/1047)
  - Wiring / Pins for RMT Hardware Accelerated use on ESP32. Allows up to 8 unique strands.
    - [Fast Pin ESP32](https://github.com/FastLED/FastLED/blob/master/platforms/esp/32/fastpin_esp32.h)

    ![Wiring / Pins for RMT Hardware Accelerated use on ESP32](/images/docs/board_design/rmt_accelerated_hardware_pins.png)
  

## Case / Enclosure

  - [ABS Plastic boxes with board standoffs](https://www.hammfg.com/electronics/small-case/plastic/1591xx)
  - [Polycarbonate Plastic boxes without board standoffs](https://www.hammfg.com/electronics/small-case/plastic/1591t)
  - [Sloping Console](https://www.hammfg.com/electronics/small-case/plastic/1599t)
  - [Anti-slip Feet 3M SJ5001](https://www.mouser.com/ProductDetail/3m/sj5001-blk/?qs=ItEYEd4DnG1l70qV%252buXsng%3D%3D)
  - [Stand-Offs / Screws for OLED/PCB]()
  - 3D Printed Custom Box
    - Sam will design and print.  Can utilize online printer shops for bulk manufacturing.