FirebaseJson json;
FirebaseJson json2;

void createFirebaseUser()
{
  FirebaseJson userJson;
  userJson.set("name", "");
  userJson.set("wifiName", globals.ssid);
  userJson.set("timezone", globals.timeZone);
  userJson.set("zipcode", weatherSettings.zipCode);
  userJson.set("games/snake/highscore", 0);
  userJson.set("games/fallios/highscore", 0);
  userJson.set("games/brick-breaker/highscore", 0);
  userJson.set("games/pong/highscore", 0);
  
  Serial.println("<<<<<<<<<<<<<<< --------FB---createFirebaseUser----- >>>>>>>>>>>>>>>>");
  
  if (Firebase.pushJSON(firebaseData, "users", userJson)) {
    Serial.println(firebaseData.dataPath());
    Serial.println(firebaseData.pushName());
    Serial.println(firebaseData.dataPath() + "/"+ firebaseData.pushName());

    globalUser.id = firebaseData.pushName();
    globalUser.wifiName = globals.ssid;
    globalUser.timezone = globals.timeZone;
    globalUser.zipcode = weatherSettings.zipCode;
  } else {
    Serial.println(firebaseData.errorReason());
  }
  
  Serial.println("<<<<<<<<<<<<<<< --------FB---createFirebaseUser----- >>>>>>>>>>>>>>>>");
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
  
  Serial.println("<<<<<<<<<<<<<<< --------FB---updateUserData----- >>>>>>>>>>>>>>>>");
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
  
  Serial.println("<<<<<<<<<<<<<<< --------FB-------- >>>>>>>>>>>>>>>>");
}