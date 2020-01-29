 #include "w7a8n1y4a_oled_128_64.h"

w7a8n1y4a_oled_128_64::w7a8n1y4a_oled_128_64(int adress){
  adress_oled  = adress;
  Wire.begin();
 
  oled_command(0xAE);

  oled_command(0x10);
  oled_command(0x02);
   
  oled_command(0x40);

  oled_command(0xB0); 

  oled_command(0x81);
  oled_command(0xFF); 

  oled_command(0xA1);
  oled_command(0xA6); 
  oled_command(0xC8); 

  oled_command(0xD3); 
  oled_command(0x00); 
  oled_command(0xAF);
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
void w7a8n1y4a_oled_128_64::oled_clear_buffer(){
 for(uint8_t i = 0; i < 8; i++){
    for(uint16_t all = 0; all < 128; all++){
      set_oled_buffer(i*128 + all, 0x00);
    }
  }
}

void w7a8n1y4a_oled_128_64::draw_byte(uint16_t x, uint16_t y, uint8_t data){
  if(x >= 0 && x <= 127 && y >= 0 && y <= 63){
    //oled_buffer[x + 128 * (y / 8)] &= (255 >> (8 - y % 8)) | (data << (y % 8));//белый фон
    oled_buffer[x + 128 * (y / 8)] &= 255 >> (8 - y % 8);
    oled_buffer[x + 128 * (y / 8)] |= data << (y % 8);
    if(y <= 56){
      // oled_buffer[x + 128 * ((y / 8) + 1)] &= (255 << (y % 8)) | (data >> (8 - y % 8));//белый фон
      oled_buffer[x + 128 * ((y / 8) + 1)] &=  255 << (y % 8);
      oled_buffer[x + 128 * ((y / 8) + 1)] |= data >> (8 - y % 8);
    }
  }
}
void w7a8n1y4a_oled_128_64::draw_pixel(uint16_t x, uint16_t y){
  oled_buffer[x + 128 * (y / 8)] |= 1 << y % 8;
}
uint16_t w7a8n1y4a_oled_128_64::oled_char(uint16_t number, uint16_t length, uint16_t length_string){
  for(int i = 0; i < length; i++){
     string_buffer[length_string + i] = schrift_buffer[number + i];
  }
  string_buffer[length_string + length + 1] = 0x00;
  return length + 1;
}
void w7a8n1y4a_oled_128_64::draw_string(uint16_t x, uint16_t y, String arr){
  for (int i=0; i<128; i++){
    string_buffer[i] = 0x00;
  }
  uint16_t length_string = 0; 
  for (uint32_t i=0; i<arr.length(); i++){
    // Serial.println((int) arr.charAt(i));
    if((int) arr.charAt(i) != 0){
      // Serial.println((int) arr.charAt(i));
      if(((int) arr.charAt(i)) == 32){
        string_buffer[length_string + 1] = 0x00;
        string_buffer[length_string + 2] = 0x00;
        string_buffer[length_string + 3] = 0x00;
        length_string += 3;
      }

      if(((int) arr.charAt(i)) == 97){
        length_string += oled_char(0,4,length_string);
      }
      if(((int) arr.charAt(i)) == 98){ 
        length_string += oled_char(4,4,length_string);
      }
      if(((int) arr.charAt(i)) == 99){
        length_string += oled_char(8,4,length_string);
      }
      if(((int) arr.charAt(i)) == 100){
        length_string += oled_char(12,4,length_string);
      }

      if(((int) arr.charAt(i)) == 101){
        length_string += oled_char(16,3,length_string);
      }
      if(((int) arr.charAt(i)) == 102){ 
        length_string += oled_char(19,3,length_string);
      }
      if(((int) arr.charAt(i)) == 103){
        length_string += oled_char(22,4,length_string);
      }
      if(((int) arr.charAt(i)) == 104){
        length_string += oled_char(26,4,length_string);
      }

      if(((int) arr.charAt(i)) == 105){
        length_string += oled_char(30,1,length_string);
      }
      if(((int) arr.charAt(i)) == 106){ 
        length_string += oled_char(31,3,length_string);
      }
      if(((int) arr.charAt(i)) == 107){
        length_string += oled_char(34,4,length_string);
      }
      if(((int) arr.charAt(i)) == 108){
        length_string += oled_char(38,3,length_string);
      }

      if(((int) arr.charAt(i)) == 109){
        length_string += oled_char(41,5,length_string);
      }
      if(((int) arr.charAt(i)) == 110){ 
        length_string += oled_char(46,4,length_string);
      }
      if(((int) arr.charAt(i)) == 111){
        length_string += oled_char(50,4,length_string);
      }
      if(((int) arr.charAt(i)) == 112){
        length_string += oled_char(54,4,length_string);
      }

      if(((int) arr.charAt(i)) == 113){
        length_string += oled_char(58,4,length_string);
      }
      if(((int) arr.charAt(i)) == 114){ 
        length_string += oled_char(62,4,length_string);
      }
      if(((int) arr.charAt(i)) == 115){
        length_string += oled_char(66,4,length_string);
      }
      if(((int) arr.charAt(i)) == 116){
        length_string += oled_char(70,3,length_string);
      }

      if(((int) arr.charAt(i)) == 117){
        length_string += oled_char(73,4,length_string);
      }
      if(((int) arr.charAt(i)) == 118){ 
        length_string += oled_char(77,5,length_string);
      }
      if(((int) arr.charAt(i)) == 119){
        length_string += oled_char(82,5,length_string);
      }
      if(((int) arr.charAt(i)) == 120){
        length_string += oled_char(87,4,length_string);
      }

      if(((int) arr.charAt(i)) == 121){
        length_string += oled_char(91,4,length_string);
      }
      if(((int) arr.charAt(i)) == 122){
        length_string += oled_char(95,4,length_string);
      }

      if(((int) arr.charAt(i)) == 49){ 
        length_string += oled_char(99,3,length_string);
      }
      if(((int) arr.charAt(i)) == 50){
        length_string += oled_char(102,4,length_string);
      }

      if(((int) arr.charAt(i)) == 51){
        length_string += oled_char(106,4,length_string);
      }
      if(((int) arr.charAt(i)) == 52){
        length_string += oled_char(110,5,length_string);
      }
      if(((int) arr.charAt(i)) == 53){ 
        length_string += oled_char(115,4,length_string);
      }
      if(((int) arr.charAt(i)) == 54){
        length_string += oled_char(119,4,length_string);
      }

      if(((int) arr.charAt(i)) == 55){
        length_string += oled_char(123,4,length_string);
      }
      if(((int) arr.charAt(i)) == 56){
        length_string += oled_char(127,4,length_string);
      }
      if(((int) arr.charAt(i)) == 57){
        length_string += oled_char(131,4,length_string);
      }
      if(((int) arr.charAt(i)) == 48){
        length_string += oled_char(135,4,length_string);
      }

      if(((int) arr.charAt(i)) == 46){
        length_string += oled_char(139,1,length_string);
      }
      if(((int) arr.charAt(i)) == 44){
        length_string += oled_char(140,2,length_string);
      }
      if(((int) arr.charAt(i)) == 33){ 
        length_string += oled_char(142,1,length_string);
      }
      if(((int) arr.charAt(i)) == 63){
        length_string += oled_char(143,5,length_string);
      }
      
      if(((int) arr.charAt(i)) == 40){
        length_string += oled_char(148,2,length_string);
      }
      if(((int) arr.charAt(i)) == 41){
        length_string += oled_char(150,2,length_string);
      }
      if(((int) arr.charAt(i)) == 42){
        length_string += oled_char(152,3,length_string);
      }
      if(((int) arr.charAt(i)) == 58){
        length_string += oled_char(155,1,length_string);
      }
      if(((int) arr.charAt(i)) == 59){
        length_string += oled_char(156,2,length_string);
      }



    }
  }
  oled_bitmap(x,y,length_string,8,string_buffer);
}
void w7a8n1y4a_oled_128_64::oled_bitmap(uint16_t x, uint16_t y, uint16_t x_size, uint16_t y_size, uint8_t array[]){
  for(uint16_t j = x; j < x_size + x; j++){
    for(uint16_t i = y / 8; i < (y_size /8) + (y / 8); i++){
      draw_byte(j, (i*8) + y%8, array[(j - x) + (i - y /8)*x_size]);
    }
  }
}

void w7a8n1y4a_game::game_start_buffer(){
  uint8_t game_buffer_1[128] = {
        1,0,0,3, 0,0,3,0, 0,3,0,1, 0,1,3,14,
        1,0,1,1, 1,2,1,1, 1,2,1,1, 0,1,3,3,

        3,0,1,3, 0,0,0,1, 0,0,3,1, 0,1,1,1,
        0,1,1,0, 1,0,1,0, 3,2,0,1, 3,0,0,5,

        6,0,0,3, 1,0,2,3, 0,1,0,1, 0,1,1,0,
        1,1,1,0, 1,3,0,0, 1,0,0,0, 3,1,0,3,

        3,3,1,0, 1,1,2,1, 1,1,2,1, 1,1,0,1,
        14,3,1,0, 1,0,3,0, 0,3,0,0, 3,0,0,1
    };
    for(int i =0;i < 128; i++){
      game_buffer[i] = game_buffer_1[i];
    }
}
void w7a8n1y4a_game::game_buffer_data(){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      if(game_buffer[16*i + j] == 0){
        oled_bitmap(j*8,i*8,8,8,clear_8_8);
      }
      if(game_buffer[16*i + j] == 1){
        oled_bitmap(j*8,i*8,8,8,zerstoerung_2);
      }
      if(game_buffer[16*i + j] == 2){
        oled_bitmap(j*8,i*8,8,8,zerstoerung_1);
      }
      if(game_buffer[16*i + j] == 3){
        oled_bitmap(j*8,i*8,8,8,zerstoerung_0);
      }
      if(game_buffer[16*i + j] == 4){
        oled_bitmap(j*8,i*8,8,8,tank_h);
      }
      if(game_buffer[16*i + j] == 5){
        oled_bitmap(j*8,i*8,8,8,tank_l);
      }
      if(game_buffer[16*i + j] == 6){
        oled_bitmap(j*8,i*8,8,8,tank_r);
      }
      if(game_buffer[16*i + j] == 7){
        oled_bitmap(j*8,i*8,8,8,tank_u);
      }
      if(game_buffer[16*i + j] == 8){
        oled_bitmap(j*8,i*8,8,8,geschoss_hor);
      }
      if(game_buffer[16*i + j] == 9){
        oled_bitmap(j*8,i*8,8,8,geschoss_ver);
      }
      if(game_buffer[16*i + j] == 10){
        oled_bitmap(j*8,i*8,8,8,flag_8_8);
      }
      if(game_buffer[16*i + j] == 11){
        oled_bitmap(j*8,i*8,8,8,flag_8_8);
      }
      if(game_buffer[16*i + j] == 12){
        oled_bitmap(j*8,i*8,8,8, geschoss_zen);
      }
      if(game_buffer[16*i + j] == 13){
        oled_bitmap(j*8,i*8,8,8, geschoss_zen);
      }
      if(game_buffer[16*i + j] == 14){
        oled_bitmap(j*8,i*8,8,8, geschoss_zen);
      }
      if(game_buffer[16*i + j] == 15){
        oled_bitmap(j*8,i*8,8,8, geschoss_zen);
      }
    }
  }
}
void w7a8n1y4a_game::game_frame(){
  if(time_out_frame <= millis() - millis_frame){
    millis_frame = millis();
    oled_clear_buffer();
    game_buffer_data();
    oled_buffer_data();
  }
}
void w7a8n1y4a_game::game_reload_attack(){
  if(time_out_reload_attack <= millis() - millis_reload_attack){
    game_attack_tick();
    millis_reload_attack = millis();
  }
}
void w7a8n1y4a_game::game_nice(){
  oled_clear_buffer();
  oled_buffer_data();
  for(int inc =31; inc < 62; inc++){
      oled_bitmap(inc,0,64,64,max_64_64);
      if(inc > 60){
      oled_bitmap(8,0,52,64,nice_game_52_64);
      }
      oled_buffer_data();
      delay(10);
    }
    delay(2000);
}
void w7a8n1y4a_game::game_over(){
  oled_clear_buffer();
  draw_string(32,23,"game");
  draw_string(63,31,"over");
  oled_buffer_data();
  delay(2000);
}
void w7a8n1y4a_game::game_attack_tick(){
  for(int i = 0; i < 128; i++){
    if(get_game_buffer(i) == 12 && i >= 16){
      if(get_game_buffer(i - 16) == 0){
        set_game_buffer(i, 0);
        set_game_buffer(i - 16, 12);
      }else if(get_game_buffer(i - 16) >= 1 && get_game_buffer(i - 16) <= 3){
        set_game_buffer(i, 0);
        set_game_buffer(i - 16, get_game_buffer(i - 16) - 1);
      }else if(get_game_buffer(i - 16) >= 4 && get_game_buffer(i - 16) <= 7){
        set_game_buffer(i, 0);
        game_nice();
      }else if(get_game_buffer(i - 16) == 11 ){
        set_game_buffer(i, 0);
        game_over();
      }else if(get_game_buffer(i - 16) == 10 ){
        set_game_buffer(i, 0);
        game_nice();
      }else if(get_game_buffer(i - 16) >= 12 && get_game_buffer(i - 16) <= 15){
        set_game_buffer(i, 0);
        set_game_buffer(i - 16, 0);
      }
    }else if(get_game_buffer(i) == 12){
      set_game_buffer(i, 0);
    }

    if(get_game_buffer(i) == 13 && i % 16 != 0){
      if(get_game_buffer(i - 1) == 0){
        set_game_buffer(i, 0);
        set_game_buffer(i - 1, 13);
      }else if(get_game_buffer(i - 1) >= 1 && get_game_buffer(i - 1) <= 3){
        set_game_buffer(i, 0);
        set_game_buffer(i - 1, get_game_buffer(i - 1) - 1);
      }else if(get_game_buffer(i - 1) >= 4 && get_game_buffer(i - 1) <= 7){
        set_game_buffer(i, 0);
        game_nice();
      }else if(get_game_buffer(i - 1) == 11 ){
        set_game_buffer(i, 0);
        game_over();
      }else if(get_game_buffer(i - 1) == 10 ){
        set_game_buffer(i, 0);
        game_nice();
      }else if(get_game_buffer(i - 1) >= 12 && get_game_buffer(i - 16) <= 15){
        set_game_buffer(i, 0);
        set_game_buffer(i - 1, 0);
      }
    }else if(get_game_buffer(i) == 13){
      set_game_buffer(i, 0);
    }
  }
  for(int i = 127; i >= 0; i--){
    
    if(get_game_buffer(i) == 14 && i % 16 != 15){
      if(get_game_buffer(i + 1) == 0){
        set_game_buffer(i, 0);
        set_game_buffer(i + 1, 14);
      }else if(get_game_buffer(i + 1) >= 1 && get_game_buffer(i + 1) <= 3){
        set_game_buffer(i, 0);
        set_game_buffer(i + 1, get_game_buffer(i + 1) - 1);
      }else if(get_game_buffer(i + 1) >= 4 && get_game_buffer(i + 1) <= 7){
        set_game_buffer(i, 0);
        game_nice();
      }else if(get_game_buffer(i + 1) == 11 ){
        set_game_buffer(i, 0);
        game_over();
      }else if(get_game_buffer(i + 1) == 10 ){
        set_game_buffer(i, 0);
        game_nice();
      }else if(get_game_buffer(i + 1) >= 12 && get_game_buffer(i + 16) <= 15){
        set_game_buffer(i, 0);
        set_game_buffer(i + 1, 0);
      }
    }else if(get_game_buffer(i) == 14){
      set_game_buffer(i, 0);
    }
    if(get_game_buffer(i) == 15 && i <= 111){
      if(get_game_buffer(i + 16) == 0){
        set_game_buffer(i, 0);
        set_game_buffer(i + 16, 15);
      }else if(get_game_buffer(i + 16) >= 1 && get_game_buffer(i + 16) <= 3){
        set_game_buffer(i, 0);
        set_game_buffer(i + 16, get_game_buffer(i + 16) - 1);
      }else if(get_game_buffer(i + 16) >= 4 && get_game_buffer(i + 16) <= 7){
        set_game_buffer(i, 0);
        game_nice();
      }else if(get_game_buffer(i + 16) == 11 ){
        set_game_buffer(i, 0);
        game_over();
      }else if(get_game_buffer(i + 16) == 10 ){
        set_game_buffer(i, 0);
        game_nice();
      }else if(get_game_buffer(i + 16) >= 12 && get_game_buffer(i + 16) <= 15){
        set_game_buffer(i, 0);
        set_game_buffer(i + 16, 0);
      }
    }else if(get_game_buffer(i) == 15){
      set_game_buffer(i, 0);
    }
  }

}

