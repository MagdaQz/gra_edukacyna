#include "WordsMaker.h"
#include <fstream>
#include "Engine.h"


WordsMaker::WordsMaker()
{
	m_alphabet.reset(new Alphabet());
	ReadWord();
	SetLetters();
	letterCanMove = false;
	mixed = false;
	m_winner.reset(new Sprite( SpriteConfigData(DL::Player, 1, 0.2, 0, 724, 337, 150, true)));
	m_table.reset(new Sprite( SpriteConfigData(DL::Player, 1, 0.2, 0, 878, 337, 150, true)));
	correct = false;
}


void WordsMaker::ReadWord()
{
	 std::ifstream wordReading("data/words.txt"); 
	 srand (time(NULL));
	 int word_number = rand() % 25 + 1;
	 for (int i = 0; i < word_number; i++)
	 {
		 wordReading >> m_word;

	 }
	 cout<<m_word<<endl;
}


void WordsMaker::SetLetters()
{
	m_wordsize = m_word.length();
	cout << m_wordsize<< " dlugosc vectora"<<endl;
	double poz_x = 3;
	double poz_y = 3;
	string letter;
	for (int i = 0; i < m_wordsize; i++)
	{
		letter = m_word[i];
		m_letters.push_back(LetterPtr( new Letter(poz_x,poz_y,10,10,letter)));
		m_letters[i]->SetSprite(SpritePtr(new Sprite(m_alphabet->Get(letter))));
		m_frame.push_back(LetterPtr( new Letter(poz_x,poz_y,10,10,letter)));
		m_frame[i]->SetSprite(SpritePtr(new Sprite(m_alphabet->Get("EMPTY"))));
		poz_x+=1;
	
	}
}


void WordsMaker::Draw()
{
	for (int i = 0; i < m_wordsize; i++)
	{
		m_frame[i]->Draw();
		m_letters[i]->Draw();

	}
	if(correct)
	{
		DrawInfo(m_winner);
	}
	if(mixed==false)
	{
		DrawInfo(m_table);
	}
}

void WordsMaker::Update(double dt)
{
	for (int i = 0; i < m_wordsize; i++)
	{
		m_frame[i]->Update(dt);
		m_letters[i]->Update(dt);


	}
	if(correct)
	{
		m_winner->Update(dt);
	}
	if(mixed==false)
	{
		m_table->Update(dt);
	}
	
}


void WordsMaker::DrawMixed()
{
	srand (time(NULL));
	int newX, newY;
	for (int i = 0; i < m_wordsize; i++)
	{
		newX = rand() % 10;
		newY = rand() % 10;
		m_letters[i]->SetPosition(newX,newY);
		m_letters[i]->Mixed();
		m_letters[i]->Draw();
	}
	mixed = true;
}

void WordsMaker::ForbidLettersMove()
{
	letterCanMove = false;
	for (int i = 0; i < m_wordsize; i++)
	{
		m_letters[i]->ForbidMoving();
	}

}

void WordsMaker::MoveRight()
{

	for (int i = 0; i < m_wordsize; i++)
	{
		if(m_letters[i]->CanMoveHorizontal())
			m_letters[i]->GoRight();
	}

}

void WordsMaker::MoveLeft()
{
	for (int i = 0; i < m_wordsize; i++)
	{
		if(m_letters[i]->CanMoveHorizontal())
			m_letters[i]->GoLeft();
	}
}

void WordsMaker::MoveUp()
{
	for (int i = 0; i < m_wordsize; i++)
	{
		if(m_letters[i]->CanMoveVertical())
			m_letters[i]->GoUp();
	}
}

void WordsMaker::MoveDown()
{
	for (int i = 0; i < m_wordsize; i++)
	{
		if(m_letters[i]->CanMoveVertical())
			m_letters[i]->GoDown();
	}
}

void WordsMaker::StopRight()
{
	for (int i = 0; i < m_wordsize; i++)
	{
			m_letters[i]->StopRight();

	}
}

void WordsMaker::StopLeft()
{
	for (int i = 0; i < m_wordsize; i++)
	{
			m_letters[i]->StopLeft();

	}
}

void WordsMaker::StopUp()
{
	for (int i = 0; i < m_wordsize; i++)
	{
			m_letters[i]->StopUp();
			m_letters[1]->ForbidMoving();
	}
}


void WordsMaker::StopDown()
{
	for (int i = 0; i < m_wordsize; i++)
	{
			m_letters[i]->StopDown();

	}
}


bool WordsMaker::LettersCollide(PlayerPtr player)
{
	Aabb player_box = player->GetAabb();
	for (int i = 0; i < m_wordsize; i++)
	{

		Aabb letter_box = m_letters[i]->GetAabb();
		Aabb frame_box = m_frame[i] ->GetAabb();
		if(letter_box.Collides(player_box)) return true;

		for (int j = i+1;j < m_wordsize; j++)
		{
			Aabb letter_box2 = m_letters[j]->GetAabb();
			if(letter_box.Collides(letter_box2)) return true;
			if(frame_box.Collides(letter_box2)) return true;
		}
	}
	return false;
}

bool WordsMaker:: CheckIfWordCorrect()
{
	if (mixed)
	{
		for (int i = 0; i < m_wordsize; i++)
		{
			if(m_letters[i]->IsCorrect() == false)
				return false;
		}
		DrawInfo(m_winner);
		correct = true;
		return true;
	}
	else return false;
}

void WordsMaker::DrawInfo(SpritePtr sprite)
{
	
	sprite->DrawCurrentFrame(0.1,0.5,0.8,0.4);

}