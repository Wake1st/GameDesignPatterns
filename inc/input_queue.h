#ifndef INPUT_QUEUE
#define INPUT_QUEUE

#include <iostream>

#include "globals.h"
#include "command.h"

#define COOLDOWN 0.6f

class InputQueue
{
public:
  bool addInput(Command *command);
  Command *update();
  void draw();

private:
  Command *pending[COMMAND_COUNT];
  int head, tail = 0;
  float timer = 0.0;
};

bool InputQueue::addInput(Command *command)
{
  // do not add if pending is full
  if ((tail + 1) % COMMAND_COUNT == head)
    return false;

  // add to the end of the list
  pending[tail] = command;
  tail = (tail + 1) % COMMAND_COUNT;
  return true;
}

Command *InputQueue::update()
{
  // first, check timer for movement
  timer -= GetFrameTime();
  if (timer > 0.f)
  {
    return NULL;
  }
  else if (head == tail)
  {
    timer = 0.f;
    return NULL;
  }
  else
  {
    timer = COOLDOWN;
  }

  // return command
  Command *command = pending[head];
  head = (head + 1) % COMMAND_COUNT;
  return command;
}

void InputQueue::draw()
{
  DrawText("Use the arrow keys to move.", 40, 120, 20, BLACK);

  DrawText(TextFormat("tail:\t%i", tail), 20, 160, 20, DARKPURPLE);
  DrawText(TextFormat("head:\t%i", head), 20, 180, 20, DARKPURPLE);
}

#endif
