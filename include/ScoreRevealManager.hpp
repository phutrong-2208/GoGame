#ifndef SCORE_REVEAL_MANAGER_HPP
#define SCORE_REVEAL_MANAGER_HPP
#include "UIManager.hpp"

class ScoreReveal{
    public:
        void setupScoreButton(std :: vector<Button> button_list);
        void drawScoreReveal(sf :: RenderWindow &window);
};

#endif SCORE_REVEAL_MANAGER_HPP