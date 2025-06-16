#ifndef QUEUE_DISPLAY
#define QUEUE_DISPLAY

#include <unordered_map>
#include "raylib.h"
#include "raymath.h"

#include "globals.h"
#include "command.h"

#define QUARTER 90.f
#define SIZE 128.f
#define GAP 32.f

class QueueDisplay
{
public:
  QueueDisplay(Texture2D arr);
  void addNew();
  void shiftHead();
  void draw();

private:
  Texture2D arrow;
  Direction directions[COMMAND_COUNT] = {
      Direction::NONE,
      Direction::NONE,
      Direction::NONE,
      Direction::NONE,
      Direction::NONE,
      Direction::NONE,
      Direction::NONE,
      Direction::NONE};
  int tail, head = 0;

  Vector2 start;
  std::unordered_map<Direction, ArrowData> map;
};

QueueDisplay::QueueDisplay(Texture2D arr)
{
  // store texture data
  arrow = arr;
  start = (Vector2){SCREEN_WIDTH / 2.f - 624.f, SCREEN_HEIGHT - 160.f};

  map.insert({Direction::LEFT,
              (ArrowData){
                offset : (Vector2){0.f, SIZE},
                rotation : QUARTER * 3,
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
  map.insert({Direction::DOWN,
              (ArrowData){
                offset : (Vector2){SIZE, SIZE},
                rotation : QUARTER * 2,
              }});
}

void QueueDisplay::addNew()
{
  // add newest command
  if (IsKeyDown(KEY_LEFT))
    directions[tail] = Direction::LEFT;
  if (IsKeyDown(KEY_RIGHT))
    directions[tail] = Direction::RIGHT;
  if (IsKeyDown(KEY_UP))
    directions[tail] = Direction::UP;
  if (IsKeyDown(KEY_DOWN))
    directions[tail] = Direction::DOWN;

  // loop tail around
  tail = (tail + 1) % COMMAND_COUNT;
}

void QueueDisplay::shiftHead()
{
  // reset the focused display
  directions[head] = Direction::NONE;

  // loop head around
  head = (head + 1) % COMMAND_COUNT;
}

void QueueDisplay::draw()
{
  for (int i = 0; i < COMMAND_COUNT; i++)
  {
    // only valid directions are drawn
    Direction dir = directions[i];
    if (dir == Direction::NONE)
    {
      continue;
    }

    // setup values
    Vector2 position = Vector2Add(start, (Vector2){(SIZE + GAP) * i, 0.f});

    // only highlight head
    Color borderColor;
    if (i == head)
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
