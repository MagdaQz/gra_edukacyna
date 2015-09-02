#ifndef __LETTER_H__
#define __LETTER_H__

#include "Sprite.h"
#include <memory>
#include <string>
#include "Entity.h"


class Letter : public Entity
{
public:
	Letter (double x, double y, size_t level_width, size_t level_height, std::string letter) 
    : Entity(x, y, DefaultXVelocity, DefaultYVelocity, DefaultXAcceleration, DefaultYAcceleration),
	  m_letter(letter),
      m_x(x),
      m_y(y),
      m_vx(0.0),
      m_vy(0),
      m_ay(DefaultYAcceleration),
      m_running_factor(1.0),
     // m_jump_allowed(true),
      m_level_width(level_width),
	  m_level_height(level_height),
    //  m_is_on_ground(true),
      m_can_go_left(false),
      m_can_go_right(false),
	  m_can_go_down(false),
	  m_can_go_up(false),
	  m_correct(false){}
	//SpritePtr GetSprite() {return m_sprite;};
	ET::EntityType GetType() const {
        return ET::Letter;
    }
	void SetSprite (SpritePtr letter)
	{
		m_letterSprite = letter;
	}
	void SetPosition(double newX, double newY)
	{
		m_x = newX;
		m_y = newY;
	}
	void Draw();
	void Update(double dt);
	void Mixed(){m_correct = false;}
	void Correct(){m_correct = true;}
	bool IsCorrect(){return m_correct;}
	double GetX() const { return m_x; }
    double GetY() const { return m_y; }
    double GetDefaultYVelocity()     const { 
        return DefaultYVelocity; 
    }
    double GetDefaultYAcceleration() const { 
        return DefaultYAcceleration; 
    }
	std::string GetLetter() {return m_letter;}

	 // obs³uga kolizji z ka¿dej strony
    void CollisionOnRight(EntityPtr entity);
    void CollisionOnLeft(EntityPtr entity);
    void CollisionOverPlayer(EntityPtr entity);
    void CollisionUnderPlayer(EntityPtr entity);

	//void Run()               { m_running_factor = 2.0; }
   // void StopRunning()       { m_running_factor = 1.0; }
    void GoLeft()            { m_vx -= 4.0; }
    void GoRight()           { m_vx += 4.0; }
	void GoDown()			 { m_vy -= 4.0; }
	void GoUp()				 { m_vy += 4.0; }
    void StopLeft()          { m_vx = 0; }
    void StopRight()         { m_vx = 0; }
	void StopDown()			 { m_vy = 0; }
	void StopUp()			 { m_vy = 0; }
    void ForbidGoingLeft()   { m_can_go_left = false; }
    void ForbidGoingRight()  { m_can_go_right = false; }
	void ForbidGoingDown()	 { m_can_go_down = false; }
	void ForbidGoingUp()	 { m_can_go_up = false; }
	void AllowMoveHorizontal() {m_can_go_right = true; m_can_go_left = true;}
	void AllowMoveVertical()   {m_can_go_up = true; m_can_go_down = true;}
	bool CanMoveHorizontal() {return m_can_go_left;}
	bool CanMoveVertical() {return m_can_go_up;}
	void ForbidMoving() { m_can_go_left = false;
						  m_can_go_right = false;
						  m_can_go_down = false;
						  m_can_go_up = false;}

	double GetNextXPosition(double dt) const { 
        return m_x + m_vx * dt * m_running_factor; 
    }
    double GetNextYPosition(double dt) const { 
        //return m_y + (m_vy + m_ay * dt) * dt; 
		return m_y + m_vy * dt * m_running_factor;
    }
 
	 Aabb GetBasicAabb() const { return Aabb(.1, 0, .9, .9);  }

	 std::string GetLetter() const {return m_letter;}
	 bool operator == (const Letter & letter2);

private:
	 enum { DefaultXVelocity = 4, DefaultYVelocity = 20,
           DefaultXAcceleration = 0, DefaultYAcceleration = -60 };
	 double m_x;               // po³o¿enie postaci na osi odciêtych
    double m_y;               // po³o¿enie postaci na osi rzêdnych
    double m_vx;              // prêdkoœæ na osi OX
    double m_vy;              // prêdkoœæ gracza w pionie
    double m_ay;              // przyspieszenie gracza w pionie
    double m_running_factor;  // wspó³czynnik biegania. 
    std::string m_letter;                         //         >1.0 => biegnie, 
                              //         <1.0 => spowolnienie

	size_t m_level_width; 
	size_t m_level_height;    // szerokoœæ poziomu (w kaflach)
   // bool m_is_on_ground;      // czy postaæ jest na pod³o¿u
    bool m_can_go_left;       // czy postaæ mo¿e iœæ w lewo
    bool m_can_go_right;      // czy postaæ mo¿e iœæ w prawo
	bool m_can_go_down;
	bool m_can_go_up;
	bool m_correct;
	SpritePtr m_letterSprite;
};

typedef shared_ptr<Letter> LetterPtr;

#endif
