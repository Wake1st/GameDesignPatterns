#ifndef BUTTON
#define BUTTON

#include "raylib.h"

#define BUTTON_FRAMES 3

class Button
{
public:
  Button(const char *btnText, Texture2D btnTexture, Vector2 btnPosition, Vector2 textOffset)
  {
    text = btnText;
    texture = btnTexture;
    position = btnPosition;
    offset = textOffset;

    frameHeight = (float)texture.height / BUTTON_FRAMES;
    rect = {0, 0, (float)texture.width, frameHeight};
  }
  void update();
  void draw();

private:
  Texture2D texture;
  Vector2 position;
  Rectangle rect;
  const char *text;
  Vector2 offset;

  float frameHeight;
};

void Button::update()
{
}

void Button::draw()
{
  DrawTextureRec(texture, rect, position, WHITE);
  DrawText(text, position.x + offset.x, position.y + offset.y, 40, BLACK);
}

#endif
