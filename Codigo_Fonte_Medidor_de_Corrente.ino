#include "BluetoothSerial.h" 

// init Class:
BluetoothSerial ESP_BT; 

#include "EmonLib.h" //INCLUSÃO DE BIBLIOTECA

#define CURRENT_CAL 7 //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO MEDINDO A CORRENTE DA CARGA)
const int pinoSensor = 36; //PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO
double currentDraw, KWh, KW, KWhIMPOSTOS,P;
int botao=1000, V=127;
EnergyMonitor emon1; //CRIA UMA INSTÂNCIA  

void setup() {
  //Serial.begin(19200);
  Serial.begin(9600);
  ESP_BT.begin(" - Lagarto - ");        // Name of your Bluetooth interface -> will show up on your phone
  emon1.current(pinoSensor, CURRENT_CAL); //PASSA PARA A FUNÇÃO OS PARÂMETROS (PINO ANALÓGIO / VALOR DE CALIBRAÇÃO)    
}

void loop() {
    emon1.calcVI(20,100); //FUNÇÃO DE CÁLCULO (20 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDIÇÃO)
    currentDraw = emon1.Irms; //VARIÁVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO

    P = V * currentDraw;
    KW = (P/1000);

      if(P >11)
    {
      KWh = (KW*(0.21276 + 0.27087));
      KWhIMPOSTOS = KWh + KWh*(0.92/100 + 4.24/100);
      //Serial.println ("Custo: R$"); //IMPRIME O TEXTO NA SERIAL
      if(KWhIMPOSTOS <= 0.01){ Serial.println("0.01"); }
      else{
      
      float var1 = KWhIMPOSTOS;
      float var2 = currentDraw;  
      float var3 = P;
      
      ESP_BT.print(var1);ESP_BT.print("|");
      //Serial.println(KWhIMPOSTOS);Serial.print("|");
      ESP_BT.print(var2);ESP_BT.print("|");
      //Serial.print(currentDraw);Serial.print("|");
      ESP_BT.print(var3);ESP_BT.print("|");
      //Serial.print(P);Serial.print("|");

      delay(1000);
    }
    } 
}
