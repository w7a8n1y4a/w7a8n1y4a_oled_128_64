#include "w7a8n1y4a_oled_128_64.h"
#include <Arduino.h>
#include <Wire.h>

w7a8n1y4a_oled_128_64::w7a8n1y4a_oled_128_64(int adress){
  Wire.begin();
 
  oled_command(0xAE);

  oled_command(0x10);
  oled_command(0x02); //нижний адрес столбца
   //верхний адрес столбца
   
  oled_command(0x40); //начальное положение строки

  oled_command(0xB0); 

  oled_command(0x81); //яркость
  oled_command(0x00); 

  oled_command(0xA1);//установки горизонтальной и вертикальной ориентации дисплэя
  oled_command(0xA6); 
  oled_command(0xC8); 

  oled_command(0xD3); 
  oled_command(0x00); 
  oled_command(0xAF);
}

void w7a8n1y4a_oled_128_64::oled_clear(){
  oled_command(0x00 | (0 & 0x0F));
  oled_command(0xB0 | (0 & 0x0F));

  for (ushort page = 0; page < 8; page++) {
      oled_command(0xB0 + page);
      oled_command(0x02); // Set column number 0 (low nibble)
      oled_command(0x10);
      Wire.beginTransmission(adress_oled);
      Wire.write(0x40);
      for (int col = 0; col < 128; col++) {
        Wire.write(0x00);
        if(col == 0x7F){
          Wire.endTransmission();
          Wire.beginTransmission(adress_oled);
          Wire.write(0x40);
          Wire.write(0x00);
        }
      }
      Wire.endTransmission();
  }
}
void w7a8n1y4a_oled_128_64::oled_command(int command){
  Wire.beginTransmission(adress_oled);
  Wire.write(0x00);
  Wire.write(command);
  Wire.endTransmission();
}
void w7a8n1y4a_oled_128_64::oled_data(int data){
  Wire.beginTransmission(adress_oled);
  Wire.write(0x40);
  Wire.write(data);
  Wire.endTransmission();
}

void w7a8n1y4a_oled_128_64::oled_buffer_data(){
  oled_command(0x00 | (0 & 0x0F));
  oled_command(0xB0 | (0 & 0x0F));

  for (ushort page = 0; page < 8; page++) {
      oled_command(0xB0 + page);
      oled_command(0x02); // Set column number 0 (low nibble)
      oled_command(0x10);
      Wire.beginTransmission(adress_oled);
      Wire.write(0x40);
      for (int col = 0; col < 128; col++) {
        Wire.write(oled_buffer[page * 128 + col]);
        if(col == 0x7F){
          Wire.endTransmission();
          Wire.beginTransmission(adress_oled);
          Wire.write(0x40);
          Wire.write(oled_buffer[page * 128 + col]);
        }
      }
      Wire.endTransmission();
  }
}

void w7a8n1y4a_oled_128_64::oled_bitmap(uint16_t x, uint16_t y, uint16_t x_size, uint16_t y_size, uint8_t array[]){
 for(uint8_t i = 0; i < 8; i++){
    for(uint16_t all = x + i * 128; all < x + x_size + i * 128; all++){
      set_oled_buffer(all, array[(all - x) - x_size * i]);
    }
  }
}

