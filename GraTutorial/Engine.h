#include "SpriteConfig.h"
#include "Renderer.h"
#include "Sound.h"
#include "WordsMaker.h"


class Engine {
public:
  // zwraca instancjê klasy Engine - jedyn¹
  static Engine& Get() {
    static Engine engine;
    return engine;
  }
 
  // inicjalizacja klasy Engine - utworzenie instancji odpowiednich klas
  void Load() {
		m_spriteConfig.reset(new SpriteConfig());
		m_renderer.reset(new Renderer());
		m_sound.reset(new Sound());
		m_wordsmaker.reset(new WordsMaker());
		
  }
 
 SpriteConfigPtr FSpriteConfig() {  return m_spriteConfig;  }
  RendererPtr FRenderer() {  return m_renderer;  }
  SoundPtr FSound() { return m_sound; }
  WordsMakerPtr FWordsMaker() {return m_wordsmaker;}
 
private:
  SpriteConfigPtr m_spriteConfig;
  RendererPtr m_renderer;
  SoundPtr m_sound;
  WordsMakerPtr m_wordsmaker;
};