#pragma once

#define SCREEN_WIDTH 768
#define SCREEN_HEIGTH 1136

#define SPLASH_STATE_SHOW_TIME 3

#define SPLASH_SCENE_BACKGROUND_FILEPATH "Resources/res/Splash Background.png"
#define MAIN_MENU_BACKGROUND_FILEPATH "Resources/res/Main Menu Background.png"
#define GAME_BACKGROUND_FILEPATH "Resources/res/Main Menu Background.png"
#define PAUSE_BACKGROUND_FILEPATH "Resources/res/Main Menu Background.png"

#define MAIN_MENU_TITLE_FILEPATH "Resources/res/Game Title.png"

#define MAIN_MENU_PLAY_BUTTON_FILEPATH "Resources/res/Play Button.png"
#define RESUME_BUTTON_FILEPATH "Resources/res/Resume Button.png"
#define HOME_BUTTON_FILEPATH "Resources/res/Home Button.png"
#define RETRY_BUTTON_FILEPATH "Resources/res/Retry Button.png"

#define MAIN_MENU_PLAY_BUTTON_OUTER_FILEPATH "Resources/res/Play Button Outer.png"
#define PAUSE_BUTTON "Resources/res/Pause Button.png"
#define X_PIECE_BUTTON "Resources/res/X.png"
#define O_PIECE_BUTTON "Resources/res/O.png"
#define X_WINNING_PIECE_BUTTON "Resources/res/X Win.png"
#define O_WINNING_PIECE_BUTTON "Resources/res/O Win.png"

#define X_PIECE 8
#define O_PIECE 0
#define EMPTY_PIECE -1
#define PLAYER_PIECE X_PIECE
#define AI_PIECE O_PIECE

#define STATE_PLAYING 98
#define STATE_PAUSED 97
#define STATE_WON 96
#define STATE_LOSE 95
#define STATE_PLACING_PIECE 94
#define STATE_AI_PLAYING 93
#define STATE_DRAW 92