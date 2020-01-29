#define CLK D5
#define DT D6
#define SW D7

#include "ESP8266TrueRandom.h"
#include <w7a8n1y4a_oled_128_64.h>
#include <w7a8n1y4a_encoder.h>
#include <images.h>

w7a8n1y4a_encoder w7a8n1y4a_enc(CLK, DT, SW);
w7a8n1y4a_gamer w7a8n1y4a_game;
void setup() {
  Serial.begin(115200);
  w7a8n1y4a_game.oled_clear_buffer();
  w7a8n1y4a_game.oled_bitmap(0,0,128,64,silberworks_128_64);
  w7a8n1y4a_game.oled_buffer_data();
}
void loop() {
  w7a8n1y4a_enc.tick();
  w7a8n1y4a_game.bot_reload_tick();
  w7a8n1y4a_game.game_reload_attack();
  w7a8n1y4a_game.game_frame();
  if(w7a8n1y4a_enc.left()){
    w7a8n1y4a_game.gamer_left();
  }
  if(w7a8n1y4a_enc.right()){
    w7a8n1y4a_game.gamer_right();

  }
  if(w7a8n1y4a_enc.press()){
    w7a8n1y4a_game.gamer_attack();
  }
  if(w7a8n1y4a_enc.long_press()){
    w7a8n1y4a_game.gamer_heran();
  }
  delay(1);
}
