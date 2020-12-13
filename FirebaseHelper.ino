FirebaseJson json;
FirebaseJson json2;

void createFirebaseUser()
{
  if ((globalUser.updateInitial != 0) 
      && ((millis() - globalUser.updateInitial) > 0) 
      && (WiFi.status() == WL_CONNECTED))
  {
    globalUser.updateInitial = 0;
    globalUser.timerDelay = millis();

    String path = "users/" + String(WiFi.macAddress());
    Serial.println("<<<<<<<<<<<<<<< --------FB---createFirebaseUser----- >>>>>>>>>>>>>>>>");

    if (Firebase.getJSON(firebaseData, path)) {
      Serial.println("USER ALREADY EXISTS");
      Serial.println(path);
      printFirebaseResult(firebaseData);

      Serial.println("==================== --------FB---createFirebaseUser----- ====================");
      return;
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println(firebaseData.errorReason());
    }

    FirebaseJson userJson;
    userJson.set("name", "");
    userJson.set("wifiName", globals.ssid);
    userJson.set("timezone", globals.timeZone);
    userJson.set("zipcode", weatherSettings.zipCode);
    // userJson.set("games/snake/highscore", 0);
    // userJson.set("games/fallios/highscore", 0);
    // userJson.set("games/brick-breaker/highscore", 0);
    // userJson.set("games/pong/highscore", 0);
    
    
    if (Firebase.set(firebaseData, path, userJson)) {
      Serial.println(firebaseData.dataPath());
      Serial.println(firebaseData.pushName());
      Serial.println(firebaseData.dataPath() + "/"+ firebaseData.pushName());

      if (firebaseData.dataType() == "json")
      {
          printFirebaseResult(firebaseData);
      }

      globalUser.id = firebaseData.pushName();
      globalUser.wifiName = globals.ssid;
      globalUser.timezone = globals.timeZone;
      globalUser.zipcode = weatherSettings.zipCode;
    } else {
      Serial.println(firebaseData.errorReason());
    }
    
    Serial.println("==================== --------FB---createFirebaseUser----- ====================");
  }
}

void updateUserData(String item, String value) 
{
  FirebaseJson updateData;
  updateData.set(item, value);

  Serial.println("<<<<<<<<<<<<<<< --------FB---updateUserData----- >>>>>>>>>>>>>>>>");
  
  if (Firebase.updateNode(firebaseData, "users/" + globalUser.id, updateData)) {
    Serial.println(firebaseData.dataPath());
    Serial.println(firebaseData.pushName());
    Serial.println(firebaseData.dataPath() + "/"+ firebaseData.pushName());
  } else {
    Serial.println(firebaseData.errorReason());
  }
  
  Serial.println("==================== --------FB---updateUserData----- ====================");
}

void updateUserData(String item, int value) 
{
  FirebaseJson updateData;
  updateData.set(item, value);

  Serial.println("<<<<<<<<<<<<<<< --------FB---updateUserData----- >>>>>>>>>>>>>>>>");
  
  if (Firebase.updateNode(firebaseData, "users/" + globalUser.id, updateData)) {
    Serial.println(firebaseData.dataPath());
    Serial.println(firebaseData.pushName());
    Serial.println(firebaseData.dataPath() + "/"+ firebaseData.pushName());
  } else {
    Serial.println(firebaseData.errorReason());
  }
  
  Serial.println("==================== --------FB---updateUserData----- ====================");
}

void addToDatabase()
{

  json2.set("child_of_002", 123.456);
  json.set("parent_001", "parent 001 text");
  json.set("parent 002", json2);

  if (Firebase.pushJSON(firebaseData, "/test/append", json)) {

    Serial.println(firebaseData.dataPath());

    Serial.println(firebaseData.pushName());

    Serial.println(firebaseData.dataPath() + "/"+ firebaseData.pushName());

  } else {
    Serial.println(firebaseData.errorReason());
  }
}

void appendData(String location, FirebaseJson json) 
{
  Serial.println("<<<<<<<<<<<<<<< --------FB-------- >>>>>>>>>>>>>>>>");
  
  if (Firebase.pushJSON(firebaseData, location, json)) {
    Serial.println(firebaseData.dataPath());
    Serial.println(firebaseData.pushName());
    Serial.println(firebaseData.dataPath() + "/"+ firebaseData.pushName());
  } else {
    Serial.println(firebaseData.errorReason());
  }
  
  Serial.println("==================== --------FB-------- ====================");
}

