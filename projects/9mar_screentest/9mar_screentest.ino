#include <SPI.h>
#include "LCD_Driver.h"  // Replace with the actual library for your LCD
#include "GUI_Paint.h"
#include "image.h"
#define RGB565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))


// Define your image data array with the actual hexadecimal representation
#define LOWER_FILEZISE_HEIGHT 240
#define LOWER_FILEZISE_WIDTH 240

// array size is 115200


void setup() {
  // int i;
  Config_Init();
  LCD_Init();
  LCD_Clear(WHITE);
  LCD_SetBacklight(100);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, RED);
  Paint_Clear(BLACK);

  // array size is 115200
  // #define imageHeight 240
  // #define imageWidth 240

  // array size is 115200
  // static byte imgBuffer[imageWidth * imageHeight * 2]; // 2 bytes per pixel assuming 16-bit color depth
  // memcpy_P(imgBuffer, img, sizeof(img));  // Copy image data from flash to RAM

  ; // Draw the image from RAM

  // for (i = 0; i < 1000; i++) {
  //   uint16_t randomColor = RGB565(random(256), random(256), random(256));
  //   // Paint_DrawString_EN(rand() % 200, rand() % 300, "Cage_Log", &Font24, BLACK, randomColor);
  // };
  Paint_DrawImage(gImage_70X70, 0, 0, 240, 240);
}

void loop() {
  uint16_t randomColor = RGB565(random(256), random(256), random(256));
  Paint_DrawString_EN(rand() % 200, rand() % 300, "Cage_Log", &Font24, BLACK, randomColor);
  Paint_DrawString_EN(rand() % 400, rand() % 400, "Wacko", &Font24, randomColor, BLACK);
  Paint_DrawString_EN(rand() % 400, rand() % 400, "Weirdo", &Font24, randomColor, BLACK);
}

