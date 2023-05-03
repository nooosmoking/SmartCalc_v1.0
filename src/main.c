#include "raygui.h"
#define RAYGUI_IMPLEMENTATION
#include "calc.h"
#include "enefete.h"
#include "raylib.h"

int main(void) {
  const int screenWidth = 760;
  const int screenHeight = 470;

  int textBoxEditMode = 1;
  char input_box[255] = {0};
  char input_str[255] = {0};
  string input = {0};

  int isPressed = 0;
  int timePressed = 0;
  int err = 0;

  double result = 0;
  char resultText[255] = {0};

  double xMax = 0;
  double xMin = 0;
  double yMax = 0;
  double yMin = 0;
  double xval = 0;
  int xBoxEditMode = 0;
  int xMaxEditMode = 0;
  int xMinEditMode = 0;
  int yMaxEditMode = 0;
  int yMinEditMode = 0;

  char xMaxText[30] = {0};
  char xMinText[30] = {0};
  char yMaxText[30] = {0};
  char yMinText[30] = {0};
  char xValText[30] = {0};

  initRange(xMaxText, xMinText, yMaxText, yMinText);

  InitWindow(screenWidth, screenHeight, "Calculator");
  Texture2D background = LoadTexture(IMG_PATH "Background.png");
  Texture2D errorPng = LoadTexture(IMG_PATH "error.png");
  Texture2D pix = LoadTexture(IMG_PATH "pix.png");
  Texture2D errorWar = pix;

  GuiLoadStyleEnefete();
  GuiSetStyle(DEFAULT, TEXT_SIZE, 45);

  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    //-------------------------------------------------------------------------------
    BeginDrawing();
    DrawTexture(background, 0, 0, WHITE);

    DrawText("Enter an expression: ", 30, 22, 25, DARKBLUE);

    if (GuiTextBox((Rectangle){30, 50, 600, 60}, input_box, 255,
                   textBoxEditMode))
      textBoxEditMode = !textBoxEditMode;

    isPressed = GuiButton((Rectangle){640, 50, 90, 60}, "=");

    DrawText("x = ", 362, 138, 40, DARKBLUE);
    if (GuiTextBox((Rectangle){445, 130, 285, 60}, xValText, 29, xBoxEditMode))
      xBoxEditMode = !xBoxEditMode;

    GuiSetStyle(DEFAULT, TEXT_SIZE, 33);
    DrawText("       MIN          MAX", 360, 200, 30, DARKBLUE);
    DrawText(" x ", 360, 235, 30, DARKBLUE);
    if (GuiTextBox((Rectangle){575, 230, 155, 40}, xMaxText, 29, xMaxEditMode))
      xMaxEditMode = !xMaxEditMode;
    if (GuiTextBox((Rectangle){400, 230, 155, 40}, xMinText, 29, xMinEditMode))
      xMinEditMode = !xMinEditMode;
    DrawText("       MIN          MAX", 360, 280, 30, DARKBLUE);
    DrawText(" y ", 360, 315, 30, DARKBLUE);
    if (GuiTextBox((Rectangle){575, 310, 155, 40}, yMaxText, 29, yMaxEditMode))
      yMaxEditMode = !yMaxEditMode;
    if (GuiTextBox((Rectangle){400, 310, 155, 40}, yMinText, 29, yMinEditMode))
      yMinEditMode = !yMinEditMode;

    GuiSetStyle(DEFAULT, TEXT_SIZE, 45);

    if (isPressed) {
      strcpy(input_str, input_box);
      input.str = input_str;
      input.len = strlen(input.str);
      input = validation(input, &err);
      xval = validVal(xValText, &err);
      xMax = validVal(xMaxText, &err);
      xMin = validVal(xMinText, &err);
      yMax = validVal(yMaxText, &err);
      yMin = validVal(yMinText, &err);
      if (xMax < xMin) err++;
      if (yMax < yMin) err++;
      timePressed++;
      if (!err) {
        result = calc(input, xval);
        strcpy(resultText, "Your result: ");
        errorWar = pix;
      } else {
        errorWar = errorPng;
        strcpy(resultText, "");
      }
    }

    if (input_box[0] == 0) {
      timePressed = 0;
    }
    if (timePressed) {
      DrawText(resultText, 370, 360, 30, DARKBLUE);
      DrawDouble(result, err);
      DrawTexture(errorWar, 40, 120, WHITE);
      DrawGraph(input, err, xMax, xMin, yMax, yMin, xMaxText, xMinText,
                yMaxText, yMinText);
    }

    EndDrawing();

    //----------------------------------------------------------------------------------
  }

  //--------------------------------------------------------------------------------------
  CloseWindow();  // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
