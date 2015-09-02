#ifndef _App_h
#define _App_h


#include <assert.h> 
#include <SDL/SDL.h>
#include "Engine.h"
#include "Sprite.h"
#include "Player.h"
#include "WordsMaker.h"
#include <SDL_mixer.h>

class App {

public:
  explicit App(size_t win_width, size_t win_height, bool fullscreen_mode) 
    : m_window_width(win_width), m_window_height(win_height), 
    m_fullscreen(fullscreen_mode) {
		m_player.reset(new Player(1, 1, 10, 10));
		m_wordsmaker.reset(new WordsMaker());

  }
 


  void Run();
 
private:
  void Draw();                // rysowanie 
  void Update(double dt);     // aktualizacja
  void Resize(size_t width, size_t height);   // zmiana rozmiaru okna
  void ProcessEvents();       // przetwarzanie zdarzeñ, które przysz³y
  void NewGame();
  void CheckPlayerEntitiesCollisions(double dt);
  void CheckLetterLetterCollisions(double dt);
  void CheckLetterFrameCollisions(double dt);
  void CheckCollisionOfOnePair(LetterPtr fst_letter,
                                 LetterPtr snd_letter, double dt);
  void CheckCollisionsWithFrames(LetterPtr letter, LetterPtr frame, double dt);
 
private:
    size_t m_window_width;   // szerokoœæ okna
    size_t m_window_height;  // wysokoœæ okna
    bool m_fullscreen;       // tryb pe³noekranowy
    bool is_done;
    SDL_Surface* m_screen;
    PlayerPtr m_player;
	WordsMakerPtr m_wordsmaker;
};


#endif