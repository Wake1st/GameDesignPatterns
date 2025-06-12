#ifndef MAIN_MENU
#define MAIN_MENU

#include "raylib.h"
#include "raymath.h"
#include "globals.h"
#include "button.h"

typedef struct MenuResources
{
  Texture2D btnTexture;
} MenuResources;

class Menu
{
public:
  Menu(MenuResources res)
  {
    Vector2 center = (Vector2){SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    Vector2 gap = (Vector2){0.0f, 32.0f};

    command = new Button("COMMAND", res.btnTexture, center + (Vector2){-256.0f, -192.0f} - gap, (Vector2){150.0f, 44.0f});
    queue = new Button("EVENT QUEUE", res.btnTexture, center + (Vector2){-256.0, -64.0f}, (Vector2){105.0f, 44.0f});
    buffer = new Button("DOUBLE BUFFER", res.btnTexture, center + (Vector2){-256.0f, 64.0f} + gap, (Vector2){85.0f, 44.0f});
  }
  void update();
  void draw();

private:
  Button *command;
  Button *queue;
  Button *buffer;
};

void Menu::update()
{
  command->update();
  queue->update();
  buffer->update();
}

void Menu::draw()
{
  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKBROWN);
  command->draw();
  queue->draw();
  buffer->draw();
}

#endif
