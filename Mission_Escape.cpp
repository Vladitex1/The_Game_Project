#include <iostream>
#include <cmath>
#include <fstream>
#include <windows.h>
#include <locale>
#include <conio.h>

using namespace std;

class The_Game {
private:
public:
    char playermodel = '\002';
    char badguymodel = '\001';
    char rightmodel = '\020';
    char leftmodel = '\021';
    char lvlbossmodel = '\005';
    char doormodel = 'l';
    char none = ' ';
    char healthmodel = '\003';
    int heartset1 = 95;
    int playerx = 12, playery = 12;

    char move = ' ';
    char Battle = ' ';



};
//-----------------------------------------------------------------------------------------Картинки------------------------------------------
class picture : public The_Game
{
    int idpic = -1;
public:
    void openpicture(int idpic, bool stripe, int strings)
    {
        const int len = 150;//len -длина strings высота
        const char ch = '\n';

        // создаем указатель на указатель
        char** mass = new char* [strings];

        // создаем каждую строку массива
        for (int i = 0; i < strings; i++) {
            mass[i] = new char[len];
        }




        string picarray[10] = { "Picture.txt","Picture1.txt","Picture2.txt","Picture3.txt","Picture4.txt","Picture5.txt","Picture6.txt","Picture7.txt","Picture8.txt","Picture9.txt" };
        ifstream fs(picarray[idpic]);

        if (!fs)
        {
            // Распечатываем ошибку и выходим
            cerr << "Uh oh, file dont opened for reading!" << endl;
        }


        for (int r = 0; r < strings; r++)
        {
            fs.getline(mass[r], len - 1); //Считываем строки в массив
            cout << mass[r] << endl; //Выводи строку из массива
        }
        fs.close(); //Закрываем файл
        if (stripe == true) { cout << "~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~" << endl << endl; }
        if (stripe == false) {}

    }
};
//------------------------------------------------------------------------------------------Генерация Карты----------------------------------
class WorldMap : public The_Game {
public:
    int i, j;
    int badguycount;
    int badguymatrix[2][10];
    int healthmatrix[10][2];
    int battleisstart = 5;
    int badguylvl1 = 0;
    int badguy_count = 1;
    int healthcount;
    int score1 = 0;
    bool set_health_use1 = NULL;
    bool door_detector_status = NULL;
    char world[16][61] = {
        //        0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45   46   47   48   49   50   51   52   53   54   55   56   57   58   59   60
        /*1*/   {' ', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', ' ', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', ' ', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', ' '}, //0
        /*2*/   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, //1
        /*3*/   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, //2
        /*4*/   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'l', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, //3
        /*5*/   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', '|', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, //4
        /*6*/   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '_', '_', '_', '_', '_', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '|'}, //5
        /*7*/   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, //6
        /*8*/   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', '_', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, //7
        /*9*/   {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', '_', '_', '_', '_', '|', ' ', ' ', '_', ' ', ' ', '|', ' ', ' ', '|', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', 'l', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, //8
        /*10*/  {'|', ' ', ' ', ' ', ' ', ' ', ' ', 'l', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', '|', ' ', ' ', '|', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', 'l', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, //9
        /*11*/  {'|', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', '|', ' ', ' ', '|', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, //10
        /*12*/  {'|', '_', '_', '_', '_', '_', '_', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '_', '|', ' ', ' ', '|', '_', '_', '|', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', '_', '_', '_', '_', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, //11
        /*13*/  {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '1'}, //12
        /*14*/  {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'l', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '1'}, //13
        /*15*/  {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', '|'}, //14
        /*16*/  {'|', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '|', '_', '_', '_', '|', '_', '_', '_', '_', '_', '_', '_', '|', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '|', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '|', '_', '_', '_', '_', '_', '_', '|'}  //15
    };

    void maprefresh() {
        //----------------------------------------------------------------------------Обновление карты

        health_detector();
        system("cls");
        for (i = 0; i < 16; i++)
        {                            // внешний цикл отвечает за перебор строк
            for (j = 0; j < 61; j++) // цикл для вывода элементов строки
                cout << world[i][j];
            cout << endl; // после вывода элементов j-й строки делаем переход на новую строку
        }
    }

    void setbattleisstart(int set)
    {
        battleisstart = set;
    }

    int getbattleisstart() const
    {
        return battleisstart;
    }

    void movestartpos()
    {
        world[5][5] = playermodel;
        world[playerx][playery] = none;
        playerx = 5, playery = 5;

    }

    bool test_borders()
    {
        bool test = false;
        if (world[playery][playerx] == '_') { world[playery][playerx] = '_';test = true; }
        if (world[playery][playerx] == '|') { world[playery][playerx] = '|';test = true; }
        if (world[playery][playerx] == 'l') { world[playery][playerx] = 'l';test = true; }
        if (world[playery][playerx] == '1') { world[playery][playerx] = '1';test = true; }
        if (world[3][16] != lvlbossmodel) { world[12][19] = none;world[13][19] = none;world[14][19] = none; }
        if (world[10][34] != lvlbossmodel) { world[2][39] = none;world[3][39] = none; }
        if (world[9][43] != lvlbossmodel) { world[12][60] = none;world[13][60] = none; }
        return test;
    }


    void moveup(int score1, int key1)//y+
    {
        world[playery][playerx] = none;
        playery = playery - 1;
        if (test_borders() == true) { playery = playery + 1; }//up
        badguy_detector();
        door_detector(key1);
        world[playery][playerx] = playermodel;
    }

    void movedown(int score1, int key1)//y+
    {

        world[playery][playerx] = none;
        playery = playery + 1;
        if (test_borders() == true) { playery = playery - 1; }//down
        badguy_detector();
        door_detector(key1);
        world[playery][playerx] = playermodel;
    }

    void moveleft(int score1, int key1)//x-
    {

        world[playery][playerx] = none;
        playerx = playerx - 1;
        if (test_borders() == true) { playerx = playerx + 1; }//left
        badguy_detector();
        door_detector(key1);
        world[playery][playerx] = playermodel;
    }

    void moveright(int score1, int key1)//x+
    {
        world[playery][playerx] = none;
        playerx = playerx + 1;
        if (test_borders() == true) { playerx = playerx - 1; }//right
        badguy_detector();
        door_detector(key1);
        world[playery][playerx] = playermodel;
    }

    void score_detector()
    {
        if (score1 == 0 || score1 == 1 || score1 == 2 || score1 == 3) { setbadguylvl(1); }
        if (score1 == 4 || score1 == 5 || score1 == 6 || score1 == 7) { setbadguylvl(2); }
        if (score1 == 8 || score1 == 9 || score1 == 10 || score1 == 11) { setbadguylvl(3); }
    }

    void door_detector(int key)
    {
        if (key>=1){
        if (world[playery - 1][playerx] == doormodel) { world[playery - 1][playerx] = none; set_door_detector_status(true); }
        if (world[playery + 1][playerx] == doormodel) { world[playery + 1][playerx] = none; set_door_detector_status(true); }
        if (world[playery][playerx + 1] == doormodel) { world[playery][playerx + 1] = none; set_door_detector_status(true); }
        if (world[playery][playerx - 1] == doormodel) { world[playery][playerx - 1] = none; set_door_detector_status(true); }
        }
    }

    void set_door_detector_status(bool set)
    {
        door_detector_status = set;
    }

    bool get_door_detector_status()
    {
        return door_detector_status;
    }

    void badguy_detector()
    {
        setbattleisstart(0);

        if (world[playery - 1][playerx] == lvlbossmodel || (world[playery + 1][playerx] == lvlbossmodel) || (world[playery][playerx + 1] == lvlbossmodel) || (world[playery][playerx - 1] == lvlbossmodel)) { setbadguylvl(4); setbattleisstart(1); }

        if ((world[playery - 1][playerx] == badguymodel))//UP
        {
            playery = playery - 1;
            world[playery + 1][playerx] == none;
            world[playery][playerx] == playermodel;
            score_detector();
            setbattleisstart(1);
        }


        if ((world[playery + 1][playerx] == badguymodel))//DOWN
        {
            playery = playery + 1;
            world[playery - 1][playerx] == none;
            world[playery][playerx] == playermodel;
            score_detector();
            setbattleisstart(1);
        }



        if ((world[playery][playerx + 1] == badguymodel))//right
        {
            world[playery][playerx] == none;
            playerx = playerx + 1;
            world[playery][playerx] == playermodel;
            score_detector();
            setbattleisstart(1);
        }


        if ((world[playery][playerx - 1] == badguymodel))//left
        {
            world[playery][playerx] == none;
            playerx = playerx - 1;
            world[playery][playerx] == playermodel;
            score_detector();
            setbattleisstart(1);
        }
    }

    void badguyposgen(int settings_lvl)
    {
        switch (settings_lvl) {
        case 1:
        {
            //Локация №1
            world[7][4] = badguymodel;
            world[13][17] = badguymodel;
            world[3][16] = lvlbossmodel;

            //Локация №2



            world[13][29] = badguymodel;
            world[2][26] = badguymodel;
            world[10][34] = lvlbossmodel;


            //Локация №3
            world[9][43] = lvlbossmodel;


            break;
        }
        case 2:
        {
            //Локация №1
            world[7][4] = badguymodel;
            world[13][17] = badguymodel;
            world[12][11] = badguymodel;
            world[3][16] = lvlbossmodel;

            //Локация №2



            world[13][29] = badguymodel;
            world[2][26] = badguymodel;
            world[7][29] = badguymodel;
            world[10][34] = lvlbossmodel;


            //Локация №3
            world[9][43] = lvlbossmodel;


            break;
        }
        case 3:
        {
            //Локация №1
            world[7][4] = badguymodel;
            world[13][17] = badguymodel;
            world[12][11] = badguymodel;
            world[14][4] = badguymodel;
            world[3][16] = lvlbossmodel;

            //Локация №2



            world[13][29] = badguymodel;
            world[2][26] = badguymodel;
            world[7][29] = badguymodel;
            world[6][21] = badguymodel;
            world[10][34] = lvlbossmodel;


            //Локация №3
            world[9][43] = lvlbossmodel;



            break;
        }
        }
    }

    void healthposgen()
    {


        world[13][2] = healthmodel;
        world[3][18] = healthmodel;
        world[10][21] = healthmodel;
        world[7][50] = healthmodel;

    }

    void health_detector()
    {

        if (world[playery - 1][playerx] == healthmodel || (world[playery + 1][playerx] == healthmodel) || (world[playery][playerx + 1] == healthmodel) || (world[playery][playerx - 1] == healthmodel)) { set_health_use(true); }


    }

    void setbadguylvl(int setlvl)
    {
        badguylvl1 = setlvl;
    }

    int getbadguylvl()
    {
        return badguylvl1;
    }

    void set_health_use(bool set)
    {

        set_health_use1 = set;

    }

    bool get_health_use()
    {

        return set_health_use1;
    }

    void set_badguy_count(int count)
    {
        badguy_count = count;
    }

    int get_badguy_count()
    {
        return badguy_count;
    }

    void teleport_cheat(int y, int x)
    {
        world[playery][playerx] == none;
        playery = y;
        playerx = x;
        world[playery][playerx] == playermodel;
    }

    bool get_playerpos_Y_X()
    {
    bool win = NULL;
    if ((playery==12)&&(playerx==60)){win = true;}
    if ((playery==13)&&(playerx==60)){win = true;}
    return win;
    }
};
//------------------------------------------------------------------------------------------БОЙ----------------------------------------------
class battlestats : public The_Game
{

public:
    int badguyhp, badguydamage, numberofbadguy, a = 228;
    int playerhp = 100, playerarmor = 50;
    int armorkoef = 5;
    int badguylvl, weapon;
    int score = 0;
    int key = 0;

    WorldMap map;
    picture Picture;

    void damage_to_player(int badguydamage)
    {
        playerhp = playerhp - (badguydamage);
        //cout<<endl<<"your HP = "<<playerhp<<endl<<endl;//<<"your Armor = "<<playerarmor<<endl;
    }

    void damage_to_badguy_lvl1(int playerdamage)
    {
        int badguyhp1;
        badguyhp1 = badguyhp - (playerdamage);
        badguyhp = badguyhp1;
        //cout<<endl<<"badguy HP = "<<badguyhp<<endl;//<<"badguy Armor = "<<playerarmor<<endl;
    }

    void battlefunction_upper_a()
    {
        system("cls");
        Picture.openpicture(5, false, 9);
        Sleep(2000);

    }


    void battlefunction_upper_b(int lvl)
    {
        get_battle_window();

        cout << endl;


        get_hp_all();
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~|" << "q - Обычная атака" << " " << "|w - Слабая атака" << " " << "|e - Критическая атака" << "          " << " Уровень противника - " << lvl << endl;
        cout << " " << "Вероятность попадания - |50%" << "               " << "|80%  " << "            " << "|10% " << endl;

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    }

    //-------------------------------------------------------------------------------------------------------------------------
    void battlefunction(int badguylvl1, int weapon1, int lvl)
    {
        badguylvl = badguylvl1;
        weapon = weapon1;

    shot:
        battlefunction_upper_b(lvl);
        //Sleep(1000);


        //cout<<"Уровень противника = "<<badguylvl<<endl;



        cout << " - Ход игрока: ";
        Sleep(500);
        int player_shot_status = GetRandomNumber(0, 100);
        int player_to_enemy_shot_status = GetRandomNumber(0, 100);

        switch (weapon)
        {
        case 1:
        {
            cout << endl << " - Вы использовали Сильную атаку" << endl;

            if (((player_shot_status) <= (100)) && ((player_shot_status) >= (50))) {
                cout << " - Попадание! " << endl;
                damage_to_badguy_lvl1(40);
                Sleep(1000);

                if (((player_to_enemy_shot_status) <= (100)) && ((player_to_enemy_shot_status) >= (67)))
                {
                    cout << " - Без эффекта." << endl;
                    //cout<<endl<<" id=1 "<<endl;
                    goto badguyshot;
                }
                if (((player_to_enemy_shot_status) <= (66)) && ((player_to_enemy_shot_status) >= (34)))
                {
                    cout << " - Противник замешкался " << endl;
                    Sleep(500);
                    //cout<<endl<<" id=2 "<<endl;
                    goto shot;
                }
                if (((player_to_enemy_shot_status) <= (33)) && ((player_to_enemy_shot_status) >= (0)))
                {
                    cout << " - КРИТИЧЕСКОЕ ПОПАДАНИЕ, противник умер на месте" << endl;
                    damage_to_badguy_lvl1(100);
                    //cout<<endl<<" id=3 "<<endl;
                    Sleep(2000);
                }
            }

            if (((player_shot_status) <= (50)) && ((player_shot_status) >= (1)))
            {
                cout << " - Промах! " << endl;
                Sleep(1000);
                goto badguyshot;
            }

            break;}

        case 2:
        {
            cout << endl << " - Вы использовали слабую атаку" << endl;
            if (((player_shot_status) <= (100)) && ((player_shot_status) >= (21)))
            {
                cout << " - Попадание! " << endl;
                damage_to_badguy_lvl1(10);
                Sleep(1000);

                if (((player_to_enemy_shot_status) <= (100)) && ((player_to_enemy_shot_status) >= (33)))
                {
                    cout << " - Без эффекта." << endl;
                    //cout<<endl<<" id=1 "<<endl;
                    goto badguyshot;
                }
                if (((player_to_enemy_shot_status) <= (30)) && ((player_to_enemy_shot_status) >= (0)))
                {
                    cout << " - КРИТИЧЕСКОЕ ПОПАДАНИЕ, противник умер на месте" << endl;
                    damage_to_badguy_lvl1(100);
                    //cout<<endl<<" id=3 "<<endl;
                    Sleep(2000);
                }
            }

            if (((player_shot_status) <= (20)) && ((player_shot_status) >= (1)))
            {
                cout << " - Промах! " << endl;
                Sleep(1000);
                goto badguyshot;
            }
            break;}

        case 3:
        {
            cout << endl << " - Вы пытаетесь нанести Критическую атаку" << endl;
            if (((player_shot_status) <= (100)) && ((player_shot_status) >= (90)))
            {
                cout << " - КРИТИЧЕСКОЕ ПОПАДАНИЕ, противник умер на месте" << endl;
                damage_to_badguy_lvl1(100);
                Sleep(1000);

            }
            if (((player_shot_status) <= (89)) && ((player_shot_status) >= (1)))
            {
                cout << " - Промах! " << endl;
                Sleep(1000);
                goto badguyshot;
            }
            break;}
        }

        cout << endl;
    badguyshot:

        //Sleep(1000);

        int badguy_shot_status = GetRandomNumber(0, 100);
        int badguy_to_player_shot_status = GetRandomNumber(0, 100);
        cout << " - Ход противника:";
        Sleep(500);
        switch (badguylvl)
        {
        case 1:
        {
            if (((badguy_shot_status) <= (100)) && ((badguy_shot_status) >= (40)))
            {
                cout << " - Попадание!" << endl;
                damage_to_player(get_badguy_damage());
                Sleep(1000);

                if (((badguy_to_player_shot_status) <= (100)) && ((badguy_to_player_shot_status) >= (33)))
                {
                    cout << " - Без эффекта." << endl;
                    //cout<<endl<<" id=1.1 "<<endl;
                }
                if (((badguy_to_player_shot_status) <= (32)) && ((badguy_to_player_shot_status) >= (15)))
                {
                    cout << " - От попадания вы замешкиваетесь, пропуск хода " << endl;
                    //cout<<endl<<" id=1.2 "<<endl;
                    goto badguyshot;
                }
                if (((badguy_to_player_shot_status) <= (14)) && ((badguy_to_player_shot_status) >= (0)))
                {
                    cout << " - КРИТИЧЕСКОЕ ПОПАДАНИЕ, вы умираете на месте" << endl;
                    damage_to_player(100);
                    //cout<<endl<<" id=1.3 "<<endl;
                    goto exit;
                }
            }
            if (((badguy_shot_status) <= (40)) && ((badguy_shot_status) >= (1)))
            {
                cout << " - Противник Промахулся!" << endl;
                Sleep(1000);
            }
            //Sleep(1000);
            break;
        }

        case 2:
        {
            if (((badguy_shot_status) <= (100)) && ((badguy_shot_status) >= (40)))
            {
                cout << " - Попадание!" << endl;
                damage_to_player(get_badguy_damage());
                Sleep(1000);

                if (((badguy_to_player_shot_status) <= (100)) && ((badguy_to_player_shot_status) >= (33)))
                {
                    cout << " - Без эффекта." << endl;
                    //cout<<endl<<" id=1.1 "<<endl;
                }
                if (((badguy_to_player_shot_status) <= (32)) && ((badguy_to_player_shot_status) >= (15)))
                {
                    cout << " - От попадания вы замешкиваетесь, пропуск хода " << endl;
                    //cout<<endl<<" id=1.2 "<<endl;
                    goto badguyshot;
                }
                if (((badguy_to_player_shot_status) <= (14)) && ((badguy_to_player_shot_status) >= (0)))
                {
                    cout << " - КРИТИЧЕСКОЕ ПОПАДАНИЕ, вы умираете на месте" << endl;
                    damage_to_player(100);
                    //cout<<endl<<" id=1.3 "<<endl;
                    goto exit;
                }
            }
            if (((badguy_shot_status) <= (40)) && ((badguy_shot_status) >= (1)))
            {
                cout << " - Противник Промахулся!" << endl;
                Sleep(1000);
            }
            //Sleep(1000);
            break;
        }

        case 3:
        {
            if (((badguy_shot_status) <= (100)) && ((badguy_shot_status) >= (40)))
            {
                cout << " - Попадание!" << endl;
                damage_to_player(get_badguy_damage());
                Sleep(1000);

                if (((badguy_to_player_shot_status) <= (100)) && ((badguy_to_player_shot_status) >= (33)))
                {
                    cout << " - Без эффекта." << endl;
                    //cout<<endl<<" id=1.1 "<<endl;
                }
                if (((badguy_to_player_shot_status) <= (32)) && ((badguy_to_player_shot_status) >= (15)))
                {
                    cout << " - От попадания вы замешкиваетесь, пропуск хода " << endl;
                    //cout<<endl<<" id=1.2 "<<endl;
                    goto badguyshot;
                }
                if (((badguy_to_player_shot_status) <= (14)) && ((badguy_to_player_shot_status) >= (0)))
                {
                    cout << " - КРИТИЧЕСКОЕ ПОПАДАНИЕ, вы умираете на месте" << endl;
                    damage_to_player(100);
                    //cout<<endl<<" id=1.3 "<<endl;
                    goto exit;
                }
            }
            if (((badguy_shot_status) <= (40)) && ((badguy_shot_status) >= (1)))
            {
                cout << " - Противник Промахулся!" << endl;
                Sleep(1000);
            }
            //Sleep(1000);
            break;
        }

        case 4:
        {
            if (((badguy_shot_status) <= (100)) && ((badguy_shot_status) >= (40)))
            {
                cout << " - Попадание!" << endl;
                damage_to_player(get_badguy_damage());
                Sleep(1000);

                if (((badguy_to_player_shot_status) <= (100)) && ((badguy_to_player_shot_status) >= (33)))
                {
                    cout << " - Без эффекта." << endl;
                    //cout<<endl<<" id=1.1 "<<endl;
                }
                if (((badguy_to_player_shot_status) <= (32)) && ((badguy_to_player_shot_status) >= (15)))
                {
                    cout << " - От попадания вы замешкиваетесь, пропуск хода " << endl;
                    //cout<<endl<<" id=1.2 "<<endl;
                    goto badguyshot;
                }
                if (((badguy_to_player_shot_status) <= (14)) && ((badguy_to_player_shot_status) >= (0)))
                {
                    cout << " - КРИТИЧЕСКОЕ ПОПАДАНИЕ, вы умираете на месте" << endl;
                    damage_to_player(100);
                    //cout<<endl<<" id=1.3 "<<endl;
                    goto exit;
                }
            }
            if (((badguy_shot_status) <= (40)) && ((badguy_shot_status) >= (1)))
            {
                cout << " - Противник Промахулся!" << endl;
                Sleep(1000);
            }
            //Sleep(1000);
            break;
        }

        {
            cout << "Противник пропускает ход" << endl;
            break;}
        }

    exit:
        cout << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        cout << " Новый ход через 3 секунды" << endl;

        Get_Timer(3);

    }

    //-------------------------------------------------------------------------------------------------------------------------



    void badguy_brain(int lvl)//ввод лвл, назначение хп, вывод лвл
    {
        if (lvl == 1) { set_badguy_hp(50); }
        if (lvl == 2) { set_badguy_hp(85); }
        if (lvl == 3) { set_badguy_hp(100); }
        if (lvl == 4) { set_badguy_hp(150); }

        if (lvl == 1) { set_badguy_damage(10); }
        if (lvl == 2) { set_badguy_damage(25); }
        if (lvl == 3) { set_badguy_damage(40); }
        if (lvl == 4) { set_badguy_damage(70); }
    }

    void set_badguy_brain(int set)//залупная функция
    {

        badguy_brain(set);

    }


    //damage metods

    void set_badguy_damage(int set)
    {

        badguydamage = set;

    }

    int get_badguy_damage()
    {
        return badguydamage;
    }


    //хпшные - методы

    void set_badguy_hp(int set)
    {
        badguyhp = set;
    }

    int get_badguy_hp()
    {
        return badguyhp;
    }


    int get_badguy_hp() const
    {
        return badguyhp;
    }

    void set_player_hp(int set)
    {
        playerhp = set;
    }

    int get_player_hp() const
    {
        return playerhp;
    }


    void get_hp_all()
    {
        cout << "        Ваше здоровье = " << convert_to_heart_a(get_player_hp()) << endl;
        cout << " Здроровье противника = " << convert_to_heart_b(get_badguy_hp()) << endl << endl;
        //cout<<"  "<<"Player HP = "<<get_player_hp()<<" "<<" Bad guy HP = "<<get_badguy_hp()<<endl<<endl;
    }

    string convert_to_heart_a(int heartset1)//player
    {
        string heart;
        heartset1 = get_player_hp();

        int heartset = heartset1;
        heart = " ";
        if ((heartset1 <= 100) && (heartset1 >= 91)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 90) && (heartset1 >= 81)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 80) && (heartset1 >= 71)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 70) && (heartset1 >= 61)) { heart = "|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 60) && (heartset1 >= 51)) { heart = "|\003|\003|\003|\003|\003|\003|"; }

        if ((heartset1 <= 50) && (heartset1 >= 41)) { heart = "|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 40) && (heartset1 >= 31)) { heart = "|\003|\003|\003|\003|"; }
        if ((heartset1 <= 30) && (heartset1 >= 21)) { heart = "|\003|\003|\003|"; }
        if ((heartset1 <= 20) && (heartset1 >= 11)) { heart = "|\003|\003|"; }
        if ((heartset1 <= 10) && (heartset1 >= 1)) { heart = "|\003|"; }

        return heart;
    }

    string convert_to_heart_b(int heartset1)//badguy
    {
        string heart;
        heartset1 = get_badguy_hp();
        //cout<<get_badguy_hp()<<endl;
        int heartset = heartset1;
        heart = " ";
        if ((heartset1 <= 200) && (heartset1 >= 191)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 190) && (heartset1 >= 181)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 180) && (heartset1 >= 171)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 170) && (heartset1 >= 161)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 160) && (heartset1 >= 151)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 150) && (heartset1 >= 141)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 140) && (heartset1 >= 131)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 130) && (heartset1 >= 121)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 120) && (heartset1 >= 111)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 110) && (heartset1 >= 101)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 100) && (heartset1 >= 91)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 90) && (heartset1 >= 81)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 80) && (heartset1 >= 71)) { heart = "|\003|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 70) && (heartset1 >= 61)) { heart = "|\003|\003|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 60) && (heartset1 >= 51)) { heart = "|\003|\003|\003|\003|\003|\003|"; }

        if ((heartset1 <= 50) && (heartset1 >= 41)) { heart = "|\003|\003|\003|\003|\003|"; }
        if ((heartset1 <= 40) && (heartset1 >= 31)) { heart = "|\003|\003|\003|\003|"; }
        if ((heartset1 <= 30) && (heartset1 >= 21)) { heart = "|\003|\003|\003|"; }
        if ((heartset1 <= 20) && (heartset1 >= 11)) { heart = "|\003|\003|"; }
        if ((heartset1 <= 10) && (heartset1 >= 1)) { heart = "|\003|"; }

        return heart;
    }




    //полезные фичи

    void Get_Timer(int seconds)
    {

        Sleep(1000);
        char ind;
        cout << endl;
        for (ind = 1;ind < seconds + 1;)
        {
            cout << " " << ".";
            Sleep(1000);
            ind++;
        }

    }

    void get_battle_window()
    {
        system("cls");
        Picture.openpicture(3, false, 9);
    }

    void get_winner_window()
    {
        set_score(get_score() + 1);
        set_key_count(get_key_count() + 1);

        char button;
        system("cls");
        Picture.openpicture(4, false, 9);
        cout << endl << "Нажмите любую клавишу для продолжения" << endl;
        button = _getch();
    }

    void get_game_winner_window()
    {
        char button;
        system("cls");
        Picture.openpicture(7, false, 27);
        cout << "                                        " << "         Ваш результат - " << get_score() << endl;
        //Picture.openpicture(0, true, 0);
        Sleep(3000);
        cout << "                                        " << "Нажмите любую клавишу для продолжения" << endl;
        button = _getch();
    }

    void get_lore1_window()
    {
        char button;
        system("cls");
        Picture.openpicture(8, true, 25);

        Sleep(3000);
        cout << "                                        " << "Нажмите любую клавишу для продолжения" << endl;
        button = _getch();

    }

    int GetRandomNumber(int min, int max)
    {
        // Установить генератор случайных чисел
        srand(time(NULL));

        // Получить случайное число - формула
        int num = min + rand() % (max - min + 1);

        return num;
    }

    void set_score(int set)
    {
        score = set;
    }

    int get_score()
    {
        return score;
    }


    void set_key_count(int set)
    {
        key = set;
    }

    int get_key_count()
    {
        return key;
    }



    void you_die()
    {
        system("cls");
        Picture.openpicture(2, false, 9);
        Sleep(6000);
    }

};
//------------------------------------------------------------------------------------------Режим игры---------------------------------------
class gamemode : public The_Game
{
public:
    WorldMap map;
    string menumatrix[5][5] = {
    {"  "," ","  ","  "},
    {"    ","  ","Играть","  "},
    {"   "," ","Настройки","  "},
    {"     "," ","Выход","  "} };
    int menuposx1 = 1, menuposy1 = 1;
    int menuposx2 = 3, menuposy2 = menuposy1;
    int settingsposx = 1, settingsposy = 1;

