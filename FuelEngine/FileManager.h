#pragma once
#include "Singleton.h"

namespace fuel
{
	class Scene;
	class FileManager : public fuel::Singleton<FileManager>
	{
	public:
		FileManager(const FileManager& other) = delete;
		FileManager(FileManager&& other) noexcept = delete;
		FileManager& operator=(const FileManager& other) = delete;
		FileManager& operator=(FileManager&& other) noexcept = delete;
		FileManager();
		virtual ~FileManager();

		static void SaveScene(Scene* scene, const std::string& fileName){ GetInstance().ISaveScene(scene, fileName); }
		static void LoadScene(Scene* scene, const std::string& fileName) { GetInstance().ILoadScene(scene, fileName); }
		static void ReadString(std::ifstream& binStream, std::string& stringData) { GetInstance().IReadString(binStream, stringData); }
		static void WriteString(std::ofstream& binStream, const std::string& stringData) { GetInstance().IWriteString(binStream, stringData); }
		
	private:
		void Initialize();

		void ISaveScene(Scene* scene, const std::string& fileName);
		void ILoadScene(Scene* scene, const std::string& fileName);
		void IReadString(std::ifstream& binStream, std::string& stringData);
		void IWriteString(std::ofstream& binStream, const std::string& stringData);
	};
}
