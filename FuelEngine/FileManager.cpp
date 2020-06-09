#include "FuelEnginePCH.h"
#include "FileManager.h"

#include "Scene.h"
#include "GameObject.h"
#include "EngineComponents.h"

fuel::FileManager::FileManager()
{
	Initialize();
}

fuel::FileManager::~FileManager()
{
}

void fuel::FileManager::Initialize()
{
}

void fuel::FileManager::ISaveScene(Scene* scene, const std::string& fileName)
{
	std::ofstream binStream;
	const std::string file{ "../Data/LevelData/Level_" + fileName + ".fuel" };
	binStream.open(file, std::ios::out | std::ios::binary);
	
	if (binStream.is_open())
	{
		// Write total number of SceneObjects to binary file
		const unsigned int numGameObjects{ scene->GetNumGameObjects() };
		binStream.write((const char*)&numGameObjects, sizeof(unsigned int));

		// Write all SceneObjects to binary file
		std::vector<std::shared_ptr<SceneObject>> sceneObjects{ scene->GetSceneObjects() };
		for (unsigned int i{ 0 }; i < numGameObjects; ++i)
		{
			// Check which type SceneObject is and write type to binary file
			ObjectType objectType{ sceneObjects[i]->GetObjectType() };
			binStream.write((const char*)&objectType, sizeof(ObjectType));

			if (objectType == GAMEOBJECT)
			{
				// Write GameObject name and tag to binary file
				GameObject* pGameObject{ reinterpret_cast<GameObject*>(sceneObjects[i].get()) };
				IWriteString(binStream, pGameObject->GetName());
				IWriteString(binStream, pGameObject->GetTag());

				// Write number of components of GameObject to binary file
				const GameObjectData gameObjectData{ pGameObject->GetGameObjectData() };
				binStream.write((const char*)&gameObjectData.numComponents, sizeof(unsigned int));

				// Write all components of GameObject to binary file
				for (BaseComponent* pComponent : pGameObject->GetComponents())
				{
					// Write componentType to binary file
					ComponentType compType{ pComponent->GetCompType() };
					binStream.write((const char*)&compType, sizeof(ComponentType));

					// Write ComponentData to binary file
					pComponent->Safe(binStream);
				}
			}
			else if (sceneObjects[i]->GetObjectType() == BUTTON)
			{
				// Write Button name and tag to binary file
				Button* pButton{ reinterpret_cast<Button*>(sceneObjects[i].get()) };
				IWriteString(binStream, pButton->GetName());
				IWriteString(binStream, pButton->GetTag());

				// Write Button data to binary file
				pButton->Safe(binStream);
			}
		}
	}
	else
	{
		Logger::LogError("No file or directory \"../Data/LevelData/Level_" + fileName + ".fuel" + "\" has been found!");
	}
}

