#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "constants.h"
#include "entity.h"

class Background : public Entity {
	static sf::Texture texture;

public:
	Background(float x, float y);

	void update() override;
	void draw(sf::RenderWindow& window) override;
};

#endif