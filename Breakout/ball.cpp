#include "ball.h"

sf::Texture Ball::texture;

Ball::Ball(float x, float y) : MovingEntity() {
	texture.loadFromFile("resources/ball.png");
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	velocity = { Constants::ball_speed, Constants::ball_speed };
	sprite.setOrigin(get_center());
}

void Ball::update() {
	sprite.move(velocity);

	if (x() < 0) {
		velocity.x = -velocity.x;
	}

	if (x() > Constants::window_width) {
		velocity.x = -velocity.x;
	}

	if (y() < 0) {
		velocity.y = -velocity.y;
	}

	if (y() > Constants::window_height) {
		destroy();
	}
}

void Ball::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Ball::move_up() noexcept {
	velocity.y = -Constants::ball_speed;
}

void Ball::move_down() noexcept {
	velocity.y = Constants::ball_speed;
}

void Ball::move_left() noexcept {
	velocity.x = -Constants::ball_speed;
}

void Ball::move_right() noexcept {
	velocity.x = Constants::ball_speed;
}