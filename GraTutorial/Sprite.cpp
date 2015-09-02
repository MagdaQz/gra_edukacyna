#include "Engine.h"
#include "Sprite.h"
 
using namespace std;
 
void Sprite::SetCurrentFrame(size_t frame_num) {
  m_current_frame = frame_num;
  m_current_frame_duration = 0.0;  // pocz�tek tej klatki
}
 
void Sprite::Update(double dt) {
  // klatka jest wy�wietlana o dt d�u�ej
  m_current_frame_duration += dt;
 
  // przejd� do nast�pnej klatki je�eli trzeba
  if (m_current_frame_duration >= m_data.frame_duration_time) {
    m_current_frame++;
    m_current_frame_duration -= m_data.frame_duration_time;
  }
 
  // sprawd� czy nast�pi� koniec animacji 
  // - przejd� do klatki 0. lub ostatniej
  if (m_current_frame >= m_data.frame_count) {
    if (m_data.loop) {
      m_current_frame = 0;
    } else {
      m_current_frame = m_data.frame_count - 1;
    }
  }
}
 
void Sprite::DrawCurrentFrame(double x, double y, 
                              double width, double height) {
  Engine::Get().FRenderer()->DrawSprite(
                    m_data.left + m_data.width * m_current_frame, 
                    m_data.bottom,
                    m_data.width, m_data.height, 
                    x, y, 
                    width, height, 
                    m_data.layer);
}