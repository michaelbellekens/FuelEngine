#pragma once

struct _TTF_Font;
namespace fuel
{
	/**
	 * Simple RAII wrapper for an _TTF_Font
	 */
	class Font
	{
	public:
		_TTF_Font* GetFont() const;
		explicit Font(const std::string& dataPath, const std::string& fontName, unsigned int size);
		~Font();

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;

		const std::string& GetName() const;
	private:
		_TTF_Font* m_Font;
		std::string m_FontName;
		unsigned int m_Size;
	};
}
