#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Aabb.h"
#include <memory>

class Object {
public:
    Object(double x, double y)
        : m_x(x), m_y(y) {
    }

    double GetX() const { return m_x; }
    double GetY() const { return m_y; }
    Aabb GetAabb() const { return Aabb(GetX(), GetY(), GetX()+1, GetY()+1); }
    
    void Draw() const;
    
private:
    double m_x;
    double m_y;
};

typedef boost::shared_ptr<Object> ObjectPtr;

#endif