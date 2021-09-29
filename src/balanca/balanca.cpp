//DEFINIÇÕES DE PINOS

#define bt1 27
#define bt2 26
#define bt3 4
#define bt4 15

#define pinDT  18
#define pinSCK  19
//-250500 valor e calibracao do arduino nano  

// INCLUSÃO DE BIBLIOTECAS
#include <Arduino.h>
#include <HX711.h>
#include "BluetoothSerial.h"
#include <ArduinoJson.h>

//#include <U8g2lib.h>

//#ifdef U8X8_HAVE_HW_SPI
//#include <SPI.h>
//#endif
//#ifdef U8X8_HAVE_HW_I2C
//#include <Wire.h>
//#endif
//#define SDA A4
//#define SCL A5

// INSTANCIANDO OBJETOS
HX711 scale;
BluetoothSerial SerialBT;

// DECLARAÇÃO DE VARIÁVEIS
double peso_do_frango = 0;
int numeroAviario = 722;
int numeroLote=57;
int idadeAve = 35;

bool flag_coleta_dados = true;

boolean bt1_f = 0x00;
boolean bt2_f = 0x00;
boolean bt3_f = 0x00;
boolean bt4_f = 0x00;

//U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE); 

//typedef u8g2_uint_t u8g_uint_t;
int draw_color =0;
char posicao_coleta=1;

void leituraBotoes();
//void show_result(const char *s);
//void show_result_tempo(const char *m,const char *s);
//void MostraValorTemp(float temp);
//void ConverteValor_Al(int minutos);
//void show_result_al(const char *m);

void setup() {
  //Serial.begin(57600);
  SerialBT.begin("Balança aviário"); //Bluetooth device name
  //u8g2.begin();
  
  draw_color = 1;         // pixel on
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);
  pinMode(bt3, INPUT_PULLUP);
  pinMode(bt4, INPUT_PULLUP);

  scale.begin(pinDT, pinSCK); // CONFIGURANDO OS PINOS DA BALANÇA
  //-250500
  scale.set_scale(-240000); // LIMPANDO O VALOR DA ESCALA

  delay(2000);
  scale.tare(); // ZERANDO A BALANÇA PARA DESCONSIDERAR A MASSA DA ESTRUTURA

}

void loop() {

leituraBotoes();
delay(50);
}

void leitura_pesagem()
{
  
  peso_do_frango = scale.get_units(5); // SALVANDO NA VARIAVEL O VALOR DA MÉDIA DE 5 MEDIDAS
  peso_do_frango *= 1000; 
    
   //Serial.println(medida, 3); // ENVIANDO PARA MONITOR SERIAL A MEDIDA COM 3 CASAS DECIMAIS
  //char data1[5];
  //char data2[6];

   //char *valor = dtostrf(medida, 4, 1, data1);  
  
  //char *valor2 = itoa(numeroAV,data2,10);

  
  //String jsonData = '{"sensor":"bruno","time":23}';
  //SerialBT.print(jsonData);

  //StaticJsonDocument<100> doc;
  //doc["sor"] = "gps",
  //serializeJson(doc,SerialBT);
  
  //String dados = "bemloco,45,sensor,56";
  SerialBT.print(String(peso_do_frango));
  delay(50);
  SerialBT.flush();
  
//  SerialBT.print(numeroAviario);
//  delay(100);
//  SerialBT.flush();
//  delay(100);
//  SerialBT.print(numeroLote);
//  delay(100);
//  SerialBT.flush();
//  delay(100);
//  SerialBT.print(idadeAve);
//  delay(100);
//  SerialBT.flush();

  scale.power_down(); // DESLIGANDO O SENSOR
  // AGUARDA 5 SEGUNDOS
   // LIGANDO O SENSOR
   delay(50);
   scale.power_up();
   
}
void leituraBotoes()
{
  
  //-----------Botão1------------------
  if(!digitalRead(bt1)) bt1_f = 0x01;

  if(digitalRead(bt1) && bt1_f == 0x01)
  {
    bt1_f = 0x00;
    leitura_pesagem();
    //u8g2.clear();
  }
  
  //------------------------------------


  //------------Botão2-------------------
  if(!digitalRead(bt2)) bt2_f = 0x01;
  
  if(digitalRead(bt2) && bt2_f == 0x01)
  {
    bt2_f = 0x00;
    leitura_pesagem();
 
  }
  //-------------------------------------

  //------------Botão3-------------------
  if(!digitalRead(bt3)) bt3_f = 0x01;
  
  if(digitalRead(bt3) && bt3_f == 0x01)
  {
    bt3_f = 0x00;
    scale.tare();
    //coletaDados(posicao_coleta);
    //posicao_coleta++;
  
  }
  
  //-----------------------------------------
  
  //------------Botão4-----------------------
  if(!digitalRead(bt4)) bt4_f = 0x01;
  
  if(digitalRead(bt4) && bt4_f == 0x01)
  {
    bt4_f = 0x00;
    leitura_pesagem();
      
  }
  //------------------------------------------
}
void coletaDados(int posicao)
{ 
  
//  switch(posicao){
//    case 1:{
//      
//      break;
//    }
//    case 2:{
//      
//       break;
//    }
//    case 3:{
//      

//      break;
//    }
//     
//  }

}


//void show_result(const char *s) {
//  
//    u8g2.setColorIndex(draw_color);
//    u8g2.setFont(u8g2_font_inr24_mr);
//    u8g2.clearBuffer();
//    u8g2.drawStr(5,30, s);
//    u8g2.drawCircle(95,5,2);
//    u8g2.setColorIndex(draw_color);
//    u8g2.setFont(u8g2_font_inb24_mr);
//    u8g2.drawStr(100,30,"C");
//    u8g2.sendBuffer();
//    ultima_temp = temperatura; 
//  
//  
//}
//void MostraValorTemp(float temp)
//{
//  char data[5];
//  char *valor = dtostrf(temp, 4, 1, data);
//  
//  
//  show_result(valor);
//}
//void MostraValorTempo(int minutos,int segundos)
//{
//  char data[6];
//  char data2[6];
//  char *valor = itoa(minutos,data,10);
//  char *valor2 = itoa(segundos,data2,10);
//  
//  show_result_tempo(valor,valor2);
//}


//void show_result(const char *s) {
//  
//    u8g2.setColorIndex(draw_color);
//    u8g2.setFont(u8g2_font_inr24_mr);
//    u8g2.clearBuffer();
//    u8g2.drawStr(5,30, s);
//    u8g2.drawCircle(95,5,2);
//    u8g2.setColorIndex(draw_color);
//    u8g2.setFont(u8g2_font_inb24_mr);
//    u8g2.drawStr(100,30,"C");
//    u8g2.sendBuffer();
//    ultima_temp = temperatura; 
//  
//  
//}