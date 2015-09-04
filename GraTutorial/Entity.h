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
	
	 // zarz�dzanie po�o�eniem 
    virtual double GetX() const { return m_x; }
    virtual double GetY() const { return m_y; }
    virtual double GetNextXPosition(double dt) const { return m_x + m_vx * dt; }
    virtual double GetNextYPosition(double dt) const { return m_y + m_vy * dt; }
    void SetX(double newx)                   { m_x = newx; }
    void SetY(double newy)                   { m_y = newy; }
    void SetPosition(double x, double y)     { m_x = x; m_y = y; }

	
	
   // pod argumenty x, y zapisuje numer aktualnego kafla
    void GetCurrentTile(size_t *x, size_t *y) const;

	 // prostok�t otaczaj�cy jednostk� bez uwzgl�dniania pozycji jednostki
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



protected:

    double m_x;               // po�o�enie jednostki na osi odci�tych
    double m_y;               // po�o�enie jednostki na osi rz�dnych
    double m_vx;              // pr�dko�� w poziomie
    double m_vy;              // pr�dko�� w pionie
    double m_ax;              // przyspieszenie w poziomie
    double m_ay;              // przyspieszenie w pionie
    bool m_is_on_ground;      // czy posta� jest na pod�o�u
    bool m_can_go_left;       // czy posta� mo�e i�� w lewo
    bool m_can_go_right;     // czy posta� mo�e i�� w prawo
	bool m_can_go_up;
	bool m_can_go_down;
};

typedef shared_ptr<Entity> EntityPtr;



#endif
