
void createRoutes(AsyncWebServer *server)
{
  // Route to load style.css file
  server->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server->on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/main.js", "text/javascript");
  });

  // Route for root / web page
  server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    int paramsNr = request->params();
    for (int i = 0; i < paramsNr; i++)
    {
      AsyncWebParameter *p = request->getParam(i);
      Serial.print("Param name: ");
      Serial.println(p->name());
      Serial.print("Param value: ");
      Serial.println(p->value());
      Serial.println("------");
      if (p->name() == "brightness")
      {
        brightness.current = p->value().toInt();
      }
    }
    request->send(SPIFFS, "/index.html", String(), false, websiteProcessor);
  });

  // server->on("/obama_not_bad.jpg", HTTP_GET, [](AsyncWebServerRequest *request) {
  //   request->send(SPIFFS, "/obama_not_bad.jpg", "image/jpg");
  // });
}

void startWebsite(AsyncWebServer *server)
{
  createRoutes(server);

  dnsServer.start(53, "*", WiFi.softAPIP());
  //only when requested from AP
  server->addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);

  // Start server
  server->begin();
}