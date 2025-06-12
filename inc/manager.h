#ifndef MANAGER
#define MANAGER

#include "level.h"
#include "menu.h"

class ScreenManager
{
public:
  ScreenManager()
  {
    currentLevel = new CommandLevel();
    menuOpen = true;
  }
  void update();
  void draw();

private:
  Screens currentScreen;
  Menu *menu;
  Level *currentLevel;
  bool menuOpen;

  Screens screenSelection();
};

void ScreenManager::update()
{
  // check for screen swap
  Screens selection = screenSelection();
  switch (selection)
  {
  case Screens::COMMAND:
    currentLevel = new CommandLevel();
    menuOpen = false;
    break;
  case Screens::EVENT_QUEUE:
    currentLevel = new EventQueueLevel();
    menuOpen = false;
    break;
  case Screens::DOUBLE_BUFFER:
    currentLevel = new DoubleBufferLevel();
    menuOpen = false;
    break;
  case Screens::MENU:
    menuOpen = !menuOpen;
  }

  // run the level
  if (menuOpen)
    menu->update();
  else
    currentLevel->update();
}

void ScreenManager::draw()
{
  if (menuOpen)
    menu->draw();
  else
    currentLevel->draw();
}

Screens ScreenManager::screenSelection()
{
  if (IsKeyPressed(KEY_C))
    return Screens::COMMAND;
  if (IsKeyPressed(KEY_Q))
    return Screens::EVENT_QUEUE;
  if (IsKeyPressed(KEY_D))
    return Screens::DOUBLE_BUFFER;
  if (IsKeyPressed(KEY_TAB))
    return Screens::MENU;
  return Screens::NONE;
}

#endif
