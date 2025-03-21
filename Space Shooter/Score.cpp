#include "Score.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace ss {

    int Score::score = 0;
    int Score::high_score = 0;

    std::string Score::filePath = "data/saves/data.sav";

    void Score::initScore()
    {
        std::ifstream file(filePath);

       
        if (!file.is_open()) {
            std::ofstream createFile(filePath);
            createFile.close();
            return;
        }

        std::string line;
        if (std::getline(file, line)) {
            std::istringstream(line) >> high_score;
        }
        else {
            std::cout << "B³¹d przy odczycie pliku lub plik jest pusty." << std::endl;
        }

        file.close();
    }

    int Score::getScore()
    {
        return score;
    }

    int Score::getHighScore()
    {
        return high_score;
    }

    void Score::giveScore(int value)
    {
        score += value;
    }

    void Score::saveHighScore()
    {
        if (score > high_score) {
            std::ofstream file(filePath);

            if (file.is_open()) {
                file << score << std::endl;
            }
            else {
                std::cout << "Nie uda³o siê otworzyæ pliku do zapisu." << std::endl;
            }

            file.close();
        }
    }

}  
