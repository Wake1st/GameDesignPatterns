#ifndef MAIN_MENU
#define MAIN_MENU

#include "raylib.h"

class Menu
{
public:
  void update();
  void draw();
};

void Menu::update()
{
}

void Menu::draw()
{
  DrawText("select 'C' for command pattern", 320, 20, 40, BLACK);
  DrawText("select 'Q' for event queue", 320, 80, 40, BLACK);
  DrawText("select 'D' for double buffer", 320, 140, 40, BLACK);
}

#endif
