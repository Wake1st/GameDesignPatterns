#ifndef COMMAND_
#define COMMAND_

#include "raylib.h"
#include "actor.h"

#define GRID_SIZE 2.0f

// base class
class Command
{
public:
  virtual void execute(Actor *actor) = 0;
  virtual void undo(Actor *actor) = 0;
};

class MoveCommand : public Command
{
public:
  MoveCommand(float x, float y);
  virtual void execute(Actor *actor);
  virtual void undo(Actor *actor);

private:
  float x, y;
};

MoveCommand::MoveCommand(float x_, float y_) : x(x_), y(y_) {}

void MoveCommand::execute(Actor *actor)
{
  actor->adjustPosition(x, y);
  actor->isMoving = true;
  actor->movesRemaining--;
}

void MoveCommand::undo(Actor *actor)
{
  actor->adjustPosition(-x, -y);
  actor->isMoving = true;
  actor->movesRemaining++;
}

#endif