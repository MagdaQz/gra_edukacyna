#include "SpriteConfig.h"
#include "Types.h"

using namespace std;


SpriteConfig::SpriteConfig() {
 
	
	Insert("player_right", 
           SpriteConfigData(
               DL::Player, 4, 0.2, 14, 82, 80, 46, true));
	Insert("player_left",  
           SpriteConfigData(
               DL::Player, 4, 0.2, 14, 241, 80, 46, true));
	Insert("player_stop",  
           SpriteConfigData(
               DL::Player, 1, 0.2, 14, 403, 80, 46, true));
	Insert("player_down",  
           SpriteConfigData(
               DL::Player, 4, 0.2, 14, 327, 80, 46, true));
	Insert("player_up",  
           SpriteConfigData(
               DL::Player, 4, 0.2, 14, 165, 80, 46, true));
	
}

 
SpriteConfigData SpriteConfig::Get(const std::string& name) const {
  if (Contains(name))
    return m_data.find(name)->second;
  throw("Config not found: "+name);
}
 
bool SpriteConfig::Contains(const std::string& name) const {
  return (m_data.find(name) != m_data.end());
}
 
void SpriteConfig::Insert(const std::string& name, const SpriteConfigData& data) {
  m_data.insert(std::make_pair(name, data));
}