#ifndef BALL_H
#define BALL_H

#include "constants.h"
#include "entity.h"

class Ball : public MovingEntity {
	static sf::Texture texture;

public:
	Ball(float x, float y);

	void update() override;
	void draw(sf::RenderWindow& window) override;

	void move_up() noexcept override;
	void move_down() noexcept override;
	void move_left() noexcept override;
	void move_right() noexcept override;
};

#endif