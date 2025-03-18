#ifndef _SS_Score
#define _SS_Score

namespace ss {

	class Score {
	private:
		static int score;
		static int high_score;


	public:

		static void initScore();
		static int getScore();
		static int getHighScore();
		static void giveScore(int value);
		static void saveHighScore();
	};

}
#endif // !SS_Score
