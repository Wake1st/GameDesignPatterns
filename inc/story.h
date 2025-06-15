#ifndef STORY
#define STORY

#include <iostream>
#include <vector>

#include "globals.h"
#include "command.h"
#include "actor.h"
#include "input.h"
#include "assets.h"

class Story
{
public:
  Story(Actor *act);
  bool update();
  void draw();
  void draw3D();

private:
  InputHandler *input;
  Command *commands[COMMAND_COUNT];
  int end = 0, index = 0;
  Actor *actor;

  void removeFrom(int ind);
};

Story::Story(Actor *act)
{
  input = new InputHandler();
  actor = act;
}

bool Story::update()
{
  if (actor->isMoving)
  {
    actor->move();
    return false;
  }

  Command *command = input->handleInput();
  if (command)
  {
    // ensure we aren't exceeding bounds
    if (index >= COMMAND_COUNT)
    {
      return false;
    }

    // execute command on actor
    command->execute(actor);

    // add to end, or remove up to
    if (index < end)
    {
      commands[index++] = command;
      Story::removeFrom(index);
      end = index;
    }
    else
    {
      commands[index++] = command;
      end++;
    }

    return true;
  }

  if (input->requestingUndo() && index > 0)
  {
    commands[--index]->undo(actor);
  }
  if (input->requestingRedo() && index < end)
  {
    commands[index++]->execute(actor);
  }

  return false;
}

void Story::draw()
{
  DrawText(TextFormat("MAX:\t%i", COMMAND_COUNT), 20, 160, 20, DARKPURPLE);
  DrawText(TextFormat("index:\t%i", index), 20, 200, 20, DARKPURPLE);
  DrawText(TextFormat("end:\t%i", end), 20, 240, 20, DARKPURPLE);
}

void Story::draw3D()
{
  DrawCube(actor->getPosition(), GRID_SIZE, GRID_SIZE, GRID_SIZE, PURPLE);
}

void Story::removeFrom(int index)
{
  for (int i = index; i < COMMAND_COUNT; i++)
  {
    commands[i] = NULL;
  }
}

#endif