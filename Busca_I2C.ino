// --------------------------------------
// i2c_scanner
//
// Version 1
// Este programa
// se puede encontrar en muchos lugares.
// Por ejemplo en el foro Arduino.cc.
// El autor original no se conoce.
//
// Versión 2, junio de 2012, con Arduino 1.0.1
// Adaptado para ser lo más simple posible por el usuario Krodal de Arduino.cc
//
// Versión 3, 26 de febrero de 2013
// V3 por louarnold
// Versión 4, 3 de marzo de 2013, con Arduino 1.0.3
// por el usuario Arduino.cc Krodal.
// Cambios por louarnold eliminados.
// Las direcciones de escaneo cambiaron de 0 ... 127 a 1 ... 119,
// según el escáner i2c de Nick Gammon
// https://www.gammon.com.au/forum/?id=10896
// Versión 5, 28 de marzo de 2013
//
// Como la versión 4, pero la dirección escanea ahora a 127.
// Un sensor parece usar la dirección 120.
//
// Versión 6, 27 de noviembre de 2015.
// Se agregó la espera de la comunicación serial de Leonardo.
//
// Versión 7, 26 de marzo de 2020.
// Incluimos en la búsqueda el segundo I2C. Definimos ADUE
//
// Este s prueba las direcciones estándar de 7 bits
// Es posible que los dispositivos con una dirección de bit superior no se vean correctamente.
// 
//

#define ADUE         // Para ArduinoDUE procesamos el segundo I2C. Poner en comentario para placas con un solo I2C
#include <Wire.h>


void setup()
{
  Wire.begin();
#ifdef ADUE
  Wire1.begin();  // inicializa el segundo bus. SCL1 y SDA1 en Arduino DUE
#endif

  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nEscaneo I2C en Arduino DUE");
}


void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Buscando...");

  nDevices = 0;
  // Para el primer I2C
  for (address = 1; address < 127; address++ ) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C: dispositivo encontrado en la dirección 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Error desconocido en la dirección 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }

#ifdef ADUE
  // Para el segundo I2C
  for (address = 1; address < 127; address++ ) {
    // busca_i2c usa el valor de retorno de
    // Write.endTransmisstion para ver si
    // un dispositivo confirmo la dirección.
    Wire1.beginTransmission(address);
    error = Wire1.endTransmission();

    if (error == 0)
    {
      Serial.print("Segundo I2C: dispositivo encontrado en la dirección 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Error desconocido en la dirección 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
#endif


  // Si no encuentra ningún dispositivo
  if (nDevices == 0)
    Serial.println("Dispositivos I2C no encontrados\n");
  else
    Serial.println("Terminado\n");

  delay(5000);           // wait 5 seconds for next scan
}
