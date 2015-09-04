#ifndef __WORDSMAKER_H__
#define __WORDSMAKER_H__

#include <memory> 
#include "Types.h"
#include <string>
#include "Sprite.h"
#include "Alphabet.h"
#include <fstream>
#include <cstring>
#include <list>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Entity.h"
#include "Letter.h"
//#include "Player.h"




class WordsMaker 
{


public:
WordsMaker();
 void LettersMaker();

 void ReadWord();
 void SetLetters();
 void Draw();
 void Update(double dt);
 void DrawInfo(SpritePtr sprite);
 void DrawMixed();

 void LetLettersMove() {letterCanMove = true;}
 void ForbidLettersMove();
 bool LettersCanMove() { return letterCanMove;}
 int GetWordSize(){return m_word.length();}
 LetterPtr GetLetter(int n){return m_letters[n];}
 LetterPtr GetFrame (int n){return m_frame[n];}
 bool LettersCollide();
 bool CheckIfWordCorrect();




 void MoveRight();
 void MoveLeft();
 void MoveUp();
 void MoveDown();
 void StopRight();
 void StopLeft();
 void StopUp();
 void StopDown();
// bool SpellingIsCorrect(LetterPtr letter1, LetterPtr letter2); 

private:
  std::string m_word;
  int m_wordsize;
 AlphabetPtr m_alphabet;
 vector <LetterPtr> m_letters;
 vector <LetterPtr> m_frame;
 bool letterCanMove;
 bool mixed;
 bool correct;
 SpritePtr m_winner;
 SpritePtr m_table;

};

typedef shared_ptr<WordsMaker> WordsMakerPtr;

#endif