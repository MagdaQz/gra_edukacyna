#include <cmath>
#include "Player.h"
#include "Engine.h"
 
Player::Player(double x, double y, size_t level_width, size_t level_height) 
    : Entity(x, y, DefaultXVelocity, DefaultYVelocity, DefaultXAcceleration, DefaultYAcceleration, true),
	  m_state(PS::Stand),
     // m_running_factor(1.0),
    //  m_jump_allowed(true),
      m_level_width(level_width),
	  m_level_height(level_height)
 
{
    SetDefaultMoving();
}

void Player::SetSprites(SpritePtr left, 
                        SpritePtr right, 
                        SpritePtr stop, SpritePtr up, SpritePtr down) {
    m_left = left;
    m_right = right;
    m_stop = stop;
	m_up = up;
	m_down = down;
}

 
void Player::CollisionOnRight(EntityPtr entity) {

   ForbidGoingRight();
   StopRight();

}

void Player::CollisionOnLeft(EntityPtr entity) {
    ForbidGoingLeft();
	StopLeft();

}

void Player::CollisionOverPlayer(EntityPtr entity) {
    ForbidGoingUp();
	StopUp();
}

void Player::CollisionUnderPlayer(EntityPtr entity) {
   ForbidGoingDown();
   StopDown();
}


void Player::Draw() const {
    const double tile_width = 
                Engine::Get().FRenderer()->GetTileWidth();
    const double tile_height = 
                Engine::Get().FRenderer()->GetTileHeight();
 
    // wylicz pozycjê gracza na ekranie
    const double pos_x = m_x * tile_width;
    const double pos_y = m_y * tile_height;
 
    switch (m_state) {
    case PS::Stand:
        m_stop->DrawCurrentFrame(pos_x, pos_y, 
                                 tile_width, tile_height);
        break;
    case PS::GoLeft:
        m_left->DrawCurrentFrame(pos_x, pos_y, 
                                 tile_width, tile_height);
        break;
    case PS::GoRight:
        m_right->DrawCurrentFrame(pos_x, pos_y, 
                                  tile_width, tile_height);
		break;

	case PS::GoDown:
        m_down->DrawCurrentFrame(pos_x, pos_y, 
                                  tile_width, tile_height);
        break;
	case PS::GoUp:
        m_up->DrawCurrentFrame(pos_x, pos_y, 
                                  tile_width, tile_height);
        break;
    }
}

void Player::Update(double dt) {
 
 
    // wylicz pozycjê gracza w poziomie (oœ OX).
    m_x = GetNextXPosition(dt);
	m_y = GetNextYPosition(dt);
    // nie mo¿na wyjœæ poza mapê
    if (m_x < 0) {
        m_x = 0; // nie mo¿na wyjœæ za pocz¹tek mapy
    } else if (m_x > m_level_width - 1) {
        // nie mo¿na wyjœæ za praw¹ krawêdŸ mapy
        m_x = m_level_width - 1; 
    }
	 if (m_y < 0) {
        m_y = 0; // nie mo¿na wyjœæ za pocz¹tek mapy
    } else if (m_y > m_level_height - 1) {
        // nie mo¿na wyjœæ za praw¹ krawêdŸ mapy
        m_y = m_level_height - 1; 
    }

	
    if (m_vx > 0.0) {
        m_state = PS::GoRight;
    } else if(m_vx < 0.0 ) {
		m_state = PS::GoLeft;
	}else if (m_vy > 0.0)
		m_state = PS::GoUp;
		else if (m_vy < 0.0)
		m_state = PS::GoDown;
    
 
    // uaktualnij animacjê
    switch (m_state) {
    case PS::Stand:
        m_stop->Update(dt);
        break;
    case PS::GoLeft:
        m_left->Update(dt);
        break;
    case PS::GoRight:
        m_right->Update(dt);
        break;
	case PS::GoDown:
        m_right->Update(dt);
        break;
	case PS::GoUp:
        m_right->Update(dt);
        break;
    }
}