# Welican Gemina

A custom ESP32 module that controls WS2811 lights, a 1.3" OLED I2C, a MSGEQ7 Microphone board, and 2 encoders.

```
Your README file is normally the first entry point to your code. It should tell people why they should use your module, how they can install it, and how they can use it. Standardizing how you write your README makes creating and maintaining your READMEs easier. Great documentation takes work!
```

This repository contains:

1. [Board Design](BOARD_DESIGN.md) to show the custom ESP32 boarddesigned for this project.

## TODOs

- WIFI Manager
- ~~Saving Favorites~~
  - ~~Favorites Menu~~
- ~~Settings~~
  - ~~Set Led Count~~
  - ~~Show IP~~
  - Timeout (short, medium, long, extra long, never)
    - Show Weather/Clock
    - Turn off
  - ~~Clock Types~~
  - ~~Random Mode Speed (short, medium, long, extra long, never)~~
  - ~~Color Order (RGB, GRB, etc)~~
  - ~~Factory Reset (reset EPROM values to default, favorites, highscores)~~
- ~~Random Mode at beginning of categories~~
- ~~Fade between patterns (to prevent quick spins on pattern knob)~~
- Audio Input morphs Music Visualizer category lights
- More visualizers (VZ)
  - Random VZ for each category (at the beginning of category)
  - Differnt types of random (at the end of category)
- ~~Weather status~~
  - ~~By Zipcode~~
  - VZ based on weather
- ~~Get Time~~
  - ~~Show time in top menu~~


## Table of Contents

- [Background](#background)
- [Install](#install)
  - [Install Arduino Libraries](#install-arduino-libraries)
  - [VS Code & C++](#vs-code-&-c++)
- [Related Documents](#related-documents)
- [Maintainers](#maintainers)
- [Contributing](#contributing)
- [Helpful Links](#helpful-links)
- [FastLed Examples](#fastled-examples)
- [License](#license)

## Background
```
  // TODO add stuff
```
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

### Install Arduino Libraries

6. Libraries `Tools > Manage Libraries` (Location is User Directory\Documents\Arduino\libraries)
  - [ESP32Encoder](https://github.com/madhephaestus/ESP32Encoder)
  - [FastLED](https://github.com/FastLED/FastLED/wiki)
    - [FastLED Samguyer Fork](https://github.com/samguyer/FastLED) *Optional
  - [arduinoFFT](https://github.com/kosme/arduinoFFT)
  - [U8g2](https://github.com/olikraus/u8g2/wiki/u8g2reference)
  - [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) *Must be installed manually
  - [ASyncTCP](https://github.com/me-no-dev/AsyncTCP) *Must be installed manually
  - [ESP32 File System Tool](https://github.com/me-no-dev/arduino-esp32fs-plugin) *Must be installed manually by copying to Tools folder!! Read instructions carefully.
  
### Create Wifi Credentials file

7. Create a file called `Secrets.h` in the main folder.
That file should include the following:
```
#define WIFI_SSID "your-wifi-ssid-goes-here"
#define WIFI_PASSWORD "your-wifi-password-goes-here"
#define OPEN_WEATHER_API_KEY "your-open-weather-api-key"
```

You will need to replace the strings with your WIFI SSID and PASSWORD

### VS Code & C++
  - [.vscode/c_app_properties.json](https://code.visualstudio.com/docs/cpp/customize-default-settings-cpp)
  - [Arduino Extension](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino)
  - [C++ Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
  - [GitLens Extension](https://marketplace.visualstudio.com/items?itemName=eamodio.gitlens)

## Related Documents

- [Welican Project Doc](https://docs.google.com/document/d/e/2PACX-1vS1qt4seWkiZLkJHX4LD_V3VYEt1su2fU610a7UOJ1a_LkRgppqzjMMRaHVzRj_jQmDRsJIRdGVeDGK/pub) - The brain-dump file created by @Kinectus
- [BOM](https://docs.google.com/spreadsheets/d/1Lj1XwBXrHm5YGtD2jA4sHXP_yh42TAKp-GVNhS_lHCg/edit?usp=sharing) - Price / Cost spreadsheet created by @Kinectus

## Maintainers

  - [@Kinectus](https://github.com/Kineticus/)

  - [@MaylorTaylor](https://github.com/MaylorTaylor/)

## Contributing

Feel free to dive in! [Open an issue](https://github.com/Kineticus/Welican_Gemina/issues/new) or submit PRs.

Standard Readme follows the [Contributor Covenant](http://contributor-covenant.org/version/1/3/0/) Code of Conduct.

## Helpful Links

  - [C++ Classes](https://www.stroustrup.com/C++11FAQ.html#member-init)
  - [Custom XBM Image Convert](https://www.online-utility.org/image/convert/to/XBM)
  - [Arduino C++ & VSCode](https://learn.sparkfun.com/tutorials/efficient-arduino-programming-with-arduino-cli-and-visual-studio-code/all)
  - [Arduino Intellisense VSCode](https://cuneyt.aliustaoglu.biz/en/enabling-arduino-intellisense-with-visual-studio-code/)
  - [Experimental FastLED RGBSet](https://github.com/FastLED/FastLED/wiki/RGBSet-Reference)
  - [Refactoring out DELAY](https://forum.arduino.cc/index.php?topic=537644.0)
  - [UG82 Screen Library](https://github.com/olikraus/u8g2)
  - [Strings for CPP](https://cpp4arduino.com/2018/11/21/eight-tips-to-use-the-string-class-efficiently.html)

## FastLED Examples

  - [Demos](https://github.com/atuline/FastLED-Demos)
  - [Demos 2](https://github.com/marmilicious/FastLED_examples)
  - [Demos 3](https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/)
  - [Flagpole](https://github.com/chemdoc77/CD77_FastLED_Projects/tree/master/CD77_Flagpole_Project)
  - [Chase Demo](https://github.com/chemdoc77/CD77_FastLED/tree/master/CD77_Chase_Demo)

## License

[MIT License](/LICENSE.md) © Welican LLC
