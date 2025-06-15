#ifndef BUTTON
#define BUTTON

#include "raylib.h"
#include "screen.h"

#define BUTTON_FRAMES 3

class Button
{
public:
  Button(const char *btnText, Texture2D btnTexture, Vector2 btnPosition, Vector2 textOffset, Screens screenOption)
  {
    text = btnText;
    texture = btnTexture;
    position = btnPosition;
    offset = textOffset;

    frameHeight = (float)texture.height / BUTTON_FRAMES;
    rect = {0, 0, (float)texture.width, frameHeight};

    bounds = {
        position.x,
        position.y,
        rect.width,
        rect.height};

    screen = screenOption;
  }
  Screens update();
  void draw();

private:
  Texture2D texture;
  Vector2 position;
  Rectangle rect;
  const char *text;
  Vector2 offset;
  Rectangle bounds;

  int btnState;
  float frameHeight;

  Screens screen;
};

Screens Button::update()
{
  Screens selection;
  Vector2 mousePoint = GetMousePosition();

  if (CheckCollisionPointRec(mousePoint, bounds))
  {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
      btnState = 2;
    else
      btnState = 1;

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
      selection = screen;
    }
  }
  else
  {
    btnState = 0;
  }

  rect.y = btnState * frameHeight;

  return selection;
}

void Button::draw()
{
  DrawTextureRec(texture, rect, position, WHITE);
  DrawText(text, position.x + offset.x, position.y + offset.y, 40, BLACK);
}

#endif
