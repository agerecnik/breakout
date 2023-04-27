#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "ball.h"
#include "brick.h"
#include "paddle.h"

bool is_interacting(const Entity& e1, const Entity& e2);
void handle_collision(Ball& b, const Paddle& p);
void handle_collision(Ball& b, Brick& br);

#endif