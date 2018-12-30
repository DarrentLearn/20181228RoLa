#ifndef ARDUINO_AVR_UNO

#include <Ticker.h>
unsigned int secendCount;

Ticker ticker;
int countWait;
int waitShow = NullWait;

void InitTimer()
{
  ShowWait(InitTimerWait,"InitTimer");
  ticker.attach(1, TimerSecond); //Use <strong>attach_ms</strong> if you need time in ms
  EndWait(InitTimerWait, "Done");
}

//硬體中斷 每秒一次
void TimerSecond()
{
  if (waitShow != NullWait)
  {
    countWait++;
    if (countWait % 100 == 0)
      Serial.print("\r\n");
    Serial.print(".");
  }
  //Serial.println("TimerSecond");
  if (secendCount + 1 != 0)
    secendCount++;
}

//主程式結束前
void Timebase()
{
  if (secendCount == 0)
    return;
  secendCount--;
  //每秒進來一次，但若有某段程式長期佔用時間，則每次主迴圈進來一次，直到追上原本的時間
  //Serial.println("TimerSecond");
  TimerMain();
}

void ShowWait(int wait, String text)
{
  waitShow = wait;
  Serial.print(text + ".");
  countWait = 0;
}

void EndWait(int wait, String text)
{
  if (waitShow != NullWait && waitShow == wait)
    Serial.println(" " + text);
  else
    Serial.println("\r\n" + text);
  waitShow = NullWait;
}
#endif
