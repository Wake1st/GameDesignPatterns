#ifndef INPUT_DISPLAY
#define INPUT_DISPLAY

#include "raylib.h"
#include "raymath.h"

#include "globals.h"

#define QUARTER 90.f
#define SIZE 128.f
#define GAP 32.f

typedef enum Direction
{
  UP,
  DOWN,
  RIGHT,
  LEFT,
} Direction;

class InputDisplay
{
public:
  InputDisplay(Texture2D arr)
  {
    arrow = arr;
    start = (Vector2){SCREEN_WIDTH / 2.f - 624.f, SCREEN_HEIGHT - 160.f};
  }
  void update();
  void draw();

private:
  Texture2D arrow;
  Direction directions[COMMAND_COUNT];
  int index = 0;

  Vector2 start;
};

void InputDisplay::update()
{
  if (IsKeyDown(KEY_LEFT))
    directions[index++] = Direction::LEFT;
  if (IsKeyDown(KEY_RIGHT))
    directions[index++] = Direction::RIGHT;
  if (IsKeyDown(KEY_UP))
    directions[index++] = Direction::UP;
  if (IsKeyDown(KEY_DOWN))
    directions[index++] = Direction::DOWN;
}

void InputDisplay::draw()
{
  for (int i = 0; i < index; i++)
  {
    float rotation;
    Vector2 offset;
    switch (directions[i])
    {
    case Direction::LEFT:
      rotation = QUARTER * 1;
      offset = (Vector2){SIZE, 0.f};
      break;
    case Direction::DOWN:
      rotation = QUARTER * 2;
      offset = (Vector2){SIZE, SIZE};
      break;
    case Direction::RIGHT:
      rotation = QUARTER * 3;
      offset = (Vector2){0.f, SIZE};
      break;
    default:
      rotation = QUARTER * 0;
      offset = (Vector2){0.f, 0.f};
    }
    DrawTextureEx(
        arrow,
        Vector2Add(start, Vector2Add((Vector2){(SIZE + GAP) * i, 0.f}, offset)),
        rotation,
        1.0,
        WHITE);
  }
}

#endif
