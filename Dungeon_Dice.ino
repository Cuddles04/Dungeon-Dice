#include <Arduboy2.h>
#include "Integers.h"
#include "Bitmaps.h"
Arduboy2 arduboy;

void DrawIcons()
{
  arduboy.drawBitmap(0, 0, Attack, 16, 16);
  arduboy.drawBitmap(0, 16, Defend, 16, 16);
  arduboy.drawBitmap(0, 32, Poison, 16, 16);
  arduboy.drawBitmap(0, 48, Heal, 16, 16);
  arduboy.drawBitmap(player.x, player.y, Arrow, 16, 16);
  arduboy.drawRect(78, 0, 50, 5);
  arduboy.fillRect(79, 1, player.Hp, 3);
  arduboy.fillRect(79, 2, player.Defence, 1);
}
void Controls()
{
  if (arduboy.justPressed(DOWN_BUTTON))
  {
    if (player.y == Pos_1) {
      player.y = Pos_2;
    }
    else if (player.y == Pos_2) {
      player.y = Pos_3;
    }
    else if (player.y == Pos_3) {
      player.y = Pos_4;
    }
  }
  else if (arduboy.justPressed(UP_BUTTON))
  {
    if (player.y == Pos_4) {
      player.y = Pos_3;
    }
    else if (player.y == Pos_3) {
      player.y = Pos_2;
    }
    else if (player.y == Pos_2) {
      player.y = Pos_1;
    }
  }
  if (arduboy.justPressed(B_BUTTON))
  {
    if (player.y == Pos_1) {
      if (enemy.Defence <= 0) {
        enemy.Hp -= random(1, 4) * 10;
      } else if (enemy.Defence > 0) {
        enemy.Defence -= random(1, 4) * 10;
      }
    }
    else if (player.y == Pos_2) {
      player.Defence += random(1, 4) * 10;
    }
    else if (player.y == Pos_3) {
      player.P_Attack += random(1, 4) * 10;
      enemy.Poisoned = true;
    }
    else if (player.y == Pos_4) {
      player.Hp += random(1, 4) * 10;
      player.Poisoned = false;
      enemy.P_Attack = 0;
    }
    turn = Them;
    enemy.active = true;
    enemy.Check = true;
    if (enemy.Poisoned == true)
    {
      enemy.Hp -= player.P_Attack;
    }
  }
}
void TextCheck()
{
  if (player.y == Pos_1) {
    arduboy.setCursor(23, Pos_1 + 4);
    arduboy.print(F("Attack"));
  }
  if (player.y == Pos_3) {
    arduboy.setCursor(23, Pos_3 + 4);
    arduboy.print(F("Posion:"));
    arduboy.print(enemy.P_Attack);
  }
  if (player.y == Pos_2) {
    arduboy.setCursor(23, Pos_2 + 4);
    arduboy.print(F("Defense:"));
    arduboy.print(player.Defence);
  }
  if (player.y == Pos_4) {
    arduboy.setCursor(23, Pos_4 + 4);
    arduboy.print(F("Heal"));
  }

}
void Enemy_Move()
{
  if (enemy.y < 48) {
    enemy.y++;
  }
  if (player.x < 56) {
    player.x++;
  }
  if (enemy.active == true) {
    enemy.Move = random(1, 5);
    enemy.active = false;
    enemy.Attack = random(1, 4) * 10;
  }
  if (player.y == Pos_1) {
    arduboy.drawBitmap(player.x, player.y, Attack, 16, 16);
  }
  else if (player.y == Pos_2) {
    arduboy.drawBitmap(player.x, 0, Defend, 16, 16);
  }
  else if (player.y == Pos_3) {
    arduboy.drawBitmap(player.x, 0, Poison, 16, 16);
  }
  else if (player.y == Pos_4) {
    arduboy.drawBitmap(player.x, 0, Heal, 16, 16);
  }

  if (enemy.Move == 1) {
    arduboy.drawBitmap(enemy.x, enemy.y, Attack, 16, 16);
  }
  else if (enemy.Move == 2) {
    arduboy.drawBitmap(enemy.x, enemy.y, Defend, 16, 16);
  }
  else if (enemy.Move == 3) {
    arduboy.drawBitmap(enemy.x, enemy.y, Poison, 16, 16);
  }
  else if (enemy.Move == 4) {
    arduboy.drawBitmap(enemy.x, enemy.y, Heal, 16, 16);
  }
  if (enemy.Poisoned == true)
  {
    arduboy.drawBitmap(56, 32, Poison, 16, 16);
  }
  if (enemy.Move == 1 and enemy.Check == true)
  {
    if (player.Defence <= 0) {
      player.Hp -= enemy.Attack;
    }
    else if (player.Defence > 0) {
      player.Defence -= enemy.Attack;
    }
    enemy.Check = false;
  }
  else if (enemy.Hp < 50) {
    if (enemy.Move == 4 and enemy.Check == true) {
      enemy.Hp += random(1, 4) * 10;
      enemy.Check = false;
      enemy.Poisoned = false;
      enemy.P_Attack = 0;
    }
  }
  else if (enemy.Move == 2 and enemy.Check == true) {
    enemy.Defence += random(1, 4) * 10;
    enemy.Check = false;
  }
  else if (enemy.Move == 3 and enemy.Check == true) {
    enemy.P_Attack += random(1, 4) * 10;
    enemy.Check = false;
    player.Poisoned = true;
  }
  arduboy.drawRect(0, 0, 50, 5);
  arduboy.fillRect(0, 1, player.Hp, 3);
  arduboy.fillRect(0, 2, player.Defence, 1);

  arduboy.drawRect(78, 0, 50, 5);
  arduboy.fillRect(79, 1, enemy.Hp, 3);
  arduboy.fillRect(79, 2, enemy.Defence, 1);
  if (arduboy.justPressed(A_BUTTON))
  {
    turn = You;
    player.y = Pos_1;
    player.x = 17;
    enemy.y = 0;
    if (player.Poisoned == true)
    {
      player.Hp -= enemy.P_Attack;
    }
  }
}
void Stat_Check()
{
  if (player.Hp < 0) {
    player.Hp = 0;
    gamestate = Game_lose;
  }
  if (player.Hp > 50) {
    player.Hp = 50;
  }
  if (enemy.Hp < 0) {
    enemy.Hp = 0;
    gamestate = Game_Win;
  }
  if (enemy.Hp > 50) {
    enemy.Hp = 50;
  }

  if (player.Defence < 0) {
    player.Defence = 0;
  }
  if (player.Defence > 50) {
    player.Defence = 50;
  }
  if (enemy.Defence < 0) {
    enemy.Defence = 0;
  }
  if (enemy.Defence > 50) {
    enemy.Defence = 50;
  }
}
void Reset()
{
  player.Hp = 50;
  player.Defence = 0;
  player.Poisoned = false;
  enemy.Hp = 50;
  enemy.Defence = 0;
  enemy.Poisoned = false;
  turn = You;
  player.y = Pos_1;
}
void setup()
{
  arduboy.begin();
  arduboy.setFrameRate(30);
  arduboy.initRandomSeed();
}

