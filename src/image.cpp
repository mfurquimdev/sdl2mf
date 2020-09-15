#include "image.h"

#include <cstdio>

Image::Image()
{
	m_surface = NULL;
	m_dimensions = { 0, 0, 0, 0 };
	m_path = "";
	m_name = "";
	m_drawable = false;
}

Image::Image(const string& path, const string& name, const int& x, const int& y, const int& w, const int& h)
{
	m_surface = NULL;
	m_dimensions = { x, y, w, h };
	m_path = path;
	m_name = name;
	m_drawable = false;
}

Image::Image(const string& path, const string& name, const SDL_Rect& dimensions)
{
	m_surface = NULL;
	m_dimensions = dimensions;
	m_path = path;
	m_name = name;
	m_drawable = false;
}

Image::Image(const string& path, const string& name)
{
	m_surface = NULL;
	m_dimensions = { 0, 0, 0, 0 };
	m_path = path;
	m_name = name;
	m_drawable = false;
}

Image::~Image()
{
	if (m_surface != NULL) {
		SDL_FreeSurface( m_surface );
		m_surface = NULL;
	}
}

bool
Image::Load()
{
	bool assetLoaded = true;

	m_surface = SDL_LoadBMP( string(m_path + "/" + m_name).c_str() );
	if (m_surface == NULL)
	{
		printf( "Unable to load image %s at path %s! SDL Error: %s\n", m_name.c_str(), m_path.c_str(), SDL_GetError() );
		assetLoaded = false;
	}
	else
	{
		m_dimensions.w = m_surface->w;
		m_dimensions.h = m_surface->h;
	}

	return assetLoaded;
}

void
Image::Drawable(bool drawable)
{
	m_drawable = drawable;
}

bool
Image::Drawable() const
{
	return m_drawable;
}

void
Image::Draw(SDL_Surface* screenSurface)
{
	if (m_drawable) {
		SDL_BlitSurface( m_surface, NULL, screenSurface, &m_dimensions );
	}
}

void
Image::Print()
{
	fprintf( stderr, "%s/%s { %d, %d, %d, %d } %d\n", m_path.c_str(), m_name.c_str(), m_dimensions.x, m_dimensions.y, m_dimensions.w, m_dimensions.h, m_drawable ); 
}
