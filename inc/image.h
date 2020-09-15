#pragma once

#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Image {

public:
	Image();
	Image(const string&, const string&, const int&, const int&, const int&, const int&);
	Image(const string&, const string&, const SDL_Rect&);
	Image(const string&, const string&);

	~Image();

	bool Load();
	void Print();

	void Draw(SDL_Surface*);
	void Drawable(bool drawable);
	bool Drawable() const;

//	void MoveTo(const int& x, const int& y);
//	pair<int, int> MoveRelative(const int& x, const int& y);
//
//	pair<int, int> ScaleDown(const float& percentage);
//	pair<int, int> ScaleUp(const float& percentage);
//	void ScaleDown(const int& x, const int& y);
//	void ScaleUp(const int& x, const int& y);
//	void ScaleTo(const int& x, const int& y);
//
//	void RotateClockwise(const float& angle);
//	void RotateCounterClockwise(const float& angle);

private:

	SDL_Surface* m_surface = NULL;
	SDL_Rect m_dimensions = { 0, 0, 0, 0 };

	string m_path = "";
	string m_name = "";

	bool m_drawable = false;

};

