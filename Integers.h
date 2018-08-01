#pragma once

struct Player
{
  public:
    bool low;
    uint8_t x = 17;
    uint8_t y = 0;
    int Hp = 50;
    uint8_t Move;
    uint8_t P_Attack = 0;
    int Defence;
    bool Poisoned = false;
};
Player player;
struct Enemy
{
  public:
    bool low = false;
    uint8_t Move;
    int Hp = 50;
    uint8_t P_Attack = 0;
    uint8_t x = 56;
    uint8_t y = 0;
    int Defence = 0;
    int Attack = 0;
    bool active = true;
    bool Check = true;
    bool Poisoned = false;
    
};
Enemy enemy;
#define You true
#define Them false

#define Game_Title 0
#define Game_Main 1
#define Game_Win 2
#define Game_lose 3

#define Pos_1 0
#define Pos_2 16
#define Pos_3 32
#define Pos_4 48

bool turn = You;

String Title = "Dungeon Dice";

int gamestate = Game_Title;

