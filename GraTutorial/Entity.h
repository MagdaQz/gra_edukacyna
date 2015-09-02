#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <iostream>
#include <memory>
#include "Aabb.h"
#include "Sprite.h"
#include "Types.h"

class Entity
{
public:
	  explicit Entity(double x, double y, double def_velocity_x, double def_velocity_y,
                    double def_acceleration_x = 0, double default_acceleration_y = 0);

    virtual ET::EntityType GetType() const = 0;
	virtual void Update(double dt){};
	virtual void Draw() const{};
	
	 // zarz¹dzanie po³o¿eniem 
    virtual double GetX() const { return m_x; }
    virtual double GetY() const { return m_y; }
    virtual double GetNextXPosition(double dt) const { return m_x + m_vx * dt; }
    virtual double GetNextYPosition(double dt) const { return m_y + m_vy * dt; }
    void SetX(double newx)                   { m_x = newx; }
    void SetY(double newy)                   { m_y = newy; }
    void SetPosition(double x, double y)     { m_x = x; m_y = y; }

	 // zarz¹dzanie prêdkoœci¹
   // double GetXVelocity() const              { return m_vx; }
 //   double GetYVelocity() const              { return m_vy; }
  //  double GetNextXVelocity(double dt) const { return m_vx ; }
  //  double GetNextYVelocity(double dt) const { return m_vy + m_ay * dt;; }
  //  double GetDefaultXVelocity() const       { return m_default_velocity_x; }
  //  double GetDefaultYVelocity() const       { return m_default_velocity_y; }
   // void  NegateXVelocity()                  { m_vx = -m_vx; }
  //  void  NegateYVelocity()                  { m_vy = -m_vy; }
  //  void  NegateVelocity()                   { NegateXVelocity(); NegateYVelocity(); }
  //  void  SetXVelocity(double velocity)      { m_vx = velocity; }
 //   void  SetYVelocity(double velocity)      { m_vy = velocity; }
 //   void  SetVelocity(double vx, double vy)  { m_vx = vx; m_vy = vy; }

    // zarz¹dzanie przyspieszeniem
  //  double GetXAcceleration() const          { return m_ax; }
 //   double GetYAcceleration() const          { return m_ay; }
  //  double GetDefaultXAcceleration() const   { return m_default_acceleration_x; }
 //   double GetDefaultYAcceleration() const   { return m_default_acceleration_y; }
 //   void  SetXAcceleration(double accel)     { m_ax = accel; }
  //  void  SetYAcceleration(double accel)     { m_ay = accel; }


	
   // pod argumenty x, y zapisuje numer aktualnego kafla
    void GetCurrentTile(size_t *x, size_t *y) const;

	 // prostok¹t otaczaj¹cy jednostkê bez uwzglêdniania pozycji jednostki
    virtual Aabb GetBasicAabb() const { return Aabb(0, 0, 1, 1);  }

    Aabb GetAabb() const { return GetBasicAabb().Move(m_x, m_y, m_x, m_y); }

    Aabb GetNextHorizontalAabb(double dt) const {
        return GetBasicAabb().Move(GetNextXPosition(dt), m_y, GetNextXPosition(dt), m_y);
    }

    Aabb GetNextVerticalAabb(double dt) const {
        return GetBasicAabb().Move(m_x, GetNextYPosition(dt), m_x, GetNextYPosition(dt));
    }

    Aabb GetNextAabb(double dt) const {
        return GetBasicAabb().Move(GetNextXPosition(dt), GetNextYPosition(dt),
                                   GetNextXPosition(dt), GetNextYPosition(dt) );
    }


private:

//	double m_default_velocity_x;      // domyœlna prêdkoœæ
 //   double m_default_velocity_y;
 //   double m_default_acceleration_x;  // domyœlne przyspieszenie
 //   double m_default_acceleration_y;

protected:
   // PS::PlayerState m_state;  // stan, w którym znajduje siê jednostka
    //SpritePtr m_left;         // animacja, kiedy jednostka idzie w lewo
    //SpritePtr m_right;        // animacja, kiedy jednostka idzie w prawo
    //SpritePtr m_stop;         // animacja, kiedy jednostka stoi

    double m_x;               // po³o¿enie jednostki na osi odciêtych
    double m_y;               // po³o¿enie jednostki na osi rzêdnych
    double m_vx;              // prêdkoœæ w poziomie
    double m_vy;              // prêdkoœæ w pionie
    double m_ax;              // przyspieszenie w poziomie
    double m_ay;              // przyspieszenie w pionie
    bool m_is_on_ground;      // czy postaæ jest na pod³o¿u
    bool m_can_go_left;       // czy postaæ mo¿e iœæ w lewo
    bool m_can_go_right;     // czy postaæ mo¿e iœæ w prawo
	bool m_can_go_up;
	bool m_can_go_down;
};

typedef shared_ptr<Entity> EntityPtr;



#endif
