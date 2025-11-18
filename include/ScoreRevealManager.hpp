#ifndef SCORE_REVEAL_MANAGER_HPP
#define SCORE_REVEAL_MANAGER_HPP
#include "UIManager.hpp"
#include "renderZone.hpp"
#include "Board.hpp"
#include "Button.hpp"

class ScoreReveal{
    public:
        void setupScoreButton(std :: vector<Button> &button_list);
        void drawScoreReveal(sf :: RenderWindow &window, GoBoard& goBoard);
};

extern ScoreReveal ScoreUI;

#endif SCORE_REVEAL_MANAGER_HPP