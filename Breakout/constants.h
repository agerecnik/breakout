#ifndef CONSTANTS_H
#define CONSTANTS_H

struct Constants {
	static constexpr int window_width{ 1111 };
	static constexpr int window_height{ 580 };
	static constexpr float ball_speed{ 6.0f };
	static constexpr float paddle_height{ 20.0f };
	static constexpr float paddle_speed{ 10.0f };
	static constexpr float brick_width{ 42.0f };
	static constexpr float brick_height{ 20.0f };
	static constexpr float brick_offset{ brick_width / 2.0f };
	static constexpr int brick_columns{ 24 };
	static constexpr int brick_rows{ 4 };
	static constexpr int brick_strength{ 3 };
	static constexpr int player_lives{ 3 };
};

#endif