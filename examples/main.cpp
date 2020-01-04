#define CLK D5
#define DT D6
#define SW D7

#include <Arduino.h>
#include <w7a8n1y4a_oled_128_64.h>
#include <w7a8n1y4a_encoder.h>

w7a8n1y4a_encoder w7a8n1y4a_enc(CLK, DT, SW);
w7a8n1y4a_oled_128_64 w7a8n1y4a(0x3C);
uint8_t icon[512] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0x70, 0x30, 0x38, 0x18, 0x18,
0x38, 0xF8, 0xF8, 0xEC, 0x04, 0x04, 0x08, 0xF8, 0x70, 0x60, 0x60, 0xC0, 0xC0, 0x80, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0x9E, 0x9F, 0xDB, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x03, 0x03, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x0E,
0x1C, 0x18, 0x30, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x03, 0x00, 0x1E, 0x7A, 0xFA, 0xE6, 0xDC, 0x70, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x1C, 0x38, 0xF0, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x70, 0xF8, 0xFF, 0x7F, 0x7C, 0x7C, 0x7C, 0xC0, 0xC0, 0x40, 0x60, 0x60, 0x20, 0xE0, 0xC0,
0x40, 0x20, 0x20, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x07, 0x1E, 0x38, 0xE0, 0x80, 0x00,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0x40, 0xE0, 0xE1, 0xF0,
0xF0, 0xD8, 0xCC, 0x4E, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0xFC,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0F, 0x38, 0x60, 0xC0, 0x00, 0x03, 0xFE,

0x80, 0xC0, 0xE0, 0xA0, 0xF0, 0xD0, 0xD8, 0xD8, 0xD8, 0xD8, 0xD8, 0xD8, 0xD8, 0x98, 0x98, 0x10,
0x10, 0x20, 0x60, 0xC0, 0x80, 0x01, 0x03, 0xE7, 0xE7, 0x3C, 0x18, 0x68, 0xEF, 0xEF, 0xC9, 0xE8,
0xF8, 0xF0, 0xE0, 0x60, 0x60, 0x30, 0x10, 0x30, 0x30, 0x20, 0x20, 0x20, 0x20, 0xC0, 0xF0, 0x1F,
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x3F, 0xC0, 0x7F,

0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xDF, 0xF7, 0xFF, 0xA3, 0xE9, 0x59, 0x41, 0x81, 0xC7, 0xFF, 0xFF,
0xFF, 0x7E, 0x7C, 0x1F, 0x0F, 0x00, 0x00, 0x03, 0x07, 0x3E, 0x66, 0xC6, 0x8F, 0xFD, 0x07, 0x06,
0x1F, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x70, 0x3B, 0x0F, 0x07, 0x01, 0x00,

0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06,
0x0C, 0x18, 0x18, 0x10, 0x10, 0x20, 0x20, 0x10, 0x10, 0x18, 0x18, 0x08, 0x0C, 0x0D, 0x0F, 0x0F,
0x0F, 0x1E, 0x1F, 0x0F, 0x06, 0x06, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
int inc=0;
void setup() {
  Serial.begin(115200);
  w7a8n1y4a.oled_clear();
  w7a8n1y4a.oled_bitmap(inc,0,64,64,icon);
  w7a8n1y4a.oled_buffer_data();
}
 
void loop() {
  w7a8n1y4a_enc.tick();

  if(w7a8n1y4a_enc.left()){
    inc -= 4;
    w7a8n1y4a.oled_bitmap(inc,0,64,64,icon);
    w7a8n1y4a.oled_buffer_data();
  } 
  if(w7a8n1y4a_enc.right()){
    inc += 4;
    w7a8n1y4a.oled_bitmap(inc,0,64,64,icon);
    w7a8n1y4a.oled_buffer_data();
  }
  if(w7a8n1y4a_enc.long_press()){
    w7a8n1y4a.oled_clear();
  }
}