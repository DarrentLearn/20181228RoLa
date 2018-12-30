#ifdef Lcd
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LcdCharacters 16 //一行 16 字元
#define LcdLines 2       //共 2 行

// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // 設定 LCD I2C 位址  //LiquidCrystal_I2C lcd(0x27, D1, D2);
String LcdlineText[2] = {"", ""};                              //儲存LCD顯示內容
int LcdDisplayTime[2] = {0, 0}; //顯示時間(秒)，顯示時間後清除或顯示時鐘
int LcdBackligth = 0; //背光在顯示恢復為時鐘後幾秒熄滅

void InitLcd(String HelloText)
{
  ShowWait(InitLcdWait,"InitLcd");
  lcd.begin(LcdCharacters, LcdLines); // 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光
  lcd.clear();
  LcdBacklight(true);
  EndWait(InitLcdWait,"Done");
  LcdShow(0, 0, HelloText);
}

//行:0/1,顯示內容,位置:LcdLeft/LcdCenter/LcdRight,顯示秒數:計時內可被其他顯示更新，但不顯示時鐘，計時後上排顯示時鐘、下排清除
void LcdShow(int y, String text, int location, int sec)
{
  LcdBcklightOn(5);
  LcdShow(y, text, location);
  LcdDisplayTime[y] = sec + 1;
}

//顯示指定行的內容，自動補空白。行:0/1,顯示內容,位置:LcdLeft/LcdCenter/LcdRight
void LcdShow(int y, String text, int location)
{
  LcdDisplayTime[y] = 0;
  unsigned int lineLength = text.length();
  if (lineLength < LcdCharacters)
  {
    String spaceText;
    int firstSpace, lastSpace;
    switch (location)
    {
      case LcdLeft:
        text = text + Repeat(' ', LcdCharacters - lineLength);
        break;
      case LcdCenter:
        firstSpace = (LcdCharacters - lineLength) / 2;
        lastSpace = LcdCharacters - lineLength - firstSpace;
        text = Repeat(' ', firstSpace) + text + Repeat(' ', lastSpace);
        break;
      case LcdRight:
        text = Repeat(' ', LcdCharacters - lineLength) + text;
        break;
    }
  }
  if (LcdlineText[y] == text) //若內容一樣就無需再重複(例如時鐘的日期)
    return;
  LcdlineText[y] = text;
  lcd.setCursor(0, y);
  lcd.print(text);
  //Serial.println((String)y + " - " + text);
}

//在指定的位置顯示文字。
void LcdShow(int x, int y, String text)
{
  lcd.setCursor(x, y);
  lcd.print(text);
}

//在上排的指定位置顯示文字。
void LcdShow(int y, String text)
{
  lcd.setCursor(0, y);
  lcd.print(text);
}

String Repeat(char repeatChar, unsigned int count)
{
  String repeatString = "";
  for (unsigned int i = 0; i < count; i++)
    repeatString += (String)repeatChar;
  return repeatString;
}

void Clear()
{
  lcd.clear();
}

#if defined ntp
void UpdateClock(struct tm *timeinfo)
{
  if (LcdDisplayTime[0] > 0)
    LcdDisplayTime[0]--;
  else
    ShowClock(timeinfo);
  if (LcdDisplayTime[1] > 0)
    LcdDisplayTime[1]--;
  else
    LcdShow(1, " ", LcdLeft);
  if (LcdDisplayTime[0] == 0 && LcdDisplayTime[1] == 0 && LcdBackligth > 0)
    if ( --LcdBackligth == 0)
      LcdBacklight(false);
}

void ShowClock(struct tm *timeinfo)
{
  LcdShow(0, GetTimeFormat(timeinfo, "%m/%d %H:%M:%S"), LcdCenter);
}
#endif

//點亮背光，恢復為時鐘後再過幾秒鐘熄滅
void LcdBcklightOn(int sec)
{
  LcdBackligth = sec + 2;
  LcdBacklight(true);
}

void LcdBacklight(bool onOff)
{
  if (onOff)
    lcd.backlight(); // 開啟背光
  else
    lcd.noBacklight(); // 關閉背光
}
#endif
