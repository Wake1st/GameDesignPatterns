#ifndef LEVEL
#define LEVEL

#include "raylib.h"

#include "screen.h"
#include "story.h"
#include "actor.h"
#include "command.h"
#include "command_display.h"
#include "input_queue.h"

typedef struct LevelResources
{
  Texture2D arrow;
} LevelResources;

class Level
{
public:
  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void draw3D() = 0;
};

class CommandLevel : public Level
{
public:
  CommandLevel(LevelResources res)
  {
    actor = new Actor();
    story = new Story(actor, res.arrow);
  }
  ~CommandLevel()
  {
    delete actor;
    delete story;
  }
  void update() override;
  void draw() override;
  void draw3D() override;

private:
  Story *story;
  Actor *actor;
};

class InputQueueLevel : public Level
{
public:
  InputQueueLevel()
  {
    inputHandler = new InputHandler();
    inputQueue = new InputQueue();
    actor = new Actor();
  }
  void update() override;
  void draw() override;
  void draw3D() override;

private:
  InputHandler *inputHandler;
  InputQueue *inputQueue;
  Actor *actor;
};

class DoubleBufferLevel : public Level
{
public:
  void update() override;
  void draw() override;
  void draw3D() override;
};

// IMPLEMENTATIONS
void CommandLevel::update()
{
  story->update();
}

void CommandLevel::draw()
{
  DrawText("COMMAND", 20, 50, 40, BLACK);
  DrawText("Instructions:", 20, 100, 20, BLACK);

  story->draw();
}

void CommandLevel::draw3D()
{
  story->draw3D();
}

void InputQueueLevel::update()
{
  // store inputs from user
  Command *newCommand = inputHandler->handleInput();
  if (newCommand)
  {
    inputQueue->addInput(newCommand);
  }

  // pass command to actor when ready
  Command *readyCommand = inputQueue->update();
  if (readyCommand)
  {
    readyCommand->execute(actor);
  }

  // make sure the actually move the character
  actor->move();
}

void InputQueueLevel::draw()
{
  DrawText("INPUT QUEUE", 20, 50, 40, BLACK);
  DrawText("Instructions:", 20, 100, 20, BLACK);

  inputQueue->draw();
}

void InputQueueLevel::draw3D()
{
  DrawCube(actor->getPosition(), GRID_SIZE, GRID_SIZE, GRID_SIZE, PURPLE);
}

void DoubleBufferLevel::update()
{
}

void DoubleBufferLevel::draw()
{
  DrawText("DOUBLE BUFFER", 20, 50, 40, BLACK);
  DrawText("Instructions:", 20, 100, 20, BLACK);
}

void DoubleBufferLevel::draw3D()
{
}

#endif
