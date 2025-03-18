#include "Score.hpp"

int ss::Score::score = 0;
int ss::Score::high_score = 0;

void ss::Score::initScore()
{

}

int ss::Score::getScore()
{
	return score;
}

int ss::Score::getHighScore()
{
	return high_score;
}

void ss::Score::giveScore(int value)
{
	score += value;
}

void ss::Score::saveHighScore()
{
	if (score > high_score) {

	}
}
