void UpdateWeatherUnderground()
{
  Serial.println("Send to WU Sensor Values");
  Serial.print("connecting to ");
  Serial.println(host);
  
  if (client.connect(host, 80)) 
  {
    // Construct WU update body
    // We now create a URL for the request
    String url = "/weatherstation/updateweatherstation.php"; 
    url +="?ID=";
    url += WUID;
    url += "&PASSWORD=";
    url += WUPASS;
    url += "&dateutc=now";
    url += "&tempf=";
    url += DS18B20TempinF;
    url += "&humidity=";
    url += DHT12_Humidity;
    url += "&softwaretype=ESP8266&action=updateraw";
    
    Serial.print("Temp: ");
    Serial.println(DS18B20TempinF); 
    Serial.println(url);

//There were some issues getting WeatherUnderground to accept the data push
//this code finally worked (taken from the ESP8266 WIFI example and modified)and I moved on.

      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

    }//end of if (client.connect(host, 80))
    
//code below was used for debugging and could be removed
      Serial.println("request sent");
  while (client.connected()) 
  {
    String line = client.readStringUntil('\n');
    if (line == "\r") 
    {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
    
    if (line.startsWith("success")) 
    {
      Serial.println("esp8266 WeatherUnderground Update was successfull!");
    } 
  
    else 
    {
      Serial.println("esp8266 WeatherUnderground Update has failed");
    }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
//end of debug code 
  
  client.stop();
  }//end of void UpdateWeatherUnderground()
