# Welican Gemina Website

## Installing

  1. Make sure you download [Node.JS](https://nodejs.org/en/download/) (so you can use `npm` commands)
  2. Make sure your terminal is in the `/website` folder.
  3. Run `npm install` to install all the dependencies in the `package.json` file.


## Build Process
  
  1. Run `npm run build`
    - This will use the `webpack.config.js` file to grab all files in `/images`, all `./styles/**.scss` files, and all the `./src/**.js` files and put the minified files into `./data/` folder.
  2. Go To ARUDINO SOFTWARE, then TOOLS > `ESP32 Data Sketch Upload`. Click this and do the "upload" to add the files to the ESP32 device.

## Developing

  1. Run `npm run start:dev`, this will launch a local server and host the files in the `./src` folder at `http://localhost:8080/`

## Helpful Places

  - [Images using ESP32](https://randomnerdtutorials.com/display-images-esp32-esp8266-web-server/)