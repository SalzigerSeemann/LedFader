#include <Arduino.h>
#include <math.h>

#define r 3
#define g 5
#define b 6

int red = 0;
int grn = 0;
int blu = 0;
int color;

const uint8_t PROGMEM gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

    int largest(int p_red, int p_grn, int p_blu){
    int rgb[] = {abs(p_red), abs(p_grn), abs(p_blu)};
    int max = 0;

    for(int i = 0; i<3; i++){
      if( rgb[i] > max){
        max = rgb[i];
      }
    }
    return max;
  }

  void setStripColor(int p_red, int p_grn, int p_blu){
    if(p_grn != 256){
     grn = p_grn;
    }
   if(p_blu != 256){
    }
      blu = p_blu;
    if(p_red != 256){
     red = p_red;
    }
    analogWrite(r, pgm_read_byte(&gamma8[red]));
    analogWrite(g, pgm_read_byte(&gamma8[grn]));
    analogWrite(b, pgm_read_byte(&gamma8[blu]));
  }

  void setColor(char color, int value){
    switch (color){

    case r:

      red = value;
      analogWrite(r, pgm_read_byte(&gamma8[red]));
      break;

    case g:

    grn = value;
    analogWrite(g, pgm_read_byte(&gamma8[grn]));
      break;

    case b:

      blu = value;
      analogWrite(b, pgm_read_byte(&gamma8[blu]));
      break;
    }
  }

  void fadeColor(char color, byte p_end, int duration){ 
   byte steps; 
   int dly;
    switch (color){
      case r:
            if(p_end>red){
          steps = p_end-red;
          dly = round(duration/steps);
          for(int i = red; i<= p_end; i++){
            setColor(r, i);
            delay(dly);
          }
        }
          else if(p_end<red){
            steps = red-p_end;
            dly = round(duration/steps);
            for(int i = red; i>= p_end; i--){
              setColor(r,i);
              delay(dly);
            }
          }
        break;
      case g:
            if(p_end>grn){
          steps = p_end-grn;
          dly = round(duration/steps);
          for(int i = grn; i<= p_end; i++){
            setColor(g, i);
            delay(dly);
          }
        }
          else if(p_end<grn){
            steps = grn-p_end;
            dly = round(duration/steps);
            for(int i = grn; i>= p_end; i--){
              setColor(g,i);
              delay(dly);
            }
          }
        break;
      case b:
            if(p_end>blu){
          steps = p_end-blu;
          dly = round(duration/steps);
          for(int i = blu; i<= p_end; i++){
            setColor(b, i);
            delay(dly);
          }
        }
          else if(p_end<blu){
            steps = blu-p_end;
            dly = round(duration/steps);
            for(int i = blu; i>= p_end; i--){
              setColor(b,i);
              delay(dly);
            }
          }
        break;
    }
 
  }

    void fadeStrip(int p_red, int p_grn, int p_blu){
      int wait = 20;

      int redSteps = p_red - red;
      int absRedSteps = abs(redSteps);

      int grnSteps = p_grn - grn;
      int absGrnSteps = abs(grnSteps);

      int bluSteps = p_blu - blu;
      int absBluSteps = abs(bluSteps);

      int redMax;
      int redOffset = 0;

      int grnMax;
      int grnOffset = 0;

      int bluMax;
      int bluOffset = 0;

      int maxSteps = largest(redSteps, grnSteps, bluSteps);
      maxSteps = abs(maxSteps);

      if(redSteps != 0){
       redMax = maxSteps-(maxSteps % absRedSteps);
       redOffset = ((maxSteps-(maxSteps % absRedSteps))/absRedSteps);
      }
      if(grnSteps != 0){
       grnMax = maxSteps-(maxSteps % absGrnSteps);
       grnOffset = ((maxSteps-(maxSteps % absGrnSteps))/absGrnSteps);
      }
      if(bluSteps != 0){
       bluMax = maxSteps-(maxSteps % absBluSteps);
       bluOffset = ((maxSteps-(maxSteps % absBluSteps))/absBluSteps);
      }
      
      if(maxSteps == absRedSteps){
        
        for(int i = 1; i<(maxSteps+1); i++){
          red = red + (redSteps/absRedSteps);
          setColor(r, red);
          if(i % grnOffset == 0 && i <= grnMax ){
            grn = grn + (grnSteps/absGrnSteps);
            setColor(g, grn);
          }
          if(i % bluOffset == 0 && i <= bluMax){
            blu = blu + (bluSteps/absBluSteps);
            setColor(b, blu);
          }
          delay(wait);
        }
          Serial.print(red);
          Serial.print(' ');
          Serial.print(grn);
          Serial.print(' ');
          Serial.println(blu);
      }
      else if(maxSteps == absGrnSteps){
                
        for(int i = 1; i<(maxSteps+1); i++){
          grn = grn + (grnSteps/absGrnSteps);
          setColor(g, grn);
          if(i % redOffset == 0 && i <= redMax ){
            red = red + (redSteps/absRedSteps);
            setColor(r, red);
          }
          if(i % bluOffset == 0 && i <= bluMax){
            blu = blu + (bluSteps/absBluSteps);
            setColor(b, blu);
          }
          delay(wait);
        }
          Serial.print(red);
          Serial.print(' ');
          Serial.print(grn);
          Serial.print(' ');
          Serial.println(blu);
      }
      else if(maxSteps == absBluSteps){

        for(int i = 1; i<(maxSteps+1); i++){
          blu = blu + (bluSteps/absBluSteps);
          setColor(b, blu);
          if(i % redOffset == 0 && i <= redMax ){
            red = red + (redSteps/absRedSteps);
            setColor(r, red);
          }
          if(i % grnOffset == 0 && i <= grnMax){
            grn = grn + (grnSteps/absGrnSteps);
            setColor(g, grn);
          }
          delay(wait);
        }
          Serial.print(red);
          Serial.print(' ');
          Serial.print(grn);
          Serial.print(' ');
          Serial.println(blu);
      }
}


void setup() {
Serial.begin(9600);
}

void loop() {
  setStripColor(0,0,0);
  fadeStrip(255,120,120);
  delay(1000);
  setStripColor(0,0,0);
  fadeStrip(1,200,33);
  delay(1000);
  setStripColor(0,0,0);
  fadeStrip(77,12,150);
  delay(10000);
}
