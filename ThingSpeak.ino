void UpdateThingspeak(void)
{
if (client.connect(server, 80)) 
  {
    // Construct API request body
    String body = "field1=";
           body += String(TempInF);
           body += "&field2=";
           body += String(DHT12_Humidity);
           body += "&field3=";
           body += String(DS18B20TempinF);//DS18B20TempinF
    
    Serial.print("Temp: ");
    Serial.println(TempInF); 
    Serial.println(body);

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body.length());
    client.print("\n\n");
    client.print(body);
    client.print("\n\n");

  }
  client.stop();
    
}