void loop()
{
  switch ( gamestate ) {
      break;
    case Game_Title:
      if (!(arduboy.nextFrame()))
        return;
      arduboy.clear();
      arduboy.drawBitmap(0,0,title,128,64);
      arduboy.pollButtons();
      arduboy.setCursor(28, 0);
      arduboy.print(Title);
      if (arduboy.justPressed(A_BUTTON))
      {
        gamestate = Game_Main;
      }
      arduboy.display();
      break;
    case Game_Main:
      arduboy.clear();
      arduboy.pollButtons();
      arduboy.initRandomSeed();
      DrawIcons();
      TextCheck();
      Stat_Check();
      if (turn == You)
      {
        Controls();
      }
      else if (turn == Them)
      {
        arduboy.clear();
        Enemy_Move();
      }
      arduboy.display();
      break;
    case Game_lose:
      arduboy.clear();
      arduboy.pollButtons();
      arduboy.setCursor(40, 30);
      arduboy.print("Game Over");
      if (arduboy.justPressed(A_BUTTON)) {
        gamestate = Game_Title;
        Reset();
      }
      arduboy.display();
      break;
    case Game_Win:
      arduboy.clear();
      arduboy.pollButtons();
      arduboy.setCursor(45,0);
      arduboy.print("You Won");
      if (arduboy.justPressed(A_BUTTON)) {
        gamestate = Game_Title;
        Reset();
      }
      arduboy.display();
  }
}