    string settingsmatrix[3][5] = {
    {"  "," ","  ","  "},
    {"  "," "," ","Количество противников "} };

    gamemode()//_______________________________________________________________________________________________________Normal Game________________
    {
        The_Game Basic;
        WorldMap Play;
        battlestats battle;
        picture Picture;
        char menu = ' ';
        char exitf = ' ';
        char settings = ' ';
    start2:
        setcursorstartpos();

    startmenu:
        menu = _getch();
        switch (menu)
        {
        case 'w':
        {setupmenu();
        break;
        }
        case 's':
        {
            setdownmenu();
            break;
        }
        case 'e':
        {
            if (menuposy1 == 1) { goto play; }
            if (menuposy1 == 2) { goto Settings; }
            if (menuposy1 == 3) { goto exit2; }
            break;}
        }

        goto startmenu;


    Settings:

        setsettingscursorstartpos();
        getsettings();
        cout << "                                                      -" << endl;
        cout << "                                                     |" << map.get_badguy_count() << "|" << endl;
        cout << "                                                      - " << endl;
        settings = _getch();


        switch (settings)
        {
        case 'a':
        {set_settings_left();
        break;
        }
        case 'd':
        {
            set_settings_right();
            break;
        }
        case 'e':
        {
            if (map.get_badguy_count() == 1) { goto start2; }
            if (map.get_badguy_count() == 2) { goto start2; }
            if (map.get_badguy_count() == 3) { goto start2; }
            break;}
        }
        goto Settings;

    play:

        battle.get_lore1_window();
        battle.set_player_hp(100);

        Play.movestartpos();
        Play.badguyposgen(map.get_badguy_count());
        Play.healthposgen();


    playgame:
        if (Play.getbattleisstart() == 1) { goto battleishere; }
        Play.maprefresh();

        //Picture.openpicture(6,false);
        cout << endl
            << "   Управление: " << "\t" << "\t" << "   Легенда: " << endl
            << " - w - Движение вверх " << "\t" << "| " << playermodel << " - Игрок" << endl
            << " - a - Движение влево " << "\t" << "| " << badguymodel << " - Враг " << endl
            << " - s - Движение вниз " << "\t" << "| " << lvlbossmodel << " - Босс локации " << endl
            << " - d - Движение вправо " << "\t" << "| " << healthmodel << " - Аптечка" << endl
            << " - z - Выход в меню " << "\t" << "| " << endl;

        if (battle.get_score() == 5) { goto winner; }

        cout << endl << "~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~" << endl;
        cout << endl << " - Здоровье - " << battle.convert_to_heart_a(battle.get_player_hp()) << endl;

        cout << endl << " - Количество ключей - " << battle.get_key_count() << " | Счет - " << battle.get_score() << endl;
        //---------------------------------------------------------------------------------------------
        //Sleep(200);
        move = _getch();


        switch (move) {
        case 'w':
        {Play.moveup(battle.get_score(), battle.get_key_count());
        break;}
        case 'a':
        {Play.moveleft(battle.get_score(), battle.get_key_count());
        break;}

        case 's':
        {Play.movedown(battle.get_score(), battle.get_key_count());
        break;}
        case 'd':
        {Play.moveright(battle.get_score(), battle.get_key_count());
        break;
        }
        case 'z':
        {goto start2;
        break;
        }

        case '*':
        {
            goto teleport_cheat;
            break;
        }

        default:
        {
            cout << "Неверный ввод" << endl;
            Sleep(1000);
        }
        }

        if (Play.get_door_detector_status() == true)
        {
            Play.set_door_detector_status(NULL);
            battle.set_key_count(battle.get_key_count() - 1);
        }

        if (Play.get_health_use() == true)
        {
            Play.set_health_use(NULL);
            battle.set_player_hp(100);
        }

        if (Play.get_playerpos_Y_X() == true)
        {
        goto winner;
        }

        goto playgame;

    teleport_cheat:

        cout << "введите коодинаты для телепорта Y,X" << endl;
        int x, y;
        cin >> y >> x;
        Play.teleport_cheat(y, x);
        //-----------------------------------------------------------------------------SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
        goto playgame;






    battleishere://старт батла
        Play.setbadguylvl(Play.getbadguylvl());//назначение уровня badguy'а
        battle.set_badguy_brain(Play.getbadguylvl());
        battle.battlefunction_upper_a();
        battle.battlefunction_upper_b(Play.getbadguylvl());//первоначальный вывод параметров хп, с подгрузкой хп под уровень


        cout << endl;
        goto nextpos;

    battlestart://возврат в цикл боя после окончания внизу

        battle.battlefunction_upper_b(Play.getbadguylvl());

    nextpos:

        cout << "Аттакуйте!" << endl;
        Battle = _getch();

        switch (Battle) {
        case 'q':
        {battle.battlefunction(Play.getbadguylvl(), 1, Play.getbadguylvl());
        break;}

        case 'w':
        {battle.battlefunction(Play.getbadguylvl(), 2, Play.getbadguylvl());
        break;}

        case 'e':
        {battle.battlefunction(Play.getbadguylvl(), 3, Play.getbadguylvl());
        break;}




        case 'r':
        {  battle.get_winner_window();
        Play.setbattleisstart(-1);
        break;}

        case 'l':
        {
            battle.damage_to_player(100);
            //Play.setbattleisstart(-1);
            break;}

        case 'k':
        {
            battle.damage_to_badguy_lvl1(100);
            //Play.setbattleisstart(-1);
            break;}

        }

        if (battle.get_player_hp() <= 0) { goto exit; }
        if (battle.get_badguy_hp() <= 0) { Play.setbattleisstart(-1); }
        if (Play.getbattleisstart() == -1) { battle.get_winner_window(); goto playgame; }

        goto battlestart;


    exit:

        battle.you_die();
        goto exit2;

    exit2:
        system("cls");
        Picture.openpicture(6, false, 9);

        exitf = _getch();

        switch (exitf)
        {
        case 'y':
        {
            break;
        }
        case 'n':
        {
            goto start2;
        }

        }

        goto exit3;

    winner:
        battle.get_game_winner_window();
        goto start2;


    exit3:

        cout << endl;
        //getchar();
    }
    //----------------------------------------------------------------------------НАЧАЛО ИГРЫ
    gamemode(char d)//___________________________________________________________________________________________________Debag Menu________________
    {
        WorldMap Play;
        battlestats battle;
        picture Picture;

    start:


        if (Play.getbattleisstart() == 1) { goto battleishere; }

        cout << "w - move.up " << endl;
        cout << "s - move.down " << endl;
        cout << "a - move.left " << endl;
        cout << "d - move.right " << endl;
        cout << "r - map.refresh " << endl;
        cout << "g - battle.get_game_winner_window " << endl;
        cout << "i - move.startpos " << endl;
        cout << "e - badboy.posgen " << endl;
        cout << "h - goto battleishere: " << endl;






        cout << "battleison " << Play.getbattleisstart() << endl;
        move = _getch();;
        cout << "press " << move << " " << endl;
        switch (move) {
        case 'w':
        {Play.moveup(battle.get_score(), battle.get_key_count());
        break;}
        case 'a':
        {Play.moveleft(battle.get_score(), battle.get_key_count());
        break;}

        case 's':
        {Play.movedown(battle.get_score(), battle.get_key_count());
        break;}
        case 'd':
        {Play.moveright(battle.get_score(), battle.get_key_count());
        break;
        }
        case 'g':
        {battle.get_game_winner_window();
            break;
        }
        case 'r':
        {Play.maprefresh();
        break;
        }
        case 'i':
        {Play.movestartpos();
        break;
        }
        case 'h':
        {
            goto battleishere;
            Play.setbattleisstart(1);
            break;
        }
        case 'e':
        {Picture.openpicture(9,false,30);
        break;
        }
        }
        goto start;
    battleishere:
        //system("cls");
        cout << "q - bedguy.lvl1.stats " << endl;
        cout << "w - player.stats " << endl;
        cout << "e - battle.function " << endl;
        cout << "r - setbattleisstart = 5 " << endl;
        cout << "t - getbattleisstart " << endl;
        cout << "h - goto start: " << endl;
        cout << "c - GetRandomNumber " << endl;
        Battle = _getch();
        switch (Battle) {
        case 'q':
        {//battle.badguylvl1stats();
            cout << "battleison " << Play.getbattleisstart() << endl;
            break;}
        case 'w':
        {
            //battle.damage_to_player();
            cout << "battleison " << Play.getbattleisstart() << endl;
            break;}
        case 'e':
        { //battle.battlefunction();
            cout << "battleison " << Play.getbattleisstart() << endl;
            break;
        }
        case 'r':

        {
            battle.get_hp_all();
            battle.damage_to_badguy_lvl1(40);
            battle.get_hp_all();

            break;
        }

        case 't':
        { Play.getbattleisstart();
        cout << Play.getbattleisstart() << endl;
        break;
        }
        case 'h':
        {
            Play.setbattleisstart(-1);
            goto start;
            break;
        }
        case 'c':
        {
            cout << endl << battle.GetRandomNumber(0, 100) << endl << endl;
            goto start;
            break;
        }
        }

        int stop;
        if (Play.getbattleisstart() == -1) { goto start; }
        goto battleishere;
    }

