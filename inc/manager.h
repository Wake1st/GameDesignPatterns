#ifndef MANAGER
#define MANAGER

#include "level.h"
#include "command.h"
#include "menu.h"

typedef struct ManagerResources
{
  MenuResources menu;
  LevelResources level;
} ManagerResources;

class ScreenManager
{
public:
  ScreenManager(ManagerResources res)
  {
    menu = new Menu(res.menu);

    levelRes = res.level;
    currentLevel = new CommandLevel(res.level);
    menuOpen = true;
  }
  void screenSelection(Screens selection);
  void update();
  void draw();
  void draw3D();

private:
  Screens currentScreen;
  Menu *menu;
  Level *currentLevel;
  bool menuOpen;

  LevelResources levelRes;
};

void ScreenManager::update()
{
  // run the level
  Screens selection;
  if (menuOpen)
    selection = menu->update();
  else
  {
    currentLevel->update();

    if (IsKeyPressed(KEY_TAB))
      selection = Screens::MENU;
  }

  // check for screen swap
  screenSelection(selection);
}

void ScreenManager::draw()
{
  if (menuOpen)
    menu->draw();
  else
  {
    currentLevel->draw();
    DrawText("Select 'tab' to open menu, and 'esc' to exit game.", 140, 20, 20, BLACK);
  }
}

void ScreenManager::draw3D()
{
  if (!menuOpen)
    currentLevel->draw3D();
}

void ScreenManager::screenSelection(Screens selection)
{
  switch (selection)
  {
  case Screens::COMMAND:
    currentLevel = new CommandLevel(levelRes);
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
    break;
  case Screens::NONE:
  default:
    // DO NOTHING
    break;
  }
}

#endif
