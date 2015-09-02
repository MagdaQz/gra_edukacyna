//struct SpriteConfigData 
#pragma once 

#ifndef _SpriteConfig_h
#define _SpriteConfig_h

#include <string>
#include <map>
#include <memory>
#include "Types.h"


using std::shared_ptr;

struct SpriteConfigData {
  explicit SpriteConfigData(DL::DisplayLayer layer, size_t frame_count, 
                            double frame_duration, double left, double bottom, 
                            double width, double height, bool loop) :
      layer(layer), frame_count(frame_count), frame_duration_time(frame_duration), 
      left(left), bottom(bottom), width(width), height(height), loop(loop) {
  }
 
  DL::DisplayLayer layer;       // warstwa, na którym bêdzie rysowany sprite. Im bli¿ej 0, tym bli¿ej obserwatora
  size_t frame_count; // liczba klatek w animacji
  double frame_duration_time;   // czas trwania klatki
  double left;  // po³o¿enie w poziomie pierwszej klatki animacji w obrazku (w px)
  double bottom;// po³o¿enie w pionie pierwszej klatki animacji w obrazku (w px)
  double width; // szerokoœæ klatki w pikselach
  double height;// wysokoœæ klatki w pikselach
  bool loop;    // czy animacja ma byæ zapêtlona?
};


class SpriteConfig {
public:
  explicit SpriteConfig();
  SpriteConfigData Get(const std::string& name) const;
  bool Contains(const std::string& name) const;
 
private:
  std::map<std::string, SpriteConfigData> m_data;
  void Insert(const std::string& name, const SpriteConfigData& data);
};
typedef shared_ptr<SpriteConfig> SpriteConfigPtr;


#endif