#define RoLaReceiver  //RoLaSender  //

String HelloText = "Hello!";

#define LcdLeft 0
#define LcdCenter 1
#define LcdRight 2

int counter = 0;

void setup() {
#if defined RoLaSender
  HelloText = "RoLaSender ready";
#endif
#if defined RoLaReceiver
  HelloText = "RoLaReceiver ready";
#endif

  Serial.begin(9600);
  Serial.println("");
  InitIOPin();
  InitLcd(HelloText);
  InitTimer();
  InitLoRa();
}

void loop() {
#if defined RoLaSender
  SendTestMessage();
#endif
  //#if defined RoLaReceiver
  //  RoLaReceiv();
  //#endif
}

void SendTestMessage()
{
  String message = "Hello " + String(counter);
  //Serial.println("LoRa Send:" + message);
  LcdShow(0, message, LcdLeft);
  RoLaSend(message);
  counter++;
  delay(5000);
}

void InitIOPin()
{
  Serial.print("InitIOPin...");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
  }
  Serial.println("Done");
}
