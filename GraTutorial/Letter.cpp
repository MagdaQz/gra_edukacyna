#include "Letter.h"
#include "Engine.h"


void Letter::Draw()
{
	const double tile_width = 
                Engine::Get().FRenderer()->GetTileWidth();
    const double tile_height = 
                Engine::Get().FRenderer()->GetTileHeight();

	const double pos_x = m_x * tile_width;
    const double pos_y = m_y * tile_height;

	m_letterSprite->DrawCurrentFrame(pos_x, pos_y, 
                                 tile_width, tile_height);
}

void Letter::CollisionOnRight(EntityPtr entity) {
   AllowMoveHorizontal();

}

void Letter::CollisionOnLeft(EntityPtr entity) {
     AllowMoveHorizontal();

}

void Letter::CollisionOverPlayer(EntityPtr entity) {
    AllowMoveVertical();
}

void Letter::CollisionUnderPlayer(EntityPtr entity) {
   AllowMoveVertical();

}


void Letter::Update(double dt)
{
	
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
	 m_letterSprite->Update(dt);


}


 bool Letter::operator == (const Letter & letter2)
 {
	 string n = letter2.GetLetter();
	 cout << " porownanie " << n <<" i " << m_letter<<endl; 
	 if(this->m_letter.compare(letter2.GetLetter()) == 0){
		 return true;}

	 return false;

 }