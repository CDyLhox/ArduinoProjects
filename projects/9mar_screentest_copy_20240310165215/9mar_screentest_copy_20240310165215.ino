// #include <SPI.h>
// #include "LCD_Driver.h"  // Replace with the actual library for your LCD
// #include "GUI_Paint.h"
// #include "image.h"
// #define RGB565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))


// // Define your image data array with the actual hexadecimal representation
// #define LOWER_FILEZISE_HEIGHT 240
// #define LOWER_FILEZISE_WIDTH 240

// // array size is 115200
// elapsedMillis imageDrawTime;
// elapsedMillis FimageDrawTime;

// int inPin = 31;
// int val = 0;

// void setup() {
//   // int i;
//   Config_Init();
//   LCD_Init();
//   LCD_Clear(WHITE);
//   LCD_SetBacklight(100);
//   Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, RED);
//   Paint_Clear(BLACK);

//   pinMode(inPin, INPUT);
//   Paint_DrawImage(gImage_70X70, 0, 0, 240, 240);
//   Paint_DrawString_EN(60,120, "Cage_Log", &Font24, BLACK, RED);
// }

// void loop() {
//   delay(10);
//   val = digitalRead(inPin);   
//   // Serial.print(val);
//   // if(val > 0){

//   uint16_t randomColor = RGB565(random(256), random(256), random(256));
//   Paint_DrawString_EN(rand() % 200, rand() % 300, "Cage_Log", &Font24, BLACK, randomColor);
//   Paint_DrawString_EN(rand() % 400, rand() % 400, "Wacko", &Font24, randomColor, BLACK);
//   Paint_DrawString_EN(rand() % 400, rand() % 400, "Weirdo", &Font24, randomColor, BLACK);



//     if (imageDrawTime >500){
//       Paint_DrawImage(gImage_70X70, rand() % 240, rand() % 240, rand() % 240, rand() % 240);
//       imageDrawTime = 0;
//       Serial.print("reset");
//     }
//     else if (FimageDrawTime >50000)
//     {
//       Paint_DrawImage(gImage_70X70, 0, 0, 240, 240);
//       FimageDrawTime = 0;
//     }
// }
//   // }
//   // else if(val == 0){
//   //   Paint_Dr 

#include <SPI.h>
#include "LCD_Driver.h"  // Replace with the actual library for your LCD
#include "GUI_Paint.h"
#include "image.h"
#include "image2.h"
#include "image3.h"
#define RGB565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))

// Define your image data array with the actual hexadecimal representation
#define LOWER_FILEZISE_HEIGHT 240
#define LOWER_FILEZISE_WIDTH 240

// array size is 115200
elapsedMillis imageDrawTime;
elapsedMillis FimageDrawTime;
elapsedMillis Texttime;

int inPin = 31;
int val = 0;
int counter = 0;

void setup() {
  // int i;
  Config_Init();
  LCD_Init();
  LCD_Clear(WHITE);
  LCD_SetBacklight(100);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, RED);
  Paint_Clear(BLACK);

  pinMode(inPin, INPUT);
  Paint_DrawImage(gImage_70X70, 0, 0, 240, 240);
  Paint_DrawString_EN(60, 120, "Cage_Log", &Font24, BLACK, RED);
  Paint_DrawImage(secondimage, rand() % 400, rand() % 400, rand() % 400, rand() % 400);
}

void loop() {
  delay(100);
  val = digitalRead(inPin);
  // Serial.print(val);
  // if(val > 0){

  uint16_t randomColor = RGB565(random(256), random(256), random(256));
  Paint_DrawString_EN(rand() % 200, rand() % 300, "Cage_Log", &Font24, BLACK, randomColor);
  Paint_DrawString_EN(rand() % 400, rand() % 400, "Wacko", &Font24, randomColor, BLACK);
  Paint_DrawString_EN(rand() % 400, rand() % 400, "Weirdo", &Font24, randomColor, BLACK);
  // Paint_DrawString_EN(rand() % 400, rand() % 400, counter , &Font24, randomColor, WHITE);
  // counter = counter + 1;

  if (imageDrawTime > 500) {
    Paint_DrawImage(gImage_70X70, rand() % 240, rand() % 240, rand() % 240, rand() % 240);
    imageDrawTime = 0;
    // circle(rand() % 400, rand() % 400,rand() % 400);
  }
  if (Texttime > 300){
    Paint_DrawString_EN(rand() % 400, rand() % 400, FimageDrawTime, &Font24, randomColor, WHITE);
    Texttime = 0;
  }
  if (FimageDrawTime > 3000) {
    Paint_DrawImage(secondimage, rand() % 240, rand() % 240, rand() % 240, rand() % 240);
  }
  else if (FimageDrawTime > 1000) {
    Paint_DrawImage(thirdimage, 0, 0, 240, 240);
  }
    else if (FimageDrawTime > 10000) {
    Paint_DrawImage(gImage_70X70, 0, 0, 240, 240);
    FimageDrawTime = 0;
  }

}
