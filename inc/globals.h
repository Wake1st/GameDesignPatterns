#ifndef GLOBALS
#define GLOBALS

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

#define ACTOR_SIZE 2.0f
#define COMMAND_COUNT 8

typedef enum class Direction
{
  NONE,
  UP,
  DOWN,
  RIGHT,
  LEFT,
} Direction;

typedef struct ArrowData
{
  Vector2 offset;
  float rotation;
} ArrowData;

#endif
