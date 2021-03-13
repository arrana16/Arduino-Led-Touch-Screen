#include <Elegoo_GFX.h>                   // Core graphics library
#include <Elegoo_TFTLCD.h>                // Hardware-specific library
#include <TouchScreen.h>                  // Touch Support

#define TS_MINX 920
#define TS_MINY 120
#define TS_MAXX 150
#define TS_MAXY 940
#define YP A3                             // must be an analog pin, use "An" notation!
#define XM A2                             // must be an analog pin, use "An" notation!
#define YM 9                              // can be a digital pin
#define XP 8                              // can be a digital pin

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// macros for color (16 bit)
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFFFF
#define PINK    0xf818

#define LCD_CS A3                         // Chip Select goes to Analog 3
#define LCD_CD A2                         // Command/Data goes to Analog 2
#define LCD_WR A1                         // LCD Write goes to Analog 1
#define LCD_RD A0                         // LCD Read goes to Analog 0
#define LCD_RESET A4                      // Can alternately just connect to Arduino's reset pin

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

int redPin = 44;
int greenPin = 45;
int bluePin =  46;

int colorblue[3] = {0,0,255};
int colorgreen[3] = {0, 255, 0};
int colorred[3] = {255, 0, 0};
int coloryellow[3] = {255, 255, 0};
int colorcyan[3] = {0, 255, 255};
int colorpink[3] = {255, 0, 255};
int colorwhite[3] = {255,255,255};
int coloroff[3] = {0, 0, 0};

class Rectangle {
  public:
    String colorName;
    int startx;
    int starty;
    int overx;
    int overy;
    int fillColor;
    int textColor;

  void touchCheck() {
    TSPoint p = ts.getPoint();
    if (p.x > startx && p.x < startx+overx && p.y > starty && p.y < starty+overy){
      return true;
    } else {
      return false;
    }
  }
    
  Rectangle(String f, int a, int b, int c, int d, int e, int g = WHITE) {
    colorName = f;
    startx = a;
    starty = b;
    overx = c;
    overy = d;
    fillColor = e;
    textColor = g;
    tft.fillRect(startx, starty, overx, overy, fillColor);
    tft.drawRect(startx, starty, overx, overy, WHITE);
    tft.setTextSize(2);
    tft.setTextColor(textColor);
    int pixelWidth=colorName.length()*6-1;
    Serial.println(pixelWidth);
    tft.setCursor((overx+2*startx)/2 - pixelWidth, (overy+2*starty)/2 - 7);
    tft.println(colorName);
  }
};
void setup() {
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  Serial.begin(9600);
  tft.reset();                            // Reset LCD
  tft.begin(0x9341);                      // Initialise LCD
  tft.fillScreen(BLACK);                  // Black Background
  Rectangle red("Red",0,0,120,80, RED);        // Upper GREEN Rectange
  Rectangle green("Green",120 ,0 , 120, 80, GREEN);
  Rectangle blue("Blue", 0, 80, 120, 80, BLUE);
  Rectangle yellow("Yellow", 120, 80, 120, 80, YELLOW, BLACK);
  Rectangle cyan("Cyan", 0, 160, 120, 80, CYAN, BLACK);
  Rectangle pink("Pink", 120, 160, 120, 80, PINK, BLACK);
  Rectangle white("White", 0, 240, 120, 80, WHITE, BLACK);
  Rectangle off("Off", 120, 240, 120, 80, BLACK);
}

void setcolor(int color[3]) {
  analogWrite(redPin, color[0]);
  analogWrite(greenPin, color[1]);
  analogWrite(bluePin, color[2]);
}



int redCord[4] = {0, 0, 120, 80};
int greenCord[4]= {120, 0, 120, 80};
int blueCord[4] = {0, 80, 120, 80};
int yellowCord[4] = {120, 80, 120, 80};
int cyanCord[4] = {0, 160, 120, 80};
int pinkCord[4] = {120, 160, 120, 80};
int whiteCord[4] = {0, 240, 120, 80};
int offCord[4] = {120, 240, 120, 80};

void loop() {
  TSPoint p = ts.getPoint();
  if (p.z > 10 && p.z < 1000)             // Check touch validity
  {
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
    if (p.x > 0 && p.x < 240)
    {
      if (p.x > redCord[0] && p.x < redCord[0]+redCord[2] && p.y> redCord[1] && p.y< redCord[1]+redCord[3]) // Red
      {
        setcolor(colorred);
      } 
      else if (p.x > greenCord[0] && p.x < greenCord[0]+greenCord[2] && p.y> greenCord[1] && p.y< greenCord[1]+greenCord[3]) // Green
      {                
        setcolor(colorgreen);
      } 

      else if (p.x > blueCord[0] && p.x < blueCord[0]+blueCord[2] && p.y> blueCord[1] && p.y< blueCord[1]+blueCord[3]) { // Blue
        setcolor(colorblue);
      }
      else if (p.x > yellowCord[0] && p.x < yellowCord[0]+yellowCord[2] && p.y> yellowCord[1] && p.y< yellowCord[1]+yellowCord[3]){ //Yellow
        setcolor(coloryellow);
      }
      else if (p.x > cyanCord[0] && p.x < cyanCord[0]+cyanCord[2] && p.y> cyanCord[1] && p.y< cyanCord[1]+cyanCord[3]) { // Blue
        setcolor(colorcyan);
      }
      else if (p.x > pinkCord[0] && p.x < pinkCord[0]+pinkCord[2] && p.y> pinkCord[1] && p.y< pinkCord[1]+pinkCord[3]) { // Blue
        setcolor(colorpink);
      }
      else if (p.x > whiteCord[0] && p.x < whiteCord[0]+whiteCord[2] && p.y> whiteCord[1] && p.y< whiteCord[1]+whiteCord[3]) { // Blue
        setcolor(colorwhite);
      }
      else if (p.x > offCord[0] && p.x < offCord[0]+offCord[2] && p.y> offCord[1] && p.y< offCord[1]+offCord[3]) {
        setcolor(coloroff);
      }
    }
  }
}
