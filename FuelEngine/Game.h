#pragma once

class Game
{
public:
	Game() = default;
	virtual ~Game() = default;

	Game(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game& operator=(Game&& other) = delete;

	virtual void Initialize() = 0;

	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Draw() = 0;
};