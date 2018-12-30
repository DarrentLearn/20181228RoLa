#include <SPI.h>
#include <LoRa.h>

#if defined(ARDUINO_AVR_UNO)
#define D8 8
#define D4 4
#define D3 3
#endif

String LoRaFailed = "Init LoRa failed!";
String Received = "Rece";
#define timeLimitSend 3
void InitLoRa()
{
  ShowWait(InitLoRaWait, "InitLoRa");
  LoRa.setPins(D8, D4, D3) ;
  if (!LoRa.begin(915E6)) {
    EndWait(InitLoRaWait, "failed!");
#ifdef Lcd
    LcdShow(0, LoRaFailed, LcdLeft);
#endif
    while (1);
  }
  LoRa.onReceive(onReceive);    // register the receive callback
  LoRa.receive();  // put the radio into receive mode
  EndWait(InitLoRaWait, "Done");
}

void RoLaSend(String text)
{
  digitalWrite(LED_BUILTIN, LOW);
  ShowWait(RoLaSendWait, "RoLaSend:\"" + text + "\" Sending");
  // send packet
  LoRa.beginPacket();
  LoRa.print(text);
  LoRa.endPacket();
  EndWait(RoLaSendWait, "Done");
  digitalWrite(LED_BUILTIN, HIGH);
}

// received a packet
void onReceive(int packetSize)
{
  digitalWrite(LED_BUILTIN, LOW);
  // read packet
  String incoming = Received + ":";
  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
  Serial.print(incoming + "    ");
#ifdef Lcd
  LcdShow(0, incoming, LcdLeft);
#endif
  // print RSSI of packet
  String rssiText = "RSSI:" + (String)LoRa.packetRssi() + " dBm";
  Serial.println(rssiText);
#ifdef Lcd
  LcdShow(1, rssiText, LcdLeft);
#endif
  digitalWrite(LED_BUILTIN, HIGH);
}
