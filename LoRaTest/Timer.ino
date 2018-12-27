#include <Ticker.h>
Ticker baseClock;
unsigned int secendCount;
int timeMinute = -1;

void InitTimer()
{
  Serial.print("InitTimer...");
  baseClock.attach(1, TimerSecond); //Use <strong>attach_ms</strong> if you need time in ms
  Serial.println(" Done.");
}

//硬體中斷 每秒一次
void TimerSecond()
{
  //Serial.println("TimerSecond");
  if (secendCount + 1 != 0)
    secendCount++;
}
#define freqGp2y 5
int timerGp2y;

//主程式結束前
void Timebase()
{
  while (secendCount > 0)
  {
    secendCount--;
    //每秒進來一次
#if defined ntp
    struct tm *timeinfo = GetLocalTime();
    UpdateClock(timeinfo);
    //LcdBacklight(false); // 關閉背光

    if (timerGp2y-- <= 0)
    {
      timerGp2y = freqGp2y;
      //ReaGp2y();
      float dustDensity;
      if (CheckGp2y(&dustDensity))
        Serial.println(String(dustDensity) + " ug/m3 ");
      Set2DatabaseGp2y(dustDensity);
    }

    if (timeMinute == timeinfo->tm_min)
      continue;
    timeMinute = timeinfo->tm_min;
    //程式剛執行與每分鐘0秒時

    //時鐘是不是需要每隔多久校正一次? 要的話應該在這裡做

#endif
  }
}
