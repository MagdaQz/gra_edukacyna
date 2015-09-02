#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <memory>
#include <string>
#include <vector>
#include <list>
#include "Aabb.h"
#include "Types.h"

// Dane dotycz¹ce jednostki wczytane np. z pliku. Na ich podstawie
// zostanie w grze stworzona odpowiednia jednostka
struct LevelEntityData {
    LevelEntityData()
        :  name("[unknown]"), x(-1), y(-1) {   }

    LevelEntityData(const std::string& name, double x, double y)
        :  name(name), x(x), y(y) {   }

    bool operator() (const LevelEntityData& a, const LevelEntityData& b) {
        return a.x < b.x;
    }

    std::string name;  // nazwa jednostki
    double x;          // po³o¿enie na osi odciêtych
    double y;          // po³o¿enie na osi rzêdnych
};


class Level {
public:
    explicit Level();

    void LoadFromFile(const std::string& filename);
    void LoadEntitiesFromFile(const std::string& filename);
    std::list<LevelEntityData> GetAllEntitiesToCreate() const  { return m_entities_to_create; }
    LevelEntityData GetPlayerData() const { return m_player_data; }

    FT::FieldType Field(size_t x, size_t y) const;
    size_t GetWidth() const   { return m_width; }
    size_t GetHeight() const  { return m_height; }
    Aabb GetFieldAabb(size_t x, size_t y) const;
    
private:
    size_t m_width;
    size_t m_height;
    std::vector<std::vector<FT::FieldType> > m_data;
    std::list<LevelEntityData> m_entities_to_create;
    LevelEntityData m_player_data;

};
typedef shared_ptr<Level> LevelPtr;

#endif
