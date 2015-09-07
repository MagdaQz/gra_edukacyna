#ifndef __PLAYER_H__
#define __PLAYER_H__
 
#include <memory> 
#include "Sprite.h"
#include "Types.h"
#include "Entity.h"
#include <stdexcept> 
 
class Player : public Entity
{
public:
    explicit Player(double x, double y, size_t level_width, size_t level_height);
 
    void SetSprites(SpritePtr left, SpritePtr right, SpritePtr stop, SpritePtr up, SpritePtr down);
    void Update(double dt);
    void Draw() const;
	ET::EntityType GetType() const {
        throw std::logic_error("Gracz nie jest jednostk¹");
    }
 
    double GetX() const { return m_x; }
    double GetY() const { return m_y; }
    double GetDefaultYVelocity()     const { 
        return DefaultYVelocity; 
    }
    double GetDefaultYAcceleration() const { 
        return DefaultYAcceleration; 
    }
 

    void GoLeft()            { m_vx -= 4.0; m_state=PS::GoLeft; }
    void GoRight()           { m_vx += 4.0; m_state=PS::GoRight;}
	void GoDown()			 { m_vy -= 4.0; m_state =PS::GoDown; }
	void GoUp()				 { m_vy += 4.0; m_state = PS::GoUp; }
    void StopLeft()          { m_vx = 0; m_state=PS::Stand; }
    void StopRight()         { m_vx = 0; m_state=PS::Stand; }
	void StopDown()			 { m_vy = 0; m_state=PS::Stand; }
	void StopUp()			 { m_vy = 0; m_state=PS::Stand; }
    void ForbidGoingLeft()   { m_can_go_left = false; }
    void ForbidGoingRight()  { m_can_go_right = false; }
	void ForbidGoingDown()	 { m_can_go_down = false; }
	void ForbidGoingUp()	 { m_can_go_up = false; }

    void SetDefaultMoving()  {
                               m_can_go_right = m_can_go_left=true;
    }

 
    double GetNextXPosition(double dt) const { 
        return m_x + m_vx * dt ;
    }
    double GetNextYPosition(double dt) const { 
		return m_y + m_vy * dt; 
    }
 
	 Aabb GetBasicAabb() const { return Aabb(.1, 0, .7, .9);  }

	 // obs³uga kolizji z ka¿dej strony
    void CollisionOnRight(EntityPtr entity);
    void CollisionOnLeft(EntityPtr entity);
    void CollisionOverPlayer(EntityPtr entity);
    void CollisionUnderPlayer(EntityPtr entity);

private:
    enum { DefaultXVelocity = 4, DefaultYVelocity = 20,
           DefaultXAcceleration = 0, DefaultYAcceleration = -60 };
 
    PS::PlayerState m_state;  // stan, w którym znajduje siê postaæ
    SpritePtr m_left;         // animacja - postaæ idzie w lewo
    SpritePtr m_right;        // animacja - postaæ idzie w prawo
    SpritePtr m_stop;		  // animacja - postaæ stoi
	SpritePtr m_down;		  // animacja - postac idzie w dó³
	SpritePtr m_up;			  // animacja - postac idzie w góre	

 
    size_t m_level_width;	  // wysokoœæ poziomu
	size_t m_level_height;    // szerokoœæ poziomu (w kaflach)

};
typedef shared_ptr<Player> PlayerPtr;
#endif