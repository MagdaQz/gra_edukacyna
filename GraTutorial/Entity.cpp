
#include <cmath>
#include <iostream>
#include "Entity.h"
#include "Engine.h"

Entity::Entity(double x, double y, double def_velocity_x, double def_velocity_y,
               double def_acceleration_x, double def_acceleration_y)
    : //m_default_velocity_x(def_velocity_x),
    //  m_default_velocity_y(def_velocity_y),
     // m_default_acceleration_x(def_acceleration_x),
     // m_default_acceleration_y(def_acceleration_y),
     // m_state(PS::Stand),
      m_x(x),
      m_y(y),
      m_vx(0),
      m_vy(0),
      m_ax(def_acceleration_x),
      m_ay(def_acceleration_y),
      m_is_on_ground(true),
      m_can_go_left(true),
      m_can_go_right(true)
      {
   // SetDefaultMovement();
}

void Entity::GetCurrentTile(size_t *x, size_t *y) const {
        const size_t v_tiles_count = Engine::Get().FRenderer()->GetVerticalTilesOnScreenCount();
        *y = v_tiles_count - (GetAabb().GetMinY() + GetAabb().GetMaxY()) / 2;
        *x = GetX() + GetBasicAabb().GetMaxX() / 2;
    }