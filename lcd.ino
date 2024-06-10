#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C 주소는 각 모듈에 따라 다를 수 있음

#define analogPinForRV    1
#define analogPinForTMP   0
const float zeroWindAdjustment = 0.2;

int TMP_Therm_ADunits;
float RV_Wind_ADunits;
float RV_Wind_Volts;
unsigned long lastMillis;
int TempCtimes100;
float zeroWind_ADunits;
float zeroWind_volts;
float WindSpeed_MPH;
float WindSpeed_MS;

void setup() {
  Serial.begin(57600);
  lcd.init();  // LCD 초기화
  lcd.backlight();  // 백라이트 활성화
  lcd.print("Wind Speed:");
  lcd.setCursor(0, 1);
  lcd.print("Voltage:");
  lastMillis = millis();
}

void loop() {
  if (millis() - lastMillis > 200) {
    TMP_Therm_ADunits = analogRead(analogPinForTMP);
    RV_Wind_ADunits = analogRead(analogPinForRV);
    RV_Wind_Volts = RV_Wind_ADunits * 0.0048828125;

    TempCtimes100 = (0.005 * ((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits)) - (16.862 * (float)TMP_Therm_ADunits) + 9075.4;  
    zeroWind_ADunits = -0.0006 * ((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits) + 1.0727 * (float)TMP_Therm_ADunits + 47.172;
    zeroWind_volts = zeroWind_ADunits * 0.0048828125 - zeroWindAdjustment;

    WindSpeed_MPH = pow(((RV_Wind_Volts - zeroWind_volts) / 0.2300), 2.7265);
    WindSpeed_MS = WindSpeed_MPH * 1609.34 / 3600.0;

    lcd.setCursor(12, 0);
    lcd.print(WindSpeed_MS, 2); // 소수점 두 자리까지 표시
    lcd.setCursor(8, 1);
    lcd.print(RV_Wind_Volts, 3); // 소수점 세 자리까지 표시
    lcd.print(" V      ");

    lastMillis = millis();
  }
}
