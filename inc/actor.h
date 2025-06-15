#ifndef ACTOR
#define ACTOR

#include "raylib.h"
#include "raymath.h"

#define CLOSENESS 0.001f
#define SPEED 42.f

class Actor
{
public:
  bool isMoving;
  int movesRemaining;

  Actor();
  void adjustPosition(float x, float y);
  void move();
  Vector3 getPosition();

private:
  Vector3 currentPosition;
  Vector3 targetPosition;
};

Actor::Actor()
{
  Vector3 origin = (Vector3){0.f, 0.f, 0.f};
  currentPosition = origin;
  targetPosition = origin;
  isMoving = false;
}

void Actor::adjustPosition(float x, float y)
{
  targetPosition = Vector3Add(currentPosition, Vector3{x, 0.0f, -y});
}

void Actor::move()
{
  float distance = Vector3Distance(currentPosition, targetPosition);
  float speed = SPEED * GetFrameTime();

  currentPosition = Vector3MoveTowards(currentPosition, targetPosition, distance * speed);

  isMoving = (currentPosition != targetPosition);
}

Vector3 Actor::getPosition()
{
  return currentPosition;
}

#endif
