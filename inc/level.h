#ifndef LEVEL
#define LEVEL

#include "raylib.h"

#include "screen.h"

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
  void update() override;
  void draw() override;
  void draw3D() override;
};

class EventQueueLevel : public Level
{
public:
  void update() override;
  void draw() override;
  void draw3D() override;
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
}

void CommandLevel::draw()
{
  DrawText("COMMAND Level", 20, 50, 40, BLACK);
  DrawText("Instructions", 20, 100, 20, BLACK);
}

void CommandLevel::draw3D()
{
}

void EventQueueLevel::update()
{
}

void EventQueueLevel::draw()
{
  DrawText("EVENT QUEUE Level", 20, 50, 40, BLACK);
  DrawText("Instructions", 20, 100, 20, BLACK);
}

void EventQueueLevel::draw3D()
{
}

void DoubleBufferLevel::update()
{
}

void DoubleBufferLevel::draw()
{
  DrawText("DOUBLE BUFFER Level", 20, 50, 40, BLACK);
  DrawText("Instructions", 20, 100, 20, BLACK);
}

void DoubleBufferLevel::draw3D()
{
}

#endif
