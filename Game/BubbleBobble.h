#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Scene.h"

class BubbleBobble : public Game
{
public:
	enum GameMode
	{
		SOLO,
		COOP,
		VS
	};
	
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
	void InitializeButtons();

	void InitializeLevelOne();
	void InitializeLevelTwo();
	void InitializeLevelThree();

	void SwitchToScene(const std::string& sceneName);
	
	void UpdateMainMenu();
	void UpdateLevelOne();
	void UpdateLevelTwo();
	void UpdateLevelThree();

	void UpdateEnemies(std::vector<std::shared_ptr<fuel::GameObject>> enemies);
	
	fuel::Scene& m_MainMenuScene;
	fuel::Scene& m_LevelOneScene;
	fuel::Scene& m_LevelTwoScene;
	fuel::Scene& m_LevelThreeScene;
	fuel::GameObject* m_pPlayer1;
	fuel::GameObject* m_pPlayer2;

	std::vector<std::shared_ptr<fuel::GameObject>> m_EnemiesLevelOne;
	std::vector<std::shared_ptr<fuel::GameObject>> m_EnemiesLevelTwo;
	std::vector<std::shared_ptr<fuel::GameObject>> m_EnemiesLevelThree;
	
	GameMode m_GameMode;
	float m_CurrentTimer{ 0.f };
};