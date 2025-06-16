#ifndef INPUT_QUEUE
#define INPUT_QUEUE

#include <iostream>

#include "command.h"

#define MAX_ALLOWED 8
#define COOLDOWN 0.6f

class InputQueue
{
public:
  void addInput(Command *command);
  Command *update();
  void draw();

private:
  Command *pending[MAX_ALLOWED];
  int head, tail = 0;
  float timer = 0.0;
};

void InputQueue::addInput(Command *command)
{
  // do not add if pending is full
  if ((tail + 1) % MAX_ALLOWED == head)
    return;

  // add to the end of the list
  pending[tail] = command;
  tail = (tail + 1) % MAX_ALLOWED;
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
  head = (head + 1) % MAX_ALLOWED;
  return command;
}

void InputQueue::draw()
{
  DrawText("Use the arrow keys to move.", 40, 120, 20, BLACK);

  DrawText(TextFormat("tail:\t%i", tail), 20, 160, 20, DARKPURPLE);
  DrawText(TextFormat("head:\t%i", head), 20, 180, 20, DARKPURPLE);
}

#endif
