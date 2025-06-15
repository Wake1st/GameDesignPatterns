/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "globals.h"
#include "manager.h"

int main()
{
  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Design Pattern Examples");

  // load resources
  Texture2D button = LoadTexture("resources/button.png");
  Texture2D arrow = LoadTexture("resources/arrow.png");

  // setup a 3D camera
  Vector3 originPoint = Vector3{0.0f, 0.0f, 0.0f};
  Camera3D mainCamera = {0};
  mainCamera.position = Vector3{0.0f, 10.0f, 10.0f};
  mainCamera.target = originPoint;
  mainCamera.up = Vector3{0.0f, 1.0f, 0.0f};
  mainCamera.fovy = 45.0f;
  mainCamera.projection = CAMERA_PERSPECTIVE;

  // example screen
  ScreenManager *manager = new ScreenManager(ManagerResources{
      MenuResources{btnTexture : button},
      LevelResources{arrow : arrow}});

  // game loop
  while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
  {
    //	-	-	-	-	-	-	-	-	UPDATE	-	-	-	-	-	-	-	-
    manager->update();

    //	-	-	-	-	-	-	-	-	DRAWING	-	-	-	-	-	-	-	-
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(DARKGRAY);

    BeginMode3D(mainCamera);
    manager->draw3D();
    EndMode3D();

    // draw some text using the default font
    manager->draw();
    DrawFPS(20, 20);

    // end the frame and get ready for the next one  (display frame, poll input, etc...)
    EndDrawing();
  }

  // unload and resources
  UnloadTexture(button);
  UnloadTexture(arrow);

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}