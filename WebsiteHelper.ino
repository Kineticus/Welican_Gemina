void setupWebsiteRoutes()
{
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", String(), false, websiteProcessor);
  });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/main.js", "text/javascript");
  });

  // server.on("/obama_not_bad.jpg", HTTP_GET, [](AsyncWebServerRequest *request) {
  //   request->send(SPIFFS, "/obama_not_bad.jpg", "image/jpg");
  // });
  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    brightness.current = 255;
    request->send(SPIFFS, "/index.html", String(), false, websiteProcessor);
  });

  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    brightness.current = 0;
    request->send(SPIFFS, "/index.html", String(), false, websiteProcessor);
  });
}