void w7a8n1y4a_gamer::gamer_reload_state(){
  game_buffer[main_position] = main_state;
}
void w7a8n1y4a_gamer::gamer_left(){
  uint8_t state_position = get_gamer_state();
  if(state_position == 4){
    set_gamer_state(5);
  }
  if(state_position == 5){
    set_gamer_state(7);
  }
  if(state_position == 6){
    set_gamer_state(4);
  }
  if(state_position == 7){
    set_gamer_state(6);
  }
  game_frame();
}
void w7a8n1y4a_gamer::gamer_right(){
  uint8_t state_position = get_gamer_state();
  if(state_position == 4){
    set_gamer_state(6);
  }
  if(state_position == 5){
    set_gamer_state(4);
  }
  if(state_position == 6){
    set_gamer_state(7);
  }
  if(state_position == 7){
    set_gamer_state(5);
  }
  game_frame();
}
void w7a8n1y4a_gamer::gamer_heran(){
  uint8_t position_position = get_gamer_position();
  uint8_t state_position = get_gamer_state();
  if(state_position == 4){
    if(position_position >= 16){
      if(get_game_buffer(position_position - 16) == 0){
        set_gamer_position(position_position - 16);
        set_game_buffer(position_position,0);
      }else if(get_game_buffer(position_position - 16) == 10){
        game_nice();
      }
    }
  }
  if(state_position == 5){
    if(position_position % 16 != 0){
      if(get_game_buffer(position_position - 1) == 0){
        set_gamer_position(position_position - 1);
        set_game_buffer(position_position,0);
      }else if(get_game_buffer(position_position - 16) == 10){
        game_nice();
      }
    }
  }
  if(state_position == 6){
    if(position_position % 16 != 15){
      if(get_game_buffer(position_position + 1) == 0){
        set_gamer_position(position_position + 1);
        set_game_buffer(position_position,0);
      }else if(get_game_buffer(position_position - 16) == 10){
        game_nice();
      }
    }
  }
  if(state_position == 7){
    if(position_position <= 112){
      if(get_game_buffer(position_position + 16) == 0){
        set_gamer_position(position_position + 16);
        set_game_buffer(position_position,0);
      }else if(get_game_buffer(position_position - 16) == 10){
        game_nice();
      }
    }
  }
  game_frame();
}
void w7a8n1y4a_gamer::gamer_attack(){
  uint8_t position_position = get_gamer_position();
  uint8_t state_position = get_gamer_state();
  if(state_position == 4 && position_position - 16 > 0){
    if(get_game_buffer(position_position - 16) == 0){
        set_game_buffer(position_position - 16, 12);
    }else if(get_game_buffer(position_position - 16) >= 1 && get_game_buffer(position_position - 16) <= 3){
      set_game_buffer(position_position - 16, get_game_buffer(position_position - 16) - 1);
    }else if(get_game_buffer(position_position - 16) >= 4 && get_game_buffer(position_position - 16) <= 7){
      game_nice();
    }else if(get_game_buffer(position_position - 16) == 11){
      game_over();
    }else if(get_game_buffer(position_position - 16) == 10){
      game_nice();
    }else if(get_game_buffer(position_position - 16) >= 12 && get_game_buffer(position_position - 16) <= 15){
      set_game_buffer(position_position - 16, 12);
    }   
  }
  if(state_position == 5 && position_position % 16 != 0){
    if(get_game_buffer(position_position - 1) == 0){
        set_game_buffer(position_position - 1, 13);
    }else if(get_game_buffer(position_position - 1) >= 1 && get_game_buffer(position_position - 1) <= 3){
      set_game_buffer(position_position - 1, get_game_buffer(position_position - 1) - 1);
    }else if(get_game_buffer(position_position - 1) >= 4 && get_game_buffer(position_position - 1) <= 7){
      game_nice();
    }else if(get_game_buffer(position_position - 1) == 11){
      game_over();
    }else if(get_game_buffer(position_position - 1) == 10){
      game_nice();
    }else if(get_game_buffer(position_position - 1) >= 12 && get_game_buffer(position_position - 1) <= 15){
      set_game_buffer(position_position - 1, 13);
    } 
  }
  if(state_position == 6 && position_position % 16 != 15){
    if(get_game_buffer(position_position + 1) == 0){
        set_game_buffer(position_position + 1, 14);
    }else if(get_game_buffer(position_position + 1) >= 1 && get_game_buffer(position_position + 1) <= 3){
      set_game_buffer(position_position + 1, get_game_buffer(position_position + 1) - 1);
    }else if(get_game_buffer(position_position + 1) >= 4 && get_game_buffer(position_position + 1) <= 7){
      game_nice();
    }else if(get_game_buffer(position_position + 1) == 11){
      game_over();
    }else if(get_game_buffer(position_position + 1) == 10){
      game_nice();
    }else if(get_game_buffer(position_position + 1) >= 12 && get_game_buffer(position_position + 1) <= 15){
      set_game_buffer(position_position + 1, 14);
    } 
  }
  if(state_position == 7 && position_position + 16 < 128){
    if(get_game_buffer(position_position + 16) == 0){
        set_game_buffer(position_position + 16, 15);
    }else if(get_game_buffer(position_position + 16) >= 1 && get_game_buffer(position_position + 16) <= 3){
      set_game_buffer(position_position + 16, get_game_buffer(position_position + 16) - 1);
    }else if(get_game_buffer(position_position + 16) >= 4 && get_game_buffer(position_position + 16) <= 7){
      game_nice();
    }else if(get_game_buffer(position_position + 16) == 11){
      game_over();
    }else if(get_game_buffer(position_position + 16) == 10){
      game_nice();
    }else if(get_game_buffer(position_position + 16) >= 12 && get_game_buffer(position_position + 16) <= 15){
      set_game_buffer(position_position + 16, 15);
    }   
  }
  game_frame();
}

