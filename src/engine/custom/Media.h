#pragma once
#include "SDL.h"
#include <map>
#include <string>
using namespace std;
class Media
{
public:
	static SDL_Texture* Image(const char* s);
	SDL_Texture* GetImage(const char* s);
	static void InitializeImages(SDL_Renderer* renderer);
	static Media& instance() {
		static Media INSTANCE;
		return INSTANCE;
	}
private:
	Media() {
		_images = new map<string, SDL_Texture*>();
	}
	static void LoadImage(const char* filename, const char* imagename, SDL_Renderer* renderer);
	map<string, SDL_Texture*>* _images;
};

