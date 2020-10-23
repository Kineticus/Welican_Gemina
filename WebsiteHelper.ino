
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
        brightness.debounce = millis() + 1420;
      }
      if (p->name() == "favorite")
      {
        int patternMode = p->value().toInt();
        patternSettings.pattern[globals.mode] = patternMode;
        globals.mode = 5;
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

String websiteProcessor(const String &var)
{
  if (var == "BRIGHTNESS")
  {
    if (brightness.current == 0)
    {
      return "Off";
    }
    else if (brightness.current == 255)
    {
      return "Max";
    }
    else if (brightness.current > 200)
    {
      return "Bright";
    }
    else if (brightness.current > 160)
    {
      return "Half";
    }
    else if (brightness.current > 120)
    {
      return "Third";
    }
    else if (brightness.current > 80)
    {
      return "Quarter";
    }
    else if (brightness.current > 40)
    {
      return "Dim";
    }
    else if (brightness.current > 0)
    {
      return "Moody";
    }
  }

  if (var == "IP_ADDRESS")
  {
    return globals.ipAddress;
  }

  if (var == "CATEGORY_NAME")
  {
    return globalStrings.categoryNameOutString;
  }

  if (var == "FUNCTION_NAME")
  {
    return globalStrings.functionNameOutString;
  }

  if (var == "MODE")
  {
    return website.returnText;
  }

  return String();
}
