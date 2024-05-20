#include "U8glib.h"
#include <SoftwareSerial.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

int pino_sensor = A0;
int valor_sensor = 0;
int posicao;
String UV_index = "0";

// Definindo os pinos para SoftwareSerial
#define RX_PIN 2
#define TX_PIN 3
SoftwareSerial espSerial(RX_PIN, TX_PIN);

bool displayOn = true;
bool altered = false;
void draw() {
  if (!displayOn) {
    return;
  }

  // Comandos gráficos para o display devem ser colocados aqui
  u8g.drawRFrame(0, 16, 67, 48, 4);
  u8g.drawRFrame(67, 16, 61, 48, 4);
  u8g.drawRFrame(0, 0, 128, 16, 4);
  u8g.drawBox(11, 48, 45, 12 );
  u8g.setFont(u8g_font_8x13B);
  u8g.setColorIndex(0);
  u8g.drawStr( 13, 59, "INDEX");
  u8g.setColorIndex(1);
  u8g.drawStr( 24, 13, "Medidor UV");
  // Centraliza o valor na tela
  u8g.setFont(u8g_font_fur25);
  u8g.drawStr( 10, 45, "UV");
  // Ajusta posição do valor do UV_Index
  if (UV_index.length() <= 1) {
    posicao = 88;
  } else {
    posicao = 78;
  }
  // Mostra valor do sensor
  u8g.setPrintPos(posicao, 52);
  u8g.print(UV_index);
}

void setup(void) {
  Serial.begin(9600);
  espSerial.begin(9600);  // Inicializa a comunicação serial com o ESP-01
  pinMode(pino_sensor, INPUT);
  if (u8g.getMode() == U8G_MODE_R3G3B2) {
    u8g.setColorIndex(255);     // white
  } else if (u8g.getMode() == U8G_MODE_GRAY2BIT) {
    u8g.setColorIndex(3);         // max intensity
  } else if (u8g.getMode() == U8G_MODE_BW) {
    u8g.setColorIndex(1);         // pixel on
  } else if (u8g.getMode() == U8G_MODE_HICOLOR) {
    u8g.setHiColorByRGB(255, 255, 255);
  }
}

void loop(void) {
  // Lê a informação do ESP-01
  if (espSerial.available() > 0) {
    char msg = espSerial.read();
    if (msg == '1' || msg == '0')
    {
      displayOn = !displayOn;
      return;
    }
  }

  Calcula_nivel_UV();
  
  // Chama a rotina de desenho na tela se o display estiver ligado
  if (displayOn) {
    u8g.firstPage();
    do {
      draw();
    } while (u8g.nextPage());
  } else {
    // Desligar o display (desenha uma tela em branco)
    u8g.firstPage();
    do {
      u8g.setColorIndex(0);
      u8g.drawBox(0, 0, 128, 64);
    } while (u8g.nextPage());
  }
  
  delay(150);
}

void Calcula_nivel_UV() {
  valor_sensor = analogRead(pino_sensor);
  // Calcula tensão em milivolts
  int tensao = (valor_sensor * (5.0 / 1023.0)) * 1000;
  // Compara com valores tabela UV_Index
  if (tensao > 0 && tensao < 50) {
    UV_index = "0";
  } else if (tensao > 50 && tensao <= 227) {
    UV_index = "0";
  } else if (tensao > 227 && tensao <= 318) {
    UV_index = "1";
  } else if (tensao > 318 && tensao <= 408) {
    UV_index = "2";
  } else if (tensao > 408 && tensao <= 503) {
    UV_index = "3";
  } else if (tensao > 503 && tensao <= 606) {
    UV_index = "4";
  } else if (tensao > 606 && tensao <= 696) {
    UV_index = "5";
  } else if (tensao > 696 && tensao <= 795) {
    UV_index = "6";
  } else if (tensao > 795 && tensao <= 881) {
    UV_index = "7";
  } else if (tensao > 881 && tensao <= 976) {
    UV_index = "8";
  } else if (tensao > 976 && tensao <= 1079) {
    UV_index = "9";
  } else if (tensao > 1079 && tensao <= 1170) {
    UV_index = "10";
  } else if (tensao > 1170) {
    UV_index = "11";
  }
}
