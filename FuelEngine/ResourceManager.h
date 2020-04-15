#pragma once
#include "Singleton.h"

namespace fuel
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		static void Init(const std::string& data) { GetInstance().IInit(data); }
		static std::shared_ptr<Texture2D> LoadTexture(const std::string& file) { return GetInstance().ILoadTexture(file); }
		static std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) { return GetInstance().ILoadFont(file, size); }
		static bool DoesFileExist(const std::string& fullPath) { return GetInstance().IDoesFileExist(fullPath); }
	private:
		void IInit(const std::string& data);
		std::shared_ptr<Texture2D> ILoadTexture(const std::string& file) const;
		std::shared_ptr<Font> ILoadFont(const std::string& file, unsigned int size) const;
		bool IDoesFileExist(const std::string& fullPath);
		
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
	};
}