void w7a8n1y4a_bot::bot_tick(){
  uint8_t position_position = get_bot_position();
  uint8_t state_position = get_bot_state();
  uint8_t random_esp = ESP8266TrueRandom.random(0,255);
  if(random_esp > 196){
    bot_attack();
  }
  if(state_position == 4 && position_position - 16 > 0){
    if(get_game_buffer(position_position - 16) == 0){

      if(get_game_buffer(position_position - 1) <= 2){
        if(random_esp > 230){
          bot_left();
        }else{
          bot_heran();
        }
      }else if(get_game_buffer(position_position + 1) <= 2){
        if(random_esp > 230){
          bot_right();
        }else{
          bot_heran();
        }
      }else{
        bot_heran();
      }
    }else if(get_game_buffer(position_position - 16) == 1){
      bot_attack();
    }else if(get_game_buffer(position_position - 16) == 3 || get_game_buffer(position_position - 16) == 2){
      if(random_esp > 127){
        bot_right();
      }else{
        bot_left();
      }
    }
  }else if(state_position == 4){
    bot_right();
  }
  if(state_position == 5 && position_position % 16 != 0){
    
    if(get_game_buffer(position_position - 1) == 0){
      if(get_game_buffer(position_position - 16) <= 2){
        if(random_esp > 196){
          bot_left();
        }else{
          bot_heran();
        }
      }else if(get_game_buffer(position_position + 16) <= 2){
         if(random_esp > 196){
          bot_right();
        }else{
          bot_heran();
        }
      }else{
        bot_heran();
      }
    }else if(get_game_buffer(position_position - 1) == 1){
      bot_attack();
    }else if(get_game_buffer(position_position - 1) == 3 || get_game_buffer(position_position - 1) == 2){
      if(random_esp > 127){
        bot_right();
      }else{
        bot_left();
      }
    }
  }else if(state_position == 5){
    bot_right();
  }
  if(state_position == 6 && position_position % 16 != 15){
    if(get_game_buffer(position_position + 1) == 0){
      if(get_game_buffer(position_position + 16) <= 2){
        if(random_esp > 230){
          bot_left();
        }else{
          bot_heran();
        }
      }else if(get_game_buffer(position_position - 16) <= 2){
         if(random_esp > 230){
          bot_right();
        }else{
          bot_heran();
        }
      }else{
        bot_heran();
      }
    }else if(get_game_buffer(position_position + 1) == 1){
      bot_attack();
    }else if(get_game_buffer(position_position + 1) == 3 || get_game_buffer(position_position + 1) == 2){
      if(random_esp > 127){
        bot_right();
      }else{
        bot_left();
      }
    }
  }else if(state_position == 6){
    bot_right();
  }
  if(state_position == 7 && position_position + 16 < 128){
    if(get_game_buffer(position_position + 16) == 0){
      if(get_game_buffer(position_position + 1) <= 2){
        if(random_esp > 196){
          bot_left();
        }else{
          bot_heran();
        }
      }else if(get_game_buffer(position_position - 1) <= 2){
         if(random_esp > 196){
          bot_right();
        }else{
          bot_heran();
        }
      }else{
        bot_heran();
      }
    }else if(get_game_buffer(position_position + 16) == 1){
      bot_attack();
    }else if(get_game_buffer(position_position + 16) == 3 || get_game_buffer(position_position + 16) == 2){
      if(random_esp > 127){
        bot_right();
      }else{
        bot_left();
      }
    }
  }else if(state_position == 7){
    bot_right();
  }
  
}
void w7a8n1y4a_bot::bot_reload_tick(){
 if(time_out_reload_bot  <= millis() - millis_reload_bot ){
    millis_reload_bot  = millis();
    bot_tick();
  }
}
void w7a8n1y4a_bot::bot_reload_state(){
  game_buffer[bot_position] = bot_state;
}
void w7a8n1y4a_bot::bot_left(){
  uint8_t state_position = get_bot_state();
  if(state_position == 4){
    set_bot_state(5);
  }
  if(state_position == 5){
    set_bot_state(7);
  }
  if(state_position == 6){
    set_bot_state(4);
  }
  if(state_position == 7){
    set_bot_state(6);
  }
}
void w7a8n1y4a_bot::bot_right(){
  uint8_t state_position = get_bot_state();
  if(state_position == 4){
    set_bot_state(6);
  }
  if(state_position == 5){
    set_bot_state(4);
  }
  if(state_position == 6){
    set_bot_state(7);
  }
  if(state_position == 7){
    set_bot_state(5);
  }
}
void w7a8n1y4a_bot::bot_heran(){
  uint8_t position_position = get_bot_position();
  uint8_t state_position = get_bot_state();
  if(state_position == 4){
    if(position_position >= 16){
      if(get_game_buffer(position_position - 16) == 0){
        set_bot_position(position_position - 16);
        set_game_buffer(position_position,0);
      }else if(get_game_buffer(position_position - 16) == 10){
        game_over();
      }
    }
  }
  if(state_position == 5){
    if(position_position % 16 != 0){
      if(get_game_buffer(position_position - 1) == 0){
        set_bot_position(position_position - 1);
        set_game_buffer(position_position,0);
      }else if(get_game_buffer(position_position - 16) == 10){
        game_over();
      }
    }
  }
  if(state_position == 6){
    if(position_position % 16 != 15){
      if(get_game_buffer(position_position + 1) == 0){
        set_bot_position(position_position + 1);
        set_game_buffer(position_position,0);
      }else if(get_game_buffer(position_position - 16) == 10){
        game_over();
      }
    }
  }
  if(state_position == 7){
    if(position_position <= 112){
      if(get_game_buffer(position_position + 16) == 0){
        set_bot_position(position_position + 16);
        set_game_buffer(position_position,0);
      }else if(get_game_buffer(position_position - 16) == 10){
        game_over();
      }
    }
  }
}

