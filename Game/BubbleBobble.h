#pragma once
#include "Game.h"
#include "Scene.h"

class BubbleBobble : public Game
{
public:
	BubbleBobble();
	virtual ~BubbleBobble();

	BubbleBobble(const BubbleBobble& other) = delete;
	BubbleBobble(BubbleBobble&& other) = delete;
	BubbleBobble& operator=(const BubbleBobble& other) = delete;
	BubbleBobble& operator=(BubbleBobble&& other) = delete;

	void Initialize() override;

	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	
private:
	void LoadScenes();

	fuel::Scene& m_MainMenuScene;
	fuel::Scene& m_LevelOneScene;
	fuel::Scene& m_LevelTwoScene;
	fuel::Scene& m_LevelThreeScene;
};