    void setcursorstartpos()
    {
        menumatrix[menuposy1][menuposx1] = rightmodel;
        menumatrix[menuposy2][menuposx2] = leftmodel;
        getmenu();


    }
    void setupmenu()
    {
        menumatrix[menuposy1][menuposx1] = none;
        menumatrix[menuposy2][menuposx2] = none;
        menuposy1 = menuposy1 - 1;
        menuposy2 = menuposy2 - 1;
        testmenupos();
        menumatrix[menuposy1][menuposx1] = rightmodel;
        menumatrix[menuposy2][menuposx2] = leftmodel;
        getmenu();
    }
    void setdownmenu()
    {
        menumatrix[menuposy1][menuposx1] = none;
        menumatrix[menuposy2][menuposx2] = none;
        menuposy1 = menuposy1 + 1;
        menuposy2 = menuposy2 + 1;
        testmenupos();
        menumatrix[menuposy1][menuposx1] = rightmodel;
        menumatrix[menuposy2][menuposx2] = leftmodel;
        getmenu();
    }
    void testmenupos()
    {
        if (menuposy1 == 0) { menuposy1 = 1; }//up
        if (menuposy1 == 4) { menuposy1 = 3; }//down
        if (menuposy2 == 0) { menuposy2 = 1; }//up
        if (menuposy2 == 4) { menuposy2 = 3; }//down
    }
    void getmenu()//----------------------------------------------------------------------------------Проблемное место
    {
        system("cls");
        picture pict;
        pict.openpicture(1, true, 9);
        int i, j;
        for (i = 0; i < 4; i++)
        {                            // внешний цикл отвечает за перебор строк
            for (j = 0; j < 4; j++) // цикл для вывода элементов строки
                if(j==2||j==3){cout <<" "<< menumatrix[i][j];}
                else{cout <<"                        "<< menumatrix[i][j];}
            cout << " " << endl<<endl; // после вывода элементов j-й строки делаем переход на новую строку
        }
    }

