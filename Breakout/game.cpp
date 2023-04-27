#include <algorithm>

#include "game.h"
#include "interactions.h"

// Remove all destroyed entities
void EntityManager::refresh() {
	for (auto& [type, entities] : grouped_entities) {
		entities.erase(remove_if(begin(entities), end(entities),
			[](const auto& e) { return e->is_destroyed(); }
		),
			end(entities));
	}

	all_entities.erase(remove_if(begin(all_entities), end(all_entities),
		[](const auto& e) { return e->is_destroyed(); }
	),
		end(all_entities));
}

// Destroy all entities
void EntityManager::clear() {
	grouped_entities.clear();
	all_entities.clear();
}

// Update all entities
void EntityManager::update() {
	for (auto& e : all_entities) {
		e->update();
	}
}

// Draw all entities
void EntityManager::draw(sf::RenderWindow& window) {
	for (auto& e : all_entities) {
		e->draw(window);
	}
}

Game::Game() {
	window.setFramerateLimit(60);
	font.loadFromFile("resources/verdana.ttf");
	
	text_state.setFont(font);
	text_state.setPosition(Constants::window_width / 2.0f - 100.0f, Constants::window_height / 2.0f - 100.0f);
	text_state.setCharacterSize(35);
	text_state.setFillColor(sf::Color::White);
	text_state.setString("Paused");

	text_lives.setFont(font);
	text_lives.setPosition(Constants::window_width / 2.0f - 65.0f, Constants::window_height / 2.0f - 50.0f);
	text_lives.setCharacterSize(35);
	text_lives.setFillColor(sf::Color::White);
	text_lives.setString("Lives: " + std::to_string(lives));
}

// Initialize the game
void Game::initialize() {
	window.setFramerateLimit(60);

	lives = Constants::player_lives;
	text_lives.setString("Lives: " + std::to_string(lives));
	state = GameState::paused;

	// Destroy all the entities and re-create them
	manager.clear();

	manager.create<Background>(0.0f, 0.0f);
	manager.create<Ball>(Constants::window_width / 2.0f, Constants::window_height / 2.0f);
	manager.create<Paddle>(Constants::window_width / 2.0f, Constants::window_height - Constants::paddle_height);

	for (int i = 0; i < Constants::brick_columns; ++i) {
		for (int j = 0; j < Constants::brick_rows; ++j) {
			float x = Constants::brick_offset + (i + 1) * Constants::brick_width;
			float y = (j + 1) * Constants::brick_height;

			manager.create<Brick>(x, y);
		}
	}

	manager.update();
}

// Start the game
void Game::run() {
	initialize();

	bool pause_key_active{ false };

	while (window.isOpen()) {
		window.clear(sf::Color::Black);

		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			break;
		}

		// When 'P' is pressed the game is paused/unpaused
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
			// If it was not pressed on the last iteration, toggle the status
			// To prevent repeated use, we ignore it if it was pressed on the previous iteration
			if (!pause_key_active) {
				if (state == GameState::paused) {
					state = GameState::running;
				}
				else {
					state = GameState::paused;
				}
			}
			pause_key_active = true;
		}
		else {
			pause_key_active = false;
		}

		// If "R" is pressed reset the game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
			initialize();
		}

		// In the paused state, the entities are not updated, only redrawn
		if (state == GameState::paused) {
			manager.draw(window);
		}

		if (state != GameState::running) {
			switch (state) {
				case GameState::paused:
					text_state.setString("   Paused  ");
					break;
				case GameState::game_over:
					text_state.setString(" Game Over ");
					break;
				case GameState::player_wins:
					text_state.setString("Player Wins");
					break;
				default:
					break;
			}

			window.draw(text_state);
			window.draw(text_lives);
		}
		else {
			if (manager.get_all<Ball>().empty()) {
				manager.create<Ball>(Constants::window_width / 2.0f, Constants::window_height / 2.0f);
				--lives;
				state = GameState::paused;
			}

			if (manager.get_all<Brick>().empty()) {
				state = GameState::player_wins;
			}

			if (lives <= 0) {
				state = GameState::game_over;
			}

			text_lives.setString("Lives: " + std::to_string(lives));

			// Calculate the updated graphics
			manager.update();

			// Check for and handle collisions between the ball and bricks
			manager.apply_all<Ball>([this](auto& the_ball) {
				manager.apply_all<Brick>([&the_ball](auto& the_brick) {
					handle_collision(the_ball, the_brick);
					});
				});

			// Check for and handle collision between the paddle and ball
			manager.apply_all<Ball>([this](auto& the_ball) {
				manager.apply_all<Paddle>([&the_ball](auto& the_paddle) {
					handle_collision(the_ball, the_paddle);
					});
				});

			manager.refresh();
			manager.draw(window);
		}

		window.display();
	}
}
