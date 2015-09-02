#include "Alphabet.h"


Alphabet::Alphabet()
{
	Insert("A", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 0, 406 +2*32, 32, 32, true));
	Insert("¥", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 32, 406 +  2*32, 32, 32, true));
	Insert("B", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 2*32, 406 + 2*32, 32, 32, true));
	Insert("C", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 3*32, 406 + 2*32, 32, 32, true));
	Insert("Æ", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 4*32, 406 + 2*32, 32, 32, true));
	Insert("D", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 5*32, 406 + 2*32, 32, 32, true));
	Insert("E", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 6*32, 406 + 2*32, 32, 32, true));
	Insert("Ê", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 7*32, 406 + 2*32, 32, 32, true));
	Insert("F", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 0, 3*32, 32, 32, true));
	Insert("G", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 32, 406 + 3*32, 32, 32, true));
	Insert("H", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 2*32, 406 + 3*32, 32, 32, true));
	Insert("I", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 3*32, 406 + 3*32, 32, 32, true));
	Insert("J", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 4*32, 406 + 3*32, 32, 32, true));
	Insert("K", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 5*32, 406 + 3*32, 32, 32, true));
	Insert("L", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 6*32, 406 + 3*32, 32, 32, true));
	Insert("£", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 7*32, 406 + 3*32, 32, 32, true));
	Insert("M", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 0, 406 + 4*32, 32, 32, true));
	Insert("N", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 32, 406 + 4*32, 32, 32, true));
	Insert("Ñ", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 2*32, 406 +  4*32, 32, 32, true));
	Insert("O", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 3*32, 406+4*32, 32, 32, true));
	Insert("Ó", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 4*32, 406 + 4*32, 32, 32, true));
	Insert("P", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 5*32, 406 + 4*32, 32, 32, true));
	Insert("R", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 6*32, 406 + 4*32, 32, 32, true));
	Insert("S", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 7*32, 406 + 4*32, 32, 32, true));
	Insert("Œ", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 0, 406 + 5*32, 32, 32, true));
	Insert("T", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 32, 406 + 5*32, 32, 32, true));
	Insert("U", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 2*32, 406 + 5*32, 32, 32, true));
	Insert("W", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 3*32, 406 + 5*32, 32, 32, true));
	Insert("Y", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 4*32, 406 + 5*32, 32, 32, true));
	Insert("Z", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 5*32, 406 + 5*32, 32, 32, true));
	Insert("¯", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 6*32, 406 + 5*32, 32, 32, true));
	Insert("", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 7*32, 406 + 5*32, 32, 32, true));
	Insert("Q", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 8*32, 406 + 2*32, 32, 32, true));
	Insert("V", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 8*32, 406 + 3*32, 32, 32, true));
	Insert("X", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 8*32, 406 + 4*32, 32, 32, true));
	Insert("EMPTY", 
           SpriteConfigData(
               DL::Player, 1, 0.2, 8*32, 406 + 5*32, 32, 32, true));

}

void Alphabet::Insert(const std::string& name, const SpriteConfigData& data) {
  m_data.insert(std::make_pair(name, data));
}


SpriteConfigData Alphabet::Get(const std::string& name) const{
  if (Contains(name)){

    return m_data.find(name)->second;
  }

  throw("Config not found: "+name);
}


bool Alphabet::Contains(const std::string& name) const{
  return (m_data.find(name) != m_data.end());
}