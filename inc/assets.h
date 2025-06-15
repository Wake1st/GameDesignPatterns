#ifndef ASSETS
#define ASSETS

#include "raylib.h"

// typedef struct Assets
// {
//   static Texture2D arrow;
// } Assets;

class Assets
{
public:
  static void storeAssets(Texture2D arrow_)
  {
    arrow = arrow_;
  }

  static Texture2D getArrow()
  {
    return arrow;
  }

private:
  static Texture2D arrow;
};

#endif
