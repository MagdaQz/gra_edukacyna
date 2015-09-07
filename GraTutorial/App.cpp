

#include <cassert>
#include <string>
#include "App.h"
#include "Sound.h"

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void App::Run() {
  // inicjalizacja okna
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  Resize(m_window_width, m_window_height);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // podwójne buforowanie
 
  

  // inicjalizacja OpenGL
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_2D);
    // niewyœwietlanie przezroczystych fragmentów sprite'a
    glEnable(GL_ALPHA_TEST); 
    glAlphaFunc(GL_GEQUAL, 0.1);
 
    const std::string atlas_filename = "data/dinoGra.bmp";
    Engine& engine = Engine::Get();
    engine.Load();
    engine.FRenderer()->LoadTexture(atlas_filename);
    m_player->SetSprites(
            SpritePtr(new Sprite(engine.FSpriteConfig()->
                                   Get("player_left"))),
            SpritePtr(new Sprite(engine.FSpriteConfig()->
                                   Get("player_right"))),
            SpritePtr(new Sprite(engine.FSpriteConfig()->
                                   Get("player_stop"))),
			SpritePtr(new Sprite(engine.FSpriteConfig()->
									Get("player_up"))),
			SpritePtr(new Sprite(engine.FSpriteConfig()->
									Get("player_down"))) );


 
	Engine::Get().FSound()->LoadSounds();
    Engine::Get().FSound()->PlayMusic("game");

  // pêtla g³ówna
 // is_done = false;
  size_t last_ticks = SDL_GetTicks();

  while (!is_done) {
    ProcessEvents();
 
    // time update
    size_t ticks = SDL_GetTicks();
    double delta_time = (ticks - last_ticks) / 1000.0;
    last_ticks = ticks;
 
    // update & render
    if (delta_time > 0) {
      Update(delta_time);
    }
    Draw();
  }
 
  SDL_Quit();
}

void App::Draw() {
 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    m_player->Draw();
	m_wordsmaker->Draw();

    SDL_GL_SwapBuffers();

}

void App::ProcessEvents() {

	 if (is_done)
        return;
 
    // przyjrzyj zdarzenia
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_VIDEORESIZE) {
            Resize(event.resize.w, event.resize.h);
        } else if(event.type == SDL_KEYDOWN 
                   && event.key.keysym.sym == SDLK_LCTRL){		
				m_wordsmaker->LetLettersMove();
		}else if (event.type == SDL_KEYUP 
                   && event.key.keysym.sym == SDLK_LCTRL) {
            m_wordsmaker->ForbidLettersMove();
	
	   }else if (event.type == SDL_QUIT) {
            is_done = true;
            break;
        } else if (event.type == SDL_KEYDOWN 
                   && event.key.keysym.sym == SDLK_ESCAPE) {
            is_done = true;
            break;
        } else if (event.type == SDL_KEYDOWN 
                   && event.key.keysym.sym == SDLK_UP) {
            m_player->GoUp();
			if(m_wordsmaker->LettersCanMove())			
			{	m_wordsmaker->MoveUp();}

        } else if (event.type == SDL_KEYDOWN 
                   && event.key.keysym.sym == SDLK_LEFT) {
            m_player->GoLeft();
			if(m_wordsmaker->LettersCanMove())			
			{	m_wordsmaker->MoveLeft();}
        } else if (event.type == SDL_KEYDOWN 
                   && event.key.keysym.sym == SDLK_RIGHT) {
            m_player->GoRight();
			if(m_wordsmaker->LettersCanMove())			
				m_wordsmaker->MoveRight();
        } else if (event.type == SDL_KEYUP 
                   && event.key.keysym.sym == SDLK_LEFT) {
            m_player->StopLeft();			
			m_wordsmaker->StopLeft();
        } else if (event.type == SDL_KEYUP 
                   && event.key.keysym.sym == SDLK_RIGHT) {
            m_player->StopRight();		
			m_wordsmaker->StopRight();
        }else if (event.type == SDL_KEYDOWN
				&& event.key.keysym.sym == SDLK_DOWN) {
			m_player->GoDown();
			if(m_wordsmaker->LettersCanMove())			
			{	m_wordsmaker->MoveDown();}
		}else if (event.type == SDL_KEYUP
				&& event.key.keysym.sym == SDLK_UP) {
			m_player ->StopUp();
			m_wordsmaker->StopUp();
		}else if (event.type == SDL_KEYUP
				&& event.key.keysym.sym == SDLK_DOWN) {
			m_player ->StopDown();
			m_wordsmaker->StopDown();
		}else if (event.type == SDL_KEYDOWN
				&& event.key.keysym.sym == SDLK_SPACE){
			 do m_wordsmaker ->DrawMixed();
			 while(m_wordsmaker->LettersCollide(m_player));			 
		}else if (event.type == SDL_KEYDOWN
				&& event.key.keysym.sym == SDLK_RSHIFT){
			 NewGame();			 
		}
}
}
void App::Resize(size_t width, size_t height) {
  m_screen = SDL_SetVideoMode(width, height, 32, 
                              SDL_OPENGL | SDL_RESIZABLE | SDL_HWSURFACE);
  assert("problem z ustawieniem wideo");

  m_window_width = width;
  m_window_height = height;

  glViewport(0, 0, static_cast<GLsizei> (width), static_cast<GLsizei> (height));
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1, 0, 1, -1, 10);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void App::Update(double dt) {

 CheckPlayerEntitiesCollisions(dt);
 CheckLetterLetterCollisions(dt);
 CheckLetterFrameCollisions(dt);
  m_player->Update(dt);
  m_wordsmaker->Update(dt);
  m_wordsmaker->CheckIfWordCorrect();

}


