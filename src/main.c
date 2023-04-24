#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "../styles/enefete/enefete.h"
#include "calc.h"
#include "raygui.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  int textBoxEditMode = 0;
  int xval = 0;
  int xBoxEditMode = 0;
  char xBoxText[64] = "Enter the value of x:";

  char input_text[255] = {0};
  int isPressed = 0;
  int err = 0;
  string input = {0};
  double result = 0;

  InitWindow(screenWidth, screenHeight, "Calculator");
  Texture2D texture = LoadTexture(IMG_PATH "Background.png");
  Texture2D errorPng = LoadTexture(IMG_PATH "error.png");

  GuiLoadStyleEnefete();
  GuiSetStyle(DEFAULT, TEXT_SIZE, 45);

  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    //-------------------------------------------------------------------------------
    BeginDrawing();
    DrawTexture(texture, 0, 0, WHITE);

    DrawText("Enter an expression: ", 50, 25, 24, DARKBLUE);
    if (GuiTextBox((Rectangle){50, 50, 600, 60}, input_text, 100000,
                   textBoxEditMode))
      textBoxEditMode = !textBoxEditMode;
    isPressed = GuiButton((Rectangle){630, 50, 115, 60}, "=");

    DrawText("x = ", 54, 138, 40, DARKBLUE);
    if (GuiValueBox((Rectangle){125, 130, 200, 60}, "", &xval, -10000000,
                    10000000, xBoxEditMode))
      xBoxEditMode = !xBoxEditMode;

    DrawText("Your result: ", 50, 210, 27, DARKBLUE);

    if (isPressed) {
      printf("err");
      input.str = input_text;
      input.len = strlen(input.str);
      validation(input, &err);
      if (!err) {
        result = calc(input);

      } else {
        printf("err");
        DrawTexture(errorPng, 0, 0, WHITE);
      }
    }

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  //--------------------------------------------------------------------------------------
  CloseWindow();  // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
