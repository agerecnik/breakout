#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
protected:
	sf::Sprite sprite;
	bool destroyed{ false };

public:
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	sf::FloatRect get_bounding_box() const noexcept;
	sf::Vector2f get_center() const noexcept;

	float x() const noexcept;
	float y() const noexcept;

	float left() const noexcept;
	float right() const noexcept;
	float top() const noexcept;
	float bottom() const noexcept;

	void destroy() noexcept;
	bool is_destroyed() const noexcept;

	virtual ~Entity() {}
};

class MovingEntity : public Entity {
protected:
	sf::Vector2f velocity;

public:
	virtual void move_up() noexcept = 0;
	virtual void move_down() noexcept = 0;
	virtual void move_left() noexcept = 0;
	virtual void move_right() noexcept = 0;
};

#endif
