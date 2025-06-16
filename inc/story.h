#ifndef STORY
#define STORY

#include "globals.h"
#include "command.h"
#include "actor.h"
#include "input.h"
#include "input_display.h"

class Story
{
public:
  Story(Actor *act, Texture2D arrow);
  void update();
  void draw();
  void draw3D();

private:
  InputDisplay *display;
  InputHandler *input;
  Command *commands[COMMAND_COUNT];
  Actor *actor;
  int end = 0, index = 0;

  void removeFrom(int ind);
};

Story::Story(Actor *act, Texture2D arrow)
{
  display = new InputDisplay(arrow);
  input = new InputHandler();
  actor = act;
}

void Story::update()
{
  if (actor->isMoving)
  {
    actor->move();
    return;
  }

  Command *command = input->handleInput();
  if (command)
  {
    // ensure we aren't exceeding bounds
    if (index >= COMMAND_COUNT)
    {
      return;
    }

    // execute command on actor
    command->execute(actor);

    // add new arrow
    display->addNew(index);

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
  }

  if (input->requestingUndo() && index > 0)
  {
    commands[--index]->undo(actor);
    display->setFocus(index);
  }
  if (input->requestingRedo() && index < end)
  {
    display->setFocus(index);
    commands[index++]->execute(actor);
  }
}

void Story::draw()
{
  DrawText("Use the arrow keys to move.", 40, 120, 20, BLACK);
  DrawText("'ctrl+z'/'ctrl+y' to undo/redo.", 40, 140, 20, BLACK);

  DrawText(TextFormat("Maximum Index:\t%i", COMMAND_COUNT), 20, 180, 20, DARKPURPLE);
  DrawText(TextFormat("Current Index:\t%i", index), 20, 200, 20, DARKPURPLE);
  DrawText(TextFormat("Highest Index:\t%i", end), 20, 220, 20, DARKPURPLE);

  display->draw();
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
    display->removeAt(i);
  }
}

#endif