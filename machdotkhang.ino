#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ADS1X15.h>

// ================= OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ================= ADS1115 =================
Adafruit_ADS1115 ads;

// ================= AD9833 =================
#define FSYNC_PIN 10
#define SDATA_PIN 11
#define SCLK_PIN  13

// ================= Phase Detect =================
#define REF_PIN  2
#define MEAS_PIN 3

volatile unsigned long tRef = 0;
volatile unsigned long tMeas = 0;
volatile bool refFlag = false;
volatile bool measFlag = false;

const float RS = 10000.0;     // điện trở chuẩn 10k
const float FREQ = 1000.0;    // 1kHz

float impedance = 0;
float phaseDeg = 0;

void refISR()
{
tRef = micros();
refFlag = true;
}

void measISR()
{
tMeas = micros();
measFlag = true;
}

void setupAD9833()
{
pinMode(FSYNC_PIN, OUTPUT);
pinMode(SDATA_PIN, OUTPUT);
pinMode(SCLK_PIN, OUTPUT);

digitalWrite(FSYNC_PIN, HIGH);

// Skeleton
// Chỗ này thay bằng thư viện AD9833 thực tế
// setFrequency(1000);
}

void setup()
{
Serial.begin(115200);

// OLED
if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
{
while (1);
}

display.clearDisplay();
display.setTextColor(SSD1306_WHITE);

// ADS1115
ads.begin();

// AD9833
setupAD9833();

// Phase pins
pinMode(REF_PIN, INPUT_PULLUP);
pinMode(MEAS_PIN, INPUT_PULLUP);

attachInterrupt(
digitalPinToInterrupt(REF_PIN),
refISR,
RISING);

attachInterrupt(
digitalPinToInterrupt(MEAS_PIN),
measISR,
RISING);

display.clearDisplay();
display.setTextSize(1);
display.setCursor(10, 10);
display.println("IMPEDANCE METER");
display.display();

delay(1500);
}

float readVoltage(uint8_t channel)
{
int16_t adc;

switch (channel)
{
case 0:
adc = ads.readADC_SingleEnded(0);
break;

```
case 1:
  adc = ads.readADC_SingleEnded(1);
  break;

default:
  adc = 0;
  break;
```

}

return adc * 0.1875f / 1000.0f;
}

void calculateImpedance()
{
float Vs = readVoltage(0); // SIG_OUT
float Vm = readVoltage(1); // MEAS_NODE

if (fabs(Vs - Vm) > 0.001)
{
impedance = RS * Vm / (Vs - Vm);
}
}

void calculatePhase()
{
if (refFlag && measFlag)
{
long dt = (long)tMeas - (long)tRef;

```
float period_us = 1000000.0 / FREQ;

phaseDeg =
    ((float)dt / period_us) * 360.0;

refFlag = false;
measFlag = false;
```

}
}

void updateDisplay()
{
display.clearDisplay();

display.setTextSize(1);

display.setCursor(0, 0);
display.println("IMPEDANCE METER");

display.setCursor(0, 18);
display.print("Freq : ");
display.print((int)FREQ);
display.println(" Hz");

display.setCursor(0, 34);
display.print("Z : ");
display.print((int)impedance);
display.println(" Ohm");

display.setCursor(0, 50);
display.print("Phase : ");
display.print(phaseDeg, 1);
display.println(" deg");

display.display();
}

void loop()
{
calculateImpedance();

calculatePhase();

updateDisplay();

Serial.print("Z = ");
Serial.print(impedance);
Serial.print(" Ohm   ");

Serial.print("Phase = ");
Serial.println(phaseDeg);

delay(200);
}
