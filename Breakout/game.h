#ifndef GAME_H
#define GAME_H

#include <memory>
#include <typeinfo>
#include <vector>

#include "background.h"
#include "ball.h"
#include "brick.h"
#include "constants.h"
#include "entity.h"
#include "paddle.h"

using entity_vector = std::vector<std::shared_ptr<Entity>>;

// Entity_manager manages the paddle, ball, bricks and background
class EntityManager {
	entity_vector all_entities;
	std::map<size_t, entity_vector> grouped_entities;

public:
	// Create an entity
	template <typename T, typename... Args>
	void create(Args&&... args) {
		static_assert(std::is_base_of<Entity, T>::value,
			R"("T" type parameter in create() must be derived from "entity")");

		auto hash = typeid(T).hash_code();
		auto ptr{ std::make_shared<T>(std::forward<Args>(args)...) };
		all_entities.emplace_back(ptr);
		grouped_entities[hash].emplace_back(ptr);
	}

	// Remove all destroyed entities
	void refresh();

	// Destroy all entities
	void clear();

	// Retrieve all the objects of a given type
	template <typename T>
	auto& get_all() {
		return grouped_entities[typeid(T).hash_code()];
	}

	// Apply a function to all entities of a given type (e.g., to check for and handle collisions)
	template <typename T, typename Func>
	void apply_all(const Func& func) {
		auto& entity_group{ get_all<T>() };
		for (auto ptr : entity_group)
			func(*std::dynamic_pointer_cast<T>(ptr));
	}

	// Update all entities
	void update();

	// Draw all entities
	void draw(sf::RenderWindow& window);
};

class Game {
	enum class GameState { paused, running, game_over, player_wins };

	sf::RenderWindow window{ {Constants::window_width, Constants::window_height}, "Breakout" };
	EntityManager manager;
	sf::Font font;
	sf::Text text_state, text_lives;
	int lives{ Constants::player_lives };
	GameState state{ GameState::running };

public:
	Game();

	// Initialize the game
	void initialize();

	// Start the game
	void run();
};

#endif // GAME_H
