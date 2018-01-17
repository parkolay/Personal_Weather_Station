//updates the vars used to display temp and %RH
void GetDHT12Data()
{ 
  UpdateDHT12();
 
  DHT12_Humidity = (DHT12Data[0] + ((float)DHT12Data[1] /10));
  DHT12_Temp = (DHT12Data[2] + ((float)DHT12Data[3] /10));
  TempInF = ((DHT12_Temp * 9 / 5) + 32);

  DisplayDHT12();
}//end void GetDHT12Data()

//pulls the data from DHT and stores it in an array
void UpdateDHT12()
{
   Wire.beginTransmission(DHT12);
   Wire.write(0);
   Wire.endTransmission();
   Wire.requestFrom(DHT12,5);
  
   DHT12Data[0] = Wire.read();   //Humidity
   DHT12Data[1] = Wire.read();   //Humidity decimal places
   DHT12Data[2] = Wire.read();   //Temperature
   DHT12Data[3] = Wire.read();   //Temperature decimal places
   DHT12Data[4] = Wire.read();   //Checksum (sum 0x00,0x01,0x02,0x03)
}//end void UpdateDHT12()

//displays Temp and %RH vars
void DisplayDHT12()
{
  lcd.setCursor(1, 2);              // set the cursor (column, line)
  lcd.print(DHT12_Temp,1);
  lcd.print((char)223);
  lcd.print("C  "); 
  lcd.setCursor(12, 2);              // set the cursor (column, line)                                            
  lcd.print(TempInF,1);
  lcd.print((char)223);
  lcd.print("F "); 
  lcd.setCursor(12, 0);
  lcd.print(DHT12_Humidity,1);
  lcd.print("%RH");
}//end void DisplayDHT12()

