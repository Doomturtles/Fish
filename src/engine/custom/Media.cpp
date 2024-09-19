#include "Media.h"
SDL_Texture* Media::Image(const char* s) {
	return instance().GetImage(s);
}
SDL_Texture* Media::GetImage(const char* s) {
	string image = s;
	return _images->at(image);
}
void Media::LoadImage(const char* filename, const char* imagename, SDL_Renderer* renderer) {
	SDL_Surface* textureSurface = SDL_LoadBMP(filename);
	if (textureSurface == NULL) {
		throw new std::exception();
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
	instance()._images->insert(make_pair(imagename, texture));
}
void Media::InitializeImages(SDL_Renderer* renderer) {
	instance()._images->clear();
	LoadImage("../src/FishGame/Resources/Fish.bmp", "Fish", renderer);
}