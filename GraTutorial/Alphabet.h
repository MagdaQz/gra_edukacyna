#ifndef __ALPHA_H__
#define __ALPHA_H__

#include <memory> 
#include "Sprite.h"
#include "Types.h"
#include <string>
#include "Sprite.h"
#include <map>
#include "SpriteConfig.h"
#include <iostream>

using namespace std;

/*struct LetterData
{
	explicit LetterData(DL::DisplayLayer layer, size_t frame_count, 
                            double frame_duration, double left, double bottom, 
                            double width, double height, bool loop) :
      layer(layer), frame_count(frame_count), frame_duration_time(frame_duration), 
		  left(left), bottom(bottom), width(width), height(height), loop(loop) {}
 

   DL::DisplayLayer layer;       // warstwa, na którym bêdzie rysowany sprite. Im bli¿ej 0, tym bli¿ej obserwatora
  size_t frame_count; // liczba klatek w animacji
  double frame_duration_time;   // czas trwania klatki
  double left;  // po³o¿enie w poziomie pierwszej klatki animacji w obrazku (w px)
  double bottom;// po³o¿enie w pionie pierwszej klatki animacji w obrazku (w px)
  double width; // szerokoœæ klatki w pikselach
  double height;// wysokoœæ klatki w pikselach
  bool loop;
};*/


class Alphabet 
{
public:
	explicit Alphabet();
  SpriteConfigData Get(const std::string& name) const;
  bool Contains(const std::string& name) const;
  void Insert(const std::string& name, const SpriteConfigData& data);
 
private:
  std::map<std::string, SpriteConfigData> m_data;
};


typedef shared_ptr<Alphabet> AlphabetPtr;







#endif