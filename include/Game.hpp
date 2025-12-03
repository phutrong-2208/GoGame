#pragma once
#include <filesystem>
#include <iostream>

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "soundEffect.hpp"
#include "mouseInput.hpp"
#include "roundedRectangle.hpp"
#include "Board.hpp"
#include "button.hpp"
#include "renderZone.hpp"
#include "fileOperation.hpp"
#include "boardOperation.hpp"
#include "UIManager.hpp"
#include "ModeManager.hpp"
#include "SettingManager.hpp"
#include "MenuManager.hpp"
#include "ScoreRevealManager.hpp"
#include "BotLogic.hpp"
#include "EasyMode.hpp"
#include "Medium_HardMode.hpp"
#include "modelEngine.hpp"

class Game {
public:
    void run(void);  // game loop
};
