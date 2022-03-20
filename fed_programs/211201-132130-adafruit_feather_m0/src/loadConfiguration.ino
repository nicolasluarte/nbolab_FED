void loadConfiguration(const char *filename, Config &config) {
  // Open file for reading
  File file = SD.open(filename);

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<1028> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  // Copy values from the JsonDocument to the Config
  config.animal = doc["animal"] | 111;
  strlcpy(config.protocol,                  // <- destination
          doc["protocol"] | "default",  // <- source
          sizeof(config.protocol));         // <- destination's capacity
  config.longDelay = doc["longDelay"] | 15;
  config.longDelayCounter = doc["longDelayCounter"] | 6; // number of 30~min random delays
  JsonArray deliveryArray = doc["deliveryDelay"].as<JsonArray>();
  
  int counter = 0;
  for (const auto& v : deliveryArray) {
    config.deliveryDelay[counter] = v.as<int>();
    counter++;
  }
  delaySize = counter;

// write permanent variables
doc["lastLongDelay"] = "prueba";

  // Close the file (Curiously, File's destructor doesn't close the file)
  file.close();
}
