#ifndef SOUND_EFFECT_HPP
#define SOUND_EFFECT_HPP

#include "SFML/Audio.hpp"

class SoundEffect{
    public:
        sf :: SoundBuffer clickSound, pieceSound;
        sf :: Sound click, piece;
        sf :: Music Background;
    SoundEffect(){
        clickSound.loadFromFile("assets\\click_button_effect.wav");
        click.setBuffer(clickSound);
        click.setVolume(500.f);
        
        pieceSound.loadFromFile("assets\\chess_placing.wav");
        piece.setBuffer(pieceSound);
        piece.setVolume(500.f);
        Background.openFromFile("assets\\background.wav");
        Background.setVolume(50.f);
    }
};

#endif