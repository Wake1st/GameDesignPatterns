#ifndef COMMAND_DISPLAY
#define COMMAND_DISPLAY

#include <unordered_map>
#include "raylib.h"
#include "raymath.h"

#include "globals.h"

#define QUARTER 90.f
#define SIZE 128.f
#define GAP 32.f

typedef enum class Direction
{
  NONE,
  UP,
  DOWN,
  RIGHT,
  LEFT,
} Direction;

typedef struct ArrowData
{
  Vector2 offset;
  float rotation;
} ArrowData;

class CommandDisplay
{
public:
  CommandDisplay(Texture2D arr);
  void addNew(int i);
  void setFocus(int i);
  void removeAt(int i);
  void draw();

private:
  Texture2D arrow;
  Direction directions[COMMAND_COUNT];
  int index = 0;

  Vector2 start;
  std::unordered_map<Direction, ArrowData> map;
  int focus = 0;
};

CommandDisplay::CommandDisplay(Texture2D arr)
{
  arrow = arr;
  start = (Vector2){SCREEN_WIDTH / 2.f - 624.f, SCREEN_HEIGHT - 160.f};

  map.insert({Direction::LEFT,
              (ArrowData){
                offset : (Vector2){0.f, SIZE},
                rotation : QUARTER * 3,
              }});
  map.insert({Direction::DOWN,
              (ArrowData){
                offset : (Vector2){SIZE, SIZE},
                rotation : QUARTER * 2,
              }});
  map.insert({Direction::RIGHT,
              (ArrowData){
                offset : (Vector2){SIZE, 0.f},
                rotation : QUARTER * 1,
              }});
  map.insert({Direction::UP,
              (ArrowData){
                offset : (Vector2){0.f, 0.f},
                rotation : QUARTER * 0,
              }});
}

void CommandDisplay::addNew(int i)
{
  // set new focus
  focus = i;
  index = i;

  // add based on input
  if (IsKeyDown(KEY_LEFT))
    directions[index++] = Direction::LEFT;
  if (IsKeyDown(KEY_RIGHT))
    directions[index++] = Direction::RIGHT;
  if (IsKeyDown(KEY_UP))
    directions[index++] = Direction::UP;
  if (IsKeyDown(KEY_DOWN))
    directions[index++] = Direction::DOWN;
}

void CommandDisplay::setFocus(int i)
{
  focus = i;
}

void CommandDisplay::removeAt(int i)
{
  directions[i] = Direction::NONE;
}

void CommandDisplay::draw()
{
  for (int i = 0; i < index; i++)
  {
    // only valid directions are drawn
    Direction dir = directions[i];
    if (dir == Direction::NONE)
    {
      continue;
    }

    // setup values
    Vector2 position = Vector2Add(start, (Vector2){(SIZE + GAP) * i, 0.f});

    // only highlight focus
    Color borderColor;
    if (i == focus)
      borderColor = YELLOW;
    else
      borderColor = GRAY;

    // draw border
    DrawRectangleRoundedLinesEx((Rectangle){position.x - 8.f, position.y - 8.f, SIZE + 16.f, SIZE + 16.f}, 0.1f, 12, 8.f, borderColor);

    // draw arrow
    ArrowData data = map[dir];
    DrawTextureEx(
        arrow,
        Vector2Add(position, data.offset),
        data.rotation,
        1.0,
        WHITE);
  }
}

#endif