void App::CheckPlayerEntitiesCollisions(double dt) {
    // poziomy i pionowy aabb gracza w nastêpnym 'kroku'
    Aabb player_box_x = m_player->GetNextHorizontalAabb(dt);
    Aabb player_box_y = m_player->GetNextVerticalAabb(dt);

	for (int i = 0; i < m_wordsmaker->GetWordSize(); i++) {
		LetterPtr letter = m_wordsmaker->GetLetter(i);
      
        Aabb letter_box = letter->GetNextAabb(dt);

        // sprawdŸ czy wyst¹pi³a kolizja. 
        if (player_box_y.IsOver(letter_box)) {
            m_player->CollisionUnderPlayer(letter);
			letter->CollisionOverPlayer(m_player);
            player_box_y = m_player->GetNextVerticalAabb(dt);
			letter_box = letter->GetNextVerticalAabb(dt);

        }
        else if (player_box_x.IsOnLeftOf(letter_box)) {

            m_player->CollisionOnRight(letter);
			letter->CollisionOnLeft(m_player);
            player_box_x = m_player->GetNextHorizontalAabb(dt);
			letter_box = letter->GetNextVerticalAabb(dt);

        }
        else if (player_box_x.IsOnRightOf(letter_box)) {

            m_player->CollisionOnLeft(letter);
			letter->CollisionOnLeft(m_player);			
            player_box_x = m_player->GetNextHorizontalAabb(dt);
			letter->GetNextHorizontalAabb(dt); 


        }
        else if (player_box_y.IsUnder(letter_box)) {
            m_player->CollisionOverPlayer(letter);
			letter->CollisionUnderPlayer(m_player);
            player_box_y = m_player->GetNextVerticalAabb(dt);
			letter->GetNextHorizontalAabb(dt);


        }
    }
}


void App::CheckCollisionOfOnePair(LetterPtr fst_letter,
                                 LetterPtr snd_letter, double dt)
{
	Aabb letter1_box_x = fst_letter->GetNextHorizontalAabb(dt);
    Aabb letter1_box_y = fst_letter->GetNextVerticalAabb(dt);

	Aabb letter2_box_x = snd_letter->GetNextHorizontalAabb(dt);
    Aabb letter2_box_y = snd_letter->GetNextVerticalAabb(dt);
	 Aabb letter_box1 = fst_letter->GetNextAabb(dt);
	 Aabb letter_box2 = snd_letter->GetNextAabb(dt);

	if (letter_box1.Collides(letter_box2) == false) {
        return;
    }
	else if (letter_box1.IsOver(letter_box2)) {

			fst_letter->StopDown();
			snd_letter->StopUp();
            fst_letter->GetNextAabb(dt);
			snd_letter->GetNextAabb(dt);
			m_player->CollisionUnderPlayer(fst_letter);

        }
	else if (letter1_box_x.IsOnRightOf(letter2_box_x)) {
			
			fst_letter->StopLeft();
			snd_letter->StopRight();
			fst_letter->GetNextAabb(dt);;
			snd_letter->GetNextAabb(dt);;
			m_player->CollisionOnLeft(fst_letter);

		}	
	else if (letter1_box_x.IsOnLeftOf(letter2_box_x)) {
		
			fst_letter->StopRight();
			snd_letter->StopLeft();
			fst_letter->GetNextAabb(dt);
			snd_letter->GetNextAabb(dt);
			m_player->CollisionOnRight(fst_letter);


        }
 
	else if (letter_box1.IsUnder(letter_box2)) {

			fst_letter->StopUp();
			snd_letter->StopDown();
            fst_letter->GetNextAabb(dt);
			snd_letter->GetNextAabb(dt);
			m_player->CollisionOverPlayer(fst_letter);

        }

}



void App::CheckLetterLetterCollisions(double dt)
{

	for (int i = 0; i < m_wordsmaker->GetWordSize(); i++) 
	{

		LetterPtr fst_letter = m_wordsmaker->GetLetter(i);
		for(int j = 0; j < m_wordsmaker->GetWordSize(); j++)
		{
			if( i == j) continue;
			LetterPtr snd_letter = m_wordsmaker->GetLetter(j);
			CheckCollisionOfOnePair(fst_letter,snd_letter, dt);

		}
          
    }

}


void App::CheckLetterFrameCollisions(double dt)
{
	for (int i = 0; i < m_wordsmaker->GetWordSize(); i++) 
	{

		LetterPtr letter = m_wordsmaker->GetLetter(i);
		for(int j = 0; j < m_wordsmaker->GetWordSize(); j++)
		{
			LetterPtr frame = m_wordsmaker->GetFrame(j);
			CheckCollisionsWithFrames(letter,frame, dt);
		}
          
    }
}

void App::CheckCollisionsWithFrames(LetterPtr letter, LetterPtr frame, double dt)
{
	Aabb letter_box_x = letter->GetNextHorizontalAabb(dt);
    Aabb letter_box_y = letter->GetNextVerticalAabb(dt);

	Aabb frame_box_x = frame->GetNextHorizontalAabb(dt);
    Aabb frame_box_y = frame->GetNextVerticalAabb(dt);
	 Aabb letter_box = letter->GetNextAabb(dt);
	 Aabb frame_box= frame->GetNextAabb(dt);

	if (letter_box.Collides(frame_box) == false) {
        return;
    }
	else{
		if(letter->GetLetter().compare(frame->GetLetter())== 0)
		{
			letter ->SetPosition(frame->GetX(), frame->GetY());
			letter ->Correct();
		}
	}

}


void App::NewGame()
{
	m_wordsmaker.reset(new WordsMaker());
}