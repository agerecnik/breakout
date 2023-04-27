#include "background.h"

sf::Texture Background::texture;

Background::Background(float x, float y) : Entity() {
	texture.loadFromFile("resources/background.png");
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void Background::update() {}

void Background::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}