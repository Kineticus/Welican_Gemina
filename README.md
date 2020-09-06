# Welican Gemina

A custom ESP32 module that controls WS2811 lights, a 1.3" OLED I2C, a MSGEQ7 Microphone board, and 2 encoders.

```
Your README file is normally the first entry point to your code. It should tell people why they should use your module, how they can install it, and how they can use it. Standardizing how you write your README makes creating and maintaining your READMEs easier. Great documentation takes work!
```

This repository contains:

1. [Board Design](BOARD_DESIGN.md) to show the custom ESP32 boarddesigned for this project.


## Table of Contents

- [Background](#background)
- [Install](#install)
- [Related Documents](#related-documents)
- [Maintainers](#maintainers)
- [Contributing](#contributing)
- [Helpful Links](#helpful-links)
- [License](#license)

## Background

  - TODO add stuff

## Install

This project requires the [Arduino IDE](https://www.arduino.cc/en/Main/Software).

1. Install [Arduino IDE](https://www.arduino.cc/en/Main/Software).
2. In the Ardunio IDE, go to `File > Preferences` (CTRL + Comma).
    
    ![Arudino File Menu](/images/docs/Arduino_File_Menu.png)

3. Enter `https://dl.espressif.com/dl/package_esp32_index.json` into the “Additional Board Manager URLs” field as shown in the figure below. Then, click the “OK” button.

    ![Arudino Preferneces](/images/docs/Arduino_Preferences.png)

  - Note: if you already have the ESP8266 boards URL, you can separate the URLs with a comma as follows:
  `https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json`

4. Open the Boards Manager. Go to `Tools > Board > Boards Manager`

    ![Arudino Board Manager Menu](/images/docs/Arduino_Board_Manager_Menu.png)

5. Search for ESP32 and press install button for the “ESP32 by Espressif Systems“

    ![Arudino Board Manager Menu](/images/docs/Arduino_Board_Manager_esp32.png)

    - That’s it! Make sure to change the Board under the Tools menu to “ESP32 Dev Module”

### Install Arduino Libraries to work with this project.

6. Libraries `Tools > Manage Libraries` (Location is User Directory\Documents\Arduino\libraries)
  - [ESP32Encoder](https://github.com/madhephaestus/ESP32Encoder)
  - [FastLED](https://github.com/FastLED/FastLED/wiki)
  - [MD_MSGEQ7](https://github.com/MajicDesigns/MD_MSGEQ7)
  - [U8g2](https://github.com/olikraus/u8g2/wiki/u8g2reference)
  - [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) *Must be installed manually
  - [ASyncTCP](https://github.com/me-no-dev/AsyncTCP) *Must be installed manually

  
## Related Documents

- [Welican Project Doc](https://docs.google.com/document/d/e/2PACX-1vS1qt4seWkiZLkJHX4LD_V3VYEt1su2fU610a7UOJ1a_LkRgppqzjMMRaHVzRj_jQmDRsJIRdGVeDGK/pub) - The brain-dump file created by @Kinectus
- [BOM](1vQbfTqqgLQGBOL_Vc3Y3t6EeIMAJTtwk68Oa4qWqWnTPhov6tkztWRGPZvIn9grQiNDXserTELyufZo) - Price / Cost spreadsheet created by @Kinectus

## Maintainers

  - [@Kinectus](https://github.com/Kineticus/)

  - [@MaylorTaylor](https://github.com/MaylorTaylor/)

## Contributing

Feel free to dive in! [Open an issue](https://github.com/Kineticus/Welican_Gemina/issues/new) or submit PRs.

Standard Readme follows the [Contributor Covenant](http://contributor-covenant.org/version/1/3/0/) Code of Conduct.

## Helpful Links

[C++ Classes](https://www.stroustrup.com/C++11FAQ.html#member-init)
[Arduino C++ & VSCode](https://learn.sparkfun.com/tutorials/efficient-arduino-programming-with-arduino-cli-and-visual-studio-code/all)
[Arduino Intellisense VSCode](https://cuneyt.aliustaoglu.biz/en/enabling-arduino-intellisense-with-visual-studio-code/)

## License

[MIT License](/LICENSE.md) © Welican LLC
