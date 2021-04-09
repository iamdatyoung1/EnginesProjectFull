#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H
#include <memory>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "../Core/Debug.h"
#include <glew.h>
//we need struct to keep info
struct Texture
{
	//create texture
	GLuint textureID = 0;
	float width = 0.0f;
	float height = 0.0f;
	std::string textureName = "";
};

class TextureHandler
{
public:
	TextureHandler(const TextureHandler&) = delete;
	TextureHandler(TextureHandler&&) = delete;
	TextureHandler& operator = (const TextureHandler&) = delete;
	TextureHandler& operator = (TextureHandler&&) = delete;
	static TextureHandler* GetInstance();
	void OnDestroy();
	//create texture and name we then need the file path to load it
	void CreateTexture(const std::string& textureName_,
		const std::string& textureFilePath_);

	const GLuint GetTexture(const std::string& textureName_);
	const Texture* GetTextureData(const std::string textureName_);

private:
	TextureHandler();
	~TextureHandler();
	//we need to delete cause they are pointers
	static std::unique_ptr<TextureHandler> textureInstance;
	friend std::default_delete<TextureHandler>;
	static std::vector<Texture*> textures;
};
#endif
