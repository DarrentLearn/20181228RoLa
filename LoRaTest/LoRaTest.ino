#define RoLaReceiver  //RoLaSender  //
#define Lcd

int NullWait = 0;
int InitIOPinWait = 1;
int InitLcdWait = 2;
int InitTimerWait = 3;
int InitLoRaWait = 4;
int RoLaSendWait = 11;

String HelloText = "Hello!";

#ifdef Lcd
#define LcdLeft 0
#define LcdCenter 1
#define LcdRight 2
#endif

#if defined RoLaSender
#define cycleRoLaSender 3
int timerRoLaSender = 0;
int countLoraMessage = 0;
#endif

void setup() {
#ifdef RoLaSender
  HelloText = "RoLaSenderReady";
#endif
#ifdef RoLaReceiver
  HelloText = "RoLaReceiReady";
#endif
  Serial.begin(9600);
  Serial.println("");
  InitIOPin();
#ifdef Lcd
  InitLcd(HelloText);
#endif
  InitTimer();
  InitLoRa();
}

void loop() {
  delay(100);
  Timebase();
}

void TimerMain()
{
  //Serial.println("TimerMain");

#ifdef RoLaSender
  if (timerRoLaSender++ > cycleRoLaSender)
  {
    SendTestMessage();
    timerRoLaSender = 0;
  }
#endif
}

#ifdef RoLaSender
void SendTestMessage()
{
  String message = "Hello " + String(countLoraMessage);
  //Serial.println("LoRa Send:" + message);
#ifdef Lcd
  LcdShow(0, message, LcdLeft);
#endif
  RoLaSend(message);
  countLoraMessage++;
}
#endif

void InitIOPin()
{
  ShowWait(InitIOPinWait, "InitIOPin");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
  }
  EndWait(InitIOPinWait, "Done");
}
