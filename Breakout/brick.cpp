#include "brick.h"

sf::Texture Brick::texture;

const sf::Color brick_color_hit1{ 0, 255, 0, 80 };
const sf::Color brick_color_hit2{ 0, 255, 0, 170 };
const sf::Color brick_color_hit3{ 0, 255, 0, 255 };

Brick::Brick(float x, float y) : Entity() {
	texture.loadFromFile("resources/brick.png");
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	sprite.setOrigin(get_center());
}

void Brick::update() {
	if (strength == 1) {
		sprite.setColor(brick_color_hit1);
	}
	else if (strength == 2) {
		sprite.setColor(brick_color_hit2);
	}
	else if (strength == 3) {
		sprite.setColor(brick_color_hit3);
	}
}

void Brick::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Brick::set_strength(int s) noexcept {
	strength = s;
}

void Brick::weaken() noexcept {
	--strength;
}

bool Brick::is_too_weak() const noexcept {
	return strength <= 0;
}