    void setsettingscursorstartpos()
    {
        settingsmatrix[1][1] = leftmodel;
        settingsmatrix[1][4] = rightmodel;
        int badguy_count;
    }

    void set_settings_right() {
        map.set_badguy_count(map.get_badguy_count() + 1);
        test_settings_count();
    }
    void set_settings_left() {
        map.set_badguy_count(map.get_badguy_count() - 1);
        test_settings_count();
    }

    void test_settings_count()
    {
        if (map.get_badguy_count() == 4) { map.set_badguy_count(3); }
        if (map.get_badguy_count() == 0) { map.set_badguy_count(1); }
    }
    void getsettings()//----------------------------------------------------------------------------------Проблемное место
    {
        system("cls");
        picture pict;
        pict.openpicture(1, true, 9);
        int i, j;
        cout << "                              " << "|e - Подтверждение |" << " a - Отбавить |" << " d - Прибавить|" << endl;
        for (i = 0; i < 2; i++)
        {                            // внешний цикл отвечает за перебор строк
            for (j = 0; j < 5; j++) // цикл для вывода элементов строки
                if(j==0){cout <<"                                    "<< settingsmatrix[i][j];}
                else{cout <<" "<< settingsmatrix[i][j];}
            cout << " " << endl; // после вывода элементов j-й строки делаем переход на новую строку
        }
    }





};
//------------------------------------------------------------------------------------------main---------------------------------------------
int main()
{

    setlocale(LC_ALL, "RUS");
start:
    system("cls");
    char gamevariant = ' ';
    picture vivod;
    vivod.openpicture(1, false, 14);
    //cout<<endl;

    cout <<"888888888888888888888888             "<< "Нажмите любую кнопку для продолжения..." <<"               8888888888888888888888888888"<< endl;
    vivod.openpicture(0, false, 14);
    gamevariant = _getch();

    switch (gamevariant)
    {
    default:
    {
        gamemode();
        break;
    }
    case '*':
    {
        gamemode('e');
        break;
    }
    //default:{cout << "Проверьте раскладку";Sleep(1000);goto start;}
    Sleep(11000);

    }
}