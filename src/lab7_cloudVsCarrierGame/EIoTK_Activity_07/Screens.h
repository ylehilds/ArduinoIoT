#include "Arduino_MKRIoTCarrier.h"

MKRIoTCarrier carrier;

bool screen_flag = true;

int screen = 0;
int num = 0;
int boardProv = 0;

int randomX;
int randomY;

bool boardGuess_confirm = false;

void mainScreen(void)
{
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextSize(5);
  carrier.display.setTextColor(ST77XX_RED);
  carrier.display.setCursor(50, 40);
  carrier.display.print("SPOOF");
  carrier.display.setTextSize(4);
  carrier.display.setCursor(25, 95);
  carrier.display.print("The Game");
  carrier.display.setTextSize(2);
  carrier.display.setCursor(15, 200);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.print("Press 02 to start");
}

void guessScreen(void)
{
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextSize(3);
  carrier.display.setTextColor(ST77XX_BLUE);
  carrier.display.setCursor(5, 8);
  carrier.display.print("P2_G");
  carrier.display.drawCircle(95, 17, 15, ST77XX_GREEN);
  carrier.display.setCursor(125, 8);
  carrier.display.print("P2_N");
  carrier.display.drawCircle(215, 17, 15, ST77XX_GREEN);
  carrier.display.setTextSize(2);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setCursor(20, 55);
  carrier.display.print("P1 guessed number");
  carrier.display.setTextSize(3);
  carrier.display.setCursor(60, 90);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.print("Confirm");
  carrier.display.setTextSize(5);
  carrier.display.setCursor(20, 200);
  carrier.display.print("+");
  carrier.display.setCursor(200, 200);
  carrier.display.print("-");
  carrier.display.setCursor(110, 150);
  carrier.display.setTextColor(ST77XX_GREEN);
  carrier.display.print(boardGuess);
}

void beansScreen(void)
{
  carrier.display.fillRect(0, 34, 240, 205, ST77XX_BLACK);
  carrier.display.setTextSize(2);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setCursor(35, 55);
  carrier.display.print("P1 beans number");
  carrier.display.setTextSize(3);
  carrier.display.setCursor(60, 90);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.print("Confirm");
  carrier.display.setTextSize(5);
  carrier.display.setCursor(20, 200);
  carrier.display.print("+");
  carrier.display.setCursor(200, 200);
  carrier.display.print("-");
  carrier.display.setCursor(110, 150);
  carrier.display.setTextColor(ST77XX_GREEN);
  carrier.display.print(boardBeans);
}

void resultsScreen(void)
{
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextColor(ST77XX_BLUE);
  carrier.display.setTextSize(5);
  carrier.display.setCursor(20, 0);
  carrier.display.print("RESULTS");
  carrier.display.setTextColor(ST77XX_GREEN);
  carrier.display.setCursor(100, 50);
  carrier.display.print("P1");
  carrier.display.setCursor(180, 50);
  carrier.display.print("P2");
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(3);
  carrier.display.setCursor(0, 115);
  carrier.display.print("Guess");
  carrier.display.setCursor(0, 180);
  carrier.display.print("Beans");
  carrier.display.setTextSize(5);
  carrier.display.setCursor(110, 110);
  carrier.display.print(boardGuess);
  carrier.display.setCursor(180, 110);
  carrier.display.print(cloudGuess);
  carrier.display.setCursor(110, 170);
  carrier.display.print(boardBeans);
  carrier.display.setCursor(180, 170);
  carrier.display.print(cloudBeans);
}

void p1_winnerScreen(void)
{
  carrier.display.fillScreen(ST77XX_WHITE);

  for (int i=0; i < 8; i++) {
    randomX = random(0, 240);
    randomY = random(0, 240);
    carrier.display.fillCircle(randomX, randomY, 20, ST77XX_GREEN);
  }

  carrier.display.setTextColor(ST77XX_ORANGE);
  carrier.display.setTextSize(5);
  carrier.display.setCursor(30, 60);
  carrier.display.print("WINNER");
  carrier.display.setCursor(100, 110);
  carrier.display.print("P1");
}


void p2_winnerScreen(void)
{
  carrier.display.fillScreen(ST77XX_BLACK);

  for (int i=0; i < 8; i++) {
    randomX = random(0, 240);
    randomY = random(0, 240);
    carrier.display.fillCircle(randomX, randomY, 20, ST77XX_RED);
  }

  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(5);
  carrier.display.setCursor(30, 60);
  carrier.display.print("WINNER");
  carrier.display.setCursor(100, 110);
  carrier.display.print("P2");
}

void tieScreen(void)
{
  carrier.display.fillScreen(ST77XX_ORANGE);

  for (int i=0; i < 4; i++) {
    randomX = random(0, 240);
    randomY = random(0, 240);
    carrier.display.fillCircle(randomX, randomY, 20, ST77XX_RED);
    carrier.display.fillCircle(randomY, randomX, 20, ST77XX_GREEN);
  }

  carrier.display.setTextColor(ST77XX_BLACK);
  carrier.display.setTextSize(5);
  carrier.display.setCursor(90, 100);
  carrier.display.print("TIE");
}

void numberUpdate(int number)
{
  carrier.display.setTextSize(5);
  carrier.display.fillRect(60, 115, 130, 100, ST77XX_BLACK);
  carrier.display.setCursor(110, 150);
  carrier.display.setTextColor(ST77XX_GREEN);
  carrier.display.print(number);
}

void resetValues(void)
{
  screen = 0;
  cloudGuess = 0;
  cloudBeans = 0;
  boardGuess = 0;
  boardBeans = 0;
  boardProv = 0;
  cloudBeans_confirm = false;
  cloudGuess_confirm = false;
  boardGuess_confirm = false;
  boardBeans_Ready = false;
  boardGuess_Ready = false;
  num = 0;
}