void w7a8n1y4a_bot::bot_attack(){
  uint8_t position_position = get_bot_position();
  uint8_t state_position = get_bot_state();
  if(state_position == 4 && position_position - 16 > 0){
    if(get_game_buffer(position_position - 16) == 0){
        set_game_buffer(position_position - 16, 12);
    }else if(get_game_buffer(position_position - 16) >= 1 && get_game_buffer(position_position - 16) <= 3){
      set_game_buffer(position_position - 16, get_game_buffer(position_position - 16) - 1);
    }else if(get_game_buffer(position_position - 16) >= 4 && get_game_buffer(position_position - 16) <= 7){
      game_nice();
    }else if(get_game_buffer(position_position - 16) == 11){
      game_over();
    }else if(get_game_buffer(position_position - 16) == 10){
      game_nice();
    }else if(get_game_buffer(position_position - 16) >= 12 && get_game_buffer(position_position - 16) <= 15){
      set_game_buffer(position_position - 16, 12);
    }   
  }
  if(state_position == 5 && position_position % 16 != 0){
    if(get_game_buffer(position_position - 1) == 0){
        set_game_buffer(position_position - 1, 13);
    }else if(get_game_buffer(position_position - 1) >= 1 && get_game_buffer(position_position - 1) <= 3){
      set_game_buffer(position_position - 1, get_game_buffer(position_position - 1) - 1);
    }else if(get_game_buffer(position_position - 1) >= 4 && get_game_buffer(position_position - 1) <= 7){
      game_nice();
    }else if(get_game_buffer(position_position - 1) == 11){
      game_over();
    }else if(get_game_buffer(position_position - 1) == 10){
      game_nice();
    }else if(get_game_buffer(position_position - 1) >= 12 && get_game_buffer(position_position - 1) <= 15){
      set_game_buffer(position_position - 1, 13);
    } 
  }
  if(state_position == 6 && position_position % 16 != 15){
    if(get_game_buffer(position_position + 1) == 0){
        set_game_buffer(position_position + 1, 14);
    }else if(get_game_buffer(position_position + 1) >= 1 && get_game_buffer(position_position + 1) <= 3){
      set_game_buffer(position_position + 1, get_game_buffer(position_position + 1) - 1);
    }else if(get_game_buffer(position_position + 1) >= 4 && get_game_buffer(position_position + 1) <= 7){
      game_nice();
    }else if(get_game_buffer(position_position + 1) == 11){
      game_over();
    }else if(get_game_buffer(position_position + 1) == 10){
      game_nice();
    }else if(get_game_buffer(position_position + 1) >= 12 && get_game_buffer(position_position + 1) <= 15){
      set_game_buffer(position_position + 1, 14);
    } 
  }
  if(state_position == 7 && position_position + 16 < 128){
    if(get_game_buffer(position_position + 16) == 0){
        set_game_buffer(position_position + 16, 15);
    }else if(get_game_buffer(position_position + 16) >= 1 && get_game_buffer(position_position + 16) <= 3){
      set_game_buffer(position_position + 16, get_game_buffer(position_position + 16) - 1);
    }else if(get_game_buffer(position_position + 16) >= 4 && get_game_buffer(position_position + 16) <= 7){
      game_nice();
    }else if(get_game_buffer(position_position + 16) == 11){
      game_over();
    }else if(get_game_buffer(position_position + 16) == 10){
      game_nice();
    }else if(get_game_buffer(position_position + 16) >= 12 && get_game_buffer(position_position + 16) <= 15){
      set_game_buffer(position_position + 16, 15);
    }   
  }
}
