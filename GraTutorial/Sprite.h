#ifndef _Sprite_h
#define _Sprite_h

#include "SpriteConfig.h"

class Sprite
{
private:
	SpriteConfigData m_data;
	size_t m_current_frame;
	double m_current_frame_duration;
public:
	explicit Sprite(const SpriteConfigData& data) :
  m_data(data), m_current_frame(0), m_current_frame_duration(0.0) { }

	void SetCurrentFrame(size_t frame_num);

	void Update(double dt);

	void DrawCurrentFrame(double x, double y, 
                              double width, double height);

};

typedef shared_ptr<Sprite> SpritePtr;

#endif
