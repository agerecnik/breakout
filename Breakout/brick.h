#ifndef BRICK_H
#define BRICK_H

#include "constants.h"
#include "entity.h"

class Brick : public Entity {
	static sf::Texture texture;
	int strength{ Constants::brick_strength };

public:
	Brick(float x, float y);

	void update() override;
	void draw(sf::RenderWindow& window) override;

	void set_strength(int) noexcept;
	void weaken() noexcept;
	bool is_too_weak() const noexcept;
};

#endif