//////////// not tested on hardware yet!!!!!!!!!!!!!
#include <Wire.h>
byte address_mux = 0x70;
byte address_AD5693 = 0x4C;

void setup()
{
  Serial.begin (9600); ////////////////serial port
  Wire.begin();        /////////////// i2c enable
}

int set_port ( int port_value)
{
  Wire.beginTransmission(address_mux );
  byte port = port_value;
  Wire.write(port); 
  Wire.endTransmission();
  Serial.print (port, DEC);
  Serial.print("\n");
}

int set_volt ( int raw_value)
{
  Wire.beginTransmission(address_AD5693);
    // Select DAC and input register
  Wire.write(0x40);
    // Write data = 0
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  
  Wire.beginTransmission(address_AD5693 );
  Wire.write(0x30); 
  Wire.write(raw_value >> 8)& 0xFF;        // 8 MSB
  Wire.write(raw_value & 0xFF); //8 LSB
  Wire.endTransmission();
  Serial.print (raw_value, DEC);
  Serial.print("\n");
}

void loop()
{
  set_port(1); //////////// set port value over here///port values 1,2,4,8
  set_volt(40900);/////////// set dac output over here
  delay(5000);           // wait 50 seconds for next scan
}