void fuel::FileManager::ILoadScene(Scene* scene, const std::string& fileName)
{
	std::ifstream binStream;
	const std::string file{ "../Data/LevelData/Level_" + fileName + ".fuel" };
	binStream.open(file, std::ios::in | std::ios::binary);

	if (binStream.is_open())
	{
		// Read total number of SceneObjects from binary file
		unsigned int numGameObjects{};
		binStream.read((char*)&numGameObjects, sizeof(unsigned int));

		// Read all SceneObjects from binary file
		for (unsigned int i{ 0 }; i < numGameObjects; ++i)
		{
			// Read type from binary file
			ObjectType objectType{};
			binStream.read((char*)&objectType, sizeof(ObjectType));

			if (objectType == GAMEOBJECT)
			{
				// Write GameObject name and tag to binary file
				std::shared_ptr<GameObject> pGameObject{ std::make_shared<GameObject>() };
				scene->AddToScene(pGameObject);

				// Read GameObject Name from binary file
				std::string stringData{};
				IReadString(binStream, stringData);
				pGameObject->SetName(stringData);
				
				// Read GameObject Tag from binary file
				IReadString(binStream, stringData);
				pGameObject->SetTag(stringData);

				// Read number of components of GameObject to binary file
				unsigned int numComps{};
				binStream.read((char*)&numComps, sizeof(unsigned int));

				for (unsigned int compIdx{ 0 }; compIdx < numComps; ++compIdx)
				{
					// Write componentType to binary file
					ComponentType compType{};
					binStream.read((char*)&compType, sizeof(ComponentType));

					switch (compType)
					{
					case ComponentType::FPS:
						{
							FPSComponent* pFPSComp = pGameObject->AddComponent<FPSComponent>();
							pFPSComp->Load(binStream);
							break;
						}
					case ComponentType::TRANSFORM:
					{
						Transform* pTrans = pGameObject->AddComponent<Transform>();
						pTrans->Load(binStream);
						break;
					}
					case ComponentType::RIGIDBODY:
						{
							RigidBody2D* pRigidBody = pGameObject->AddComponent<RigidBody2D>();
							pRigidBody->Load(binStream);
							break;
						}
					case ComponentType::BOXCOLLIDER:
						{
							BoxCollider* pBoxCol = pGameObject->AddComponent<BoxCollider>();
							pBoxCol->Load(binStream);
							break;
						}
					case ComponentType::SPHERECOLLIDER:
						{
							SphereCollider* pSphereCol = pGameObject->AddComponent<SphereCollider>();
							pSphereCol->Load(binStream);
							break;
						}
					case ComponentType::TEXTRENDERER:
						{
							TextComponent* pTextComp = pGameObject->AddComponent<TextComponent>();
							pTextComp->Load(binStream);
							break;
						}
					case ComponentType::RENDERER:
						{
							RenderComponent* pRenderComp = pGameObject->AddComponent<RenderComponent>();
							pRenderComp->Load(binStream);
							break;
						}
					case ComponentType::SPRITERENDERER:
						{
							SpriteComponent* pSpriteComp = pGameObject->AddComponent<SpriteComponent>();
							pSpriteComp->Load(binStream);
							break;
						}
					case ComponentType::CONTROLLER:
						{
							PlayerController* pController = pGameObject->AddComponent<PlayerController>();
							pController->Load(binStream);
							break;
						}
					case ComponentType::VIBRATION:
						{
							VibrationComponent* pVibrationComp = pGameObject->AddComponent<VibrationComponent>();
							pVibrationComp->Load(binStream);
							break;
						}
					}
				}
			}
			else if (objectType == BUTTON)
			{
				// Write Button name and tag to binary file
				std::shared_ptr<Button> pButton{ std::make_shared<Button>() };
				scene->AddToScene(pButton);
				scene->AddButton(pButton.get());
				
				std::string stringData{};
				IReadString(binStream, stringData);
				pButton->SetName(stringData);
				IReadString(binStream, stringData);
				pButton->SetTag(stringData);

				// Write Button data to binary file
				pButton->Load(binStream);
			}
		}
	}
	else
	{
	Logger::LogError("No file or directory \"../Data/LevelData/Level_" + fileName + ".fuel" + "\" has been found!");
	}
}

void fuel::FileManager::IReadString(std::ifstream& binStream, std::string& stringData)
{
	stringData.clear();
	
	unsigned int numChars{};
	binStream.read((char*)&numChars, sizeof(unsigned int));

	char charData{};
	for (unsigned int i{ 0 }; i < numChars; ++i)
	{
		binStream.read((char*)&charData, sizeof(char));
		stringData.push_back(charData);
	}
}

void fuel::FileManager::IWriteString(std::ofstream& binStream, const std::string& stringData)
{
	unsigned int numChars{ stringData.size() };
	binStream.write((const char*)&numChars, sizeof(unsigned int));

	for (unsigned int i{ 0 }; i < numChars; ++i)
	{
		binStream.write((const char*)&stringData[i], sizeof(char));
	}
}
