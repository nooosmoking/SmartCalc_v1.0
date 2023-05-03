#include <string.h>
#include "raygui.h"
#include "raylib.h"
#include "calc.h"
#include "rlgl.h"  // OpenGL abstraction layer to OpenGL 1.1, 2.1, 3.3+ or ES2

void initRange(char* xMaxText, char* xMinText, char* yMaxText, char* yMinText) {
  strcpy(xMaxText, "15");
  strcpy(yMaxText, "15");
  strcpy(xMinText, "-15");
  strcpy(yMinText, "-15");
};

void DrawDouble(double val, int err) {
  char str[255] = "";
  if (!err) {
    if (fmod(val, 1) != 0) {
      sprintf(str, "%.7lf", val);
    } else {
      sprintf(str, "%.0lf", val);
    }
    DrawText(str, 365, 395, 43, DARKBLUE);
  }
}

void initGraph(char* xMaxText, char* xMinText, char* yMaxText, char* yMinText) {
  GuiGrid((Rectangle){40, 140, 300, 300}, NULL, 50, 2);
  DrawText(xMaxText, 345, 280, 20, DARKBLUE);
  DrawText(xMinText, 3, 280, 20, DARKBLUE);
  DrawText(yMaxText, 180, 120, 20, DARKBLUE);
  DrawText(yMinText, 180, 443, 20, DARKBLUE);

  DrawLine(40, 290, 340, 290, DARKBLUE);
  DrawLine(40, 291, 340, 291, DARKBLUE);

  DrawLine(190, 140, 190, 440, DARKBLUE);
  DrawLine(191, 140, 191, 440, DARKBLUE);
  DrawTriangle((Vector2){325, 285}, (Vector2){325, 297}, (Vector2){340, 290},
               DARKBLUE);
  DrawTriangle((Vector2){185, 155}, (Vector2){195, 155}, (Vector2){190, 140},
               DARKBLUE);
}

void DrawGraph(string input, double err, double xMax, double xMin, double yMax,
               double yMin, char* xMaxText, char* xMinText, char* yMaxText,
               char* yMinText) {
  int i = 0;
  Vector2 data[100000] = {0};
  float step = 0;
  float y = 0.;
  float masX = 0, masY = 0;
  char xMaxTextTmp[30] = {0};
  char xMinTextTmp[30] = {0};
  char yMaxTextTmp[30] = {0};
  char yMinTextTmp[30] = {0};

  strcpy(xMaxTextTmp, xMaxText);
  strcpy(xMinTextTmp, xMinText);
  strcpy(yMaxTextTmp, yMaxText);
  strcpy(yMinTextTmp, yMinText);
  int len = 0;
  if (!err) {
    if (fabs(xMax) > fabs(xMin)) {
      memmove(&(xMinTextTmp[1]), xMaxText, strlen(xMaxText));
      xMinTextTmp[0] = '-';
      step = xMax * 2. / 1200.;
      masX = 10. * (15. / xMax);
    } else if (fabs(xMax) < fabs(xMin)) {
       xMinText++;
      memmove(xMaxTextTmp, xMinText, strlen(xMinText));
      xMinText--;
      step = xMin * 2. / 1200. * -1.;
      masX = -10. * (15. / xMin);
    } else {
      step = xMax * 2. / 1200.;
      masX = 10. * (15. / xMax);
    }

    if (fabs(yMax) > fabs(yMin)) {
      memmove(&(yMinTextTmp[1]), yMaxText, strlen(yMaxText));
      yMinTextTmp[0] = '-';
      masY = 10. * (15. / yMax);
    } else if (fabs(yMax) < fabs(yMin)) {
      ++yMinText;
      memmove(yMaxTextTmp, yMinText, strlen(yMinText));
      yMinText--;
      masY = -10. * (15. / yMin);
    } else {
      masY = 10. * (15. / yMax);
    }
    initGraph(xMaxTextTmp, xMinTextTmp, yMaxTextTmp, yMinTextTmp);

    for (float x = (float)xMin; x < (float)xMax; x += step) {
      y = (float)calc(input, (double)x);
      if (y < yMax && y > yMin) {
        data[i].y = 290. - y * masY;
        data[i].x = 190. + x * masX;
        i++;
      }
    }

    rlBegin(RL_LINES);
    rlColor3f(70, 255, 255);
    for (int j = 1; j < i; j++) {
      if (data[j].y <= 440 && data[j].y >= 140 && data[j - 1].y <= 440 &&
          data[j - 1].y >= 140) {
        rlVertex2i(data[j - 1].x, data[j - 1].y);
        rlVertex2i(data[j].x, data[j].y);
      }
    }
    rlEnd();
  }
}