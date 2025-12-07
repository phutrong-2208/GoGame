#ifndef SOUND_EFFECT_HPP
#define SOUND_EFFECT_HPP

#include "SFML/Audio.hpp"
#include <string>

class SoundEffect{
    public:
        sf :: SoundBuffer clickSound, pieceSound;
        sf :: Sound click, piece;
        sf :: Music Background;
    SoundEffect(){
        clickSound.loadFromFile("assets\\click_button_effect.wav");
        click.setBuffer(clickSound);
        click.setVolume(100.f);
        
        pieceSound.loadFromFile("assets\\chess_placing.wav");
        piece.setBuffer(pieceSound);
        piece.setVolume(100.f);
        Background.openFromFile("assets\\background0.wav");
        Background.setVolume(50.f);
    }
};

extern SoundEffect Audio;

#endif