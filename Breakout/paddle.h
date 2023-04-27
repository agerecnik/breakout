#ifndef PADDLE_H
#define PADDLE_H

#include "constants.h"
#include "entity.h"

class Paddle : public MovingEntity {
	static sf::Texture texture;

	void process_player_input();

public:
	Paddle(float x, float y);

	void update() override;
	void draw(sf::RenderWindow& window) override;

	void move_up() noexcept override;
	void move_down() noexcept override;
	void move_left() noexcept override;
	void move_right() noexcept override;
};

#endif