void printFirebaseResult(FirebaseData &data)
{
    Serial.println("PATH: " + data.dataPath());
    Serial.println("TYPE: " + data.dataType());

    if (data.dataType() == "int")
        Serial.println(data.intData());
    else if (data.dataType() == "float")
        Serial.println(data.floatData(), 5);
    else if (data.dataType() == "double")
        printf("%.9lf\n", data.doubleData());
    else if (data.dataType() == "boolean")
        Serial.println(data.boolData() == 1 ? "true" : "false");
    else if (data.dataType() == "string")
        Serial.println(data.stringData());
    else if (data.dataType() == "json")
    {
        Serial.println();
        FirebaseJson &json = data.jsonObject();
        //Print all object data
        Serial.println("Pretty printed JSON data:");
        String jsonStr;
        json.toString(jsonStr, true);
        Serial.println(jsonStr);
        Serial.println();
        Serial.println("Iterate JSON data:");
        Serial.println();
        size_t len = json.iteratorBegin();
        String key, value = "";
        int type = 0;
        for (size_t i = 0; i < len; i++)
        {
            json.iteratorGet(i, type, key, value);
            Serial.print(i);
            Serial.print(", ");
            Serial.print("Type: ");
            Serial.print(type == FirebaseJson::JSON_OBJECT ? "object" : "array");
            if (type == FirebaseJson::JSON_OBJECT)
            {
                Serial.print(", Key: ");
                Serial.print(key);
            }
            Serial.print(", Value: ");
            Serial.println(value);
        }
        json.iteratorEnd();
    }
    else if (data.dataType() == "array")
    {
        Serial.println();
        //get array data from FirebaseData using FirebaseJsonArray object
        FirebaseJsonArray &arr = data.jsonArray();
        //Print all array values
        Serial.println("Pretty printed Array:");
        String arrStr;
        arr.toString(arrStr, true);
        Serial.println(arrStr);
        Serial.println();
        Serial.println("Iterate array values:");
        Serial.println();
        for (size_t i = 0; i < arr.size(); i++)
        {
            Serial.print(i);
            Serial.print(", Value: ");

            FirebaseJsonData &jsonData = data.jsonData();
            //Get the result data from FirebaseJsonArray object
            arr.get(jsonData, i);
            if (jsonData.typeNum == FirebaseJson::JSON_BOOL)
                Serial.println(jsonData.boolValue ? "true" : "false");
            else if (jsonData.typeNum == FirebaseJson::JSON_INT)
                Serial.println(jsonData.intValue);
            else if (jsonData.typeNum == FirebaseJson::JSON_FLOAT)
                Serial.println(jsonData.floatValue);
            else if (jsonData.typeNum == FirebaseJson::JSON_DOUBLE)
                printf("%.9lf\n", jsonData.doubleValue);
            else if (jsonData.typeNum == FirebaseJson::JSON_STRING ||
                     jsonData.typeNum == FirebaseJson::JSON_NULL ||
                     jsonData.typeNum == FirebaseJson::JSON_OBJECT ||
                     jsonData.typeNum == FirebaseJson::JSON_ARRAY)
                Serial.println(jsonData.stringValue);
        }
    }
    else if (data.dataType() == "blob")
    {

        Serial.println();

        for (int i = 0; i < data.blobData().size(); i++)
        {
            if (i > 0 && i % 16 == 0)
                Serial.println();

            if (i < 16)
                Serial.print("0");

            Serial.print(data.blobData()[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }
    else if (data.dataType() == "file")
    {

        Serial.println();

        File file = data.fileStream();
        int i = 0;

        while (file.available())
        {
            if (i > 0 && i % 16 == 0)
                Serial.println();

            int v = file.read();

            if (v < 16)
                Serial.print("0");

            Serial.print(v, HEX);
            Serial.print(" ");
            i++;
        }
        Serial.println();
        file.close();
    }
    else
    {
        Serial.println(data.payload());
    }
}