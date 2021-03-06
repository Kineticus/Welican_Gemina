
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
        brightness.target = p->value().toInt();
        brightness.debounce = millis() + 1420;
      }
      if (p->name() == "favorite")
      {
        startSmoothOperator();
        int patternMode = p->value().toInt();
        patternSettings.pattern[globals.mode] = patternMode;
        globals.mode = 0;
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
  //Multithread timing issue
  delay(5);

  if (var == "BRIGHTNESS")
  {
    if (brightness.target == 0)
    {
      return "Off";
    }
    else if (brightness.target == 255)
    {
      return "Max";
    }
    else if (brightness.target > 200)
    {
      return "Bright";
    }
    else if (brightness.target > 160)
    {
      return "Half";
    }
    else if (brightness.target > 120)
    {
      return "Third";
    }
    else if (brightness.target > 80)
    {
      return "Quarter";
    }
    else if (brightness.target > 40)
    {
      return "Dim";
    }
    else if (brightness.target > 0)
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
