#ifndef _renderer_h
#define _renderer_h

#include <memory>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Types.h"
#include "Aabb.h"

using std::shared_ptr;

class Renderer
{


public:
    Renderer() :
        m_tile_width(.1), m_tile_height(.1) {
    }

    double GetTileWidth() const { return m_tile_width; }
    double GetTileHeight() const { return m_tile_height; }
	size_t GetHorizontalTilesOnScreenCount() const { return 1.0 / m_tile_width  + 0.5; }
    size_t GetVerticalTilesOnScreenCount()   const { return 1.0 / m_tile_height + 0.5; }

    void SetTileSize(double width, double height);

    void LoadTexture(const std::string & filename);
    void DrawSprite(double tex_x, double tex_y, double tex_w, double tex_h, double pos_x, double pos_y,
                    double width, double height, DL::DisplayLayer layer);

	void DrawAabb(const Aabb& box, double r, double g, double b, double a) const;
	void DrawQuad(double min_x, double min_y,
                  double max_x, double max_y,
                  double r, double g, double b, double a) const;
    void SetProjection(size_t width, size_t height);
    void ResetProjection();

private:
    GLuint m_texture;
    double m_tile_width;
    double m_tile_height;
};

typedef shared_ptr<Renderer> RendererPtr;

#endif