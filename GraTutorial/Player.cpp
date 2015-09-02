#include <cmath>
#include "Player.h"
#include "Engine.h"
 
Player::Player(double x, double y, size_t level_width, size_t level_height) 
    : Entity(x, y, DefaultXVelocity, DefaultYVelocity, DefaultXAcceleration, DefaultYAcceleration),
	  m_state(PS::Stand),
     // m_x(x),
     // m_y(y),
     // m_vx(0.0),
    //  m_vy(0),
    //  m_ay(DefaultYAcceleration),
      m_running_factor(1.0),
      m_jump_allowed(true),
      m_level_width(level_width),
	  m_level_height(level_height),
      m_is_on_ground(true),
    //  m_can_go_left(true),
   //   m_can_go_right(true),
	  m_can_go_down(true),
	  m_can_go_up(true)
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

void Player::Jump(double y_velocity) {
    // wykonaj skok o ile jest taka mo�liwo��
    if (m_jump_allowed) {
        m_jump_allowed = false;
        m_is_on_ground = false;
        m_vy = y_velocity;            // pocz�tkowa pr�dko��
        m_ay = DefaultYAcceleration;  // przyspieszenie
    }
}
 
void Player::CollisionOnRight(EntityPtr entity) {

   ForbidGoingRight();
   StopRight();
  // cout<<"kolizja z prawej"<<endl;
}

void Player::CollisionOnLeft(EntityPtr entity) {
    ForbidGoingLeft();
	//SetXVelocity(0);
	StopLeft();
	//cout <<"kolizja z lewej"<<endl;

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
 
    // wylicz pozycj� gracza na ekranie
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
    // wylicz now� pr�dko�� oraz po��enie na osi OY
  /*  if (!m_is_on_ground) {
        m_y = GetNextYPosition(dt);
        m_vy += m_ay * dt;
    }*/
 
    // je�eli poni�ej pierwszego kafla, to nie spadaj ni�ej.
    // Na razie ustalamy poziom na y=1, aby posta� nie ucieka�a
    //  za ekran
  /*  if (m_y < 1) {
        m_y = 1;
        PlayerOnGround();}*/
    
 
    // wylicz pozycj� gracza w poziomie (o� OX).
    m_x = GetNextXPosition(dt);
	m_y = GetNextYPosition(dt);
    // nie mo�na wyj�� poza map�
    if (m_x < 0) {
        m_x = 0; // nie mo�na wyj�� za pocz�tek mapy
    } else if (m_x > m_level_width - 1) {
        // nie mo�na wyj�� za praw� kraw�d� mapy
        m_x = m_level_width - 1; 
    }
	 if (m_y < 0) {
        m_y = 0; // nie mo�na wyj�� za pocz�tek mapy
    } else if (m_y > m_level_height - 1) {
        // nie mo�na wyj�� za praw� kraw�d� mapy
        m_y = m_level_height - 1; 
    }

	/* double next_x = GetNextXPosition(dt);
    if (next_x < m_x && m_can_go_left) {
        m_x = next_x;
    } else if (next_x > m_x && m_can_go_right) {
        m_x = next_x;
    } */
    // ustal stan ruchu gracza na podstawie pr�dko�ci
   /* if (fabs(m_vx) < 0.01) {
        m_state = PS::Stand;
        m_vx = 0;
    } else*/ if (m_vx > 0.0) {
        m_state = PS::GoRight;
    } else if(m_vx < 0.0 ) {
		m_state = PS::GoLeft;
	}else if (m_vy > 0.0)
		m_state = PS::GoUp;
		else if (m_vy < 0.0)
		m_state = PS::GoDown;
    
 
    // uaktualnij animacj�
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