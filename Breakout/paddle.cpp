#include "paddle.h"

sf::Texture Paddle::texture;

Paddle::Paddle(float x, float y) : MovingEntity() {
	texture.loadFromFile("resources/paddle.png");
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	velocity = { 0.0f, 0.0f };
	sprite.setOrigin(get_center());
}

void Paddle::update() {
	process_player_input();
	sprite.move(velocity);
}

void Paddle::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Paddle::process_player_input() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		if (left() >= 0) {
			velocity.x = -Constants::paddle_speed;
		}
		else {
			velocity.x = 0;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		if (right() <= Constants::window_width) {
			velocity.x = Constants::paddle_speed;
		}
		else {
			velocity.x = 0;
		}
	}
	else {
		velocity.x = 0;
	}
}

void Paddle::move_up() noexcept {}

void Paddle::move_down() noexcept {}

void Paddle::move_left() noexcept {
	velocity.x = -Constants::paddle_speed;
}

void Paddle::move_right() noexcept {
	velocity.x = Constants::paddle_speed;
}