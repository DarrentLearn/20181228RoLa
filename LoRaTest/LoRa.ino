#include <SPI.h>
#include <LoRa.h>
String LoRaFailed = "Init LoRa failed!";
String Received = "Rece";
void InitLoRa()
{
  Serial.print("InitLoRa...");
  LoRa.setPins(D8, D4, D3) ;
  if (!LoRa.begin(915E6)) {
    Serial.println("failed!");
    LcdShow(0, LoRaFailed, LcdLeft);
    while (1);
  }
  LoRa.onReceive(onReceive);    // register the receive callback
  LoRa.receive();  // put the radio into receive mode  
  Serial.println("Done.");
}

void RoLaSend(String text)
{
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Sending packet: " + text);
  // send packet
  LoRa.beginPacket();
  LoRa.print(text);
  LoRa.endPacket();
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
  LcdShow(0, incoming, LcdLeft);

  // print RSSI of packet
  String rssiText = "RSSI:" + (String)LoRa.packetRssi() + " dBm";
  Serial.println(rssiText);
  LcdShow(1, rssiText, LcdLeft);
  digitalWrite(LED_BUILTIN, HIGH);
}
