/* ������:
1: �������� ����, ����� ���� X
2: ������� ���������� ����� ����
3: ������� �����
4: ������� ���������� (������ ���������� �����)
5: ������� ��������������� ������� ����
6: ������������ ����������� �����
7: ������� ���������, �������� ��������
8: ���������� ����� �� ���������
���������� ��: ������� ����� Lvl ������, ��������: �� �������� ����������
*/
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
    char playermodel='\002';
    char badguymodel = '\001';
    char inputmodel ='\020';
    char none = ' ';
    int badguylvl = 5;
    int heartset1 = 95;

    char world[12][13];
    int playerx=12,playery=12;

    char move = ' ';
    char Battle=' ';

};
//-----------------------------------------------------------------------------------------��������------------------------------------------
class picture : public The_Game
{
int idpic=-1;
public:
void openpicture(int idpic)
{
    const int len = 150, strings = 8;//len -����� strings ������
	const char ch = '\n';
	char mass[len][strings];

    string picarray[5]={" ","Picture1.txt","Picture2.txt","Picture3.txt"};
	ifstream fs(picarray[idpic]);


	for(int r = 0; r<strings; r++)
	{
		fs.getline(mass[r], len-1); //��������� ������ � ������
		cout << mass[r] << endl; //������ ������ �� �������
	}
	fs.close(); //��������� ����
    cout<<"~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~"<<endl<<endl;
}
};
//------------------------------------------------------------------------------------------��������� �����----------------------------------
class WorldMap : public The_Game {
public:
int i, j;
int badguycount;
int badguymatrix[10][2];
int battleisstart = 5;

void mapcreate(){
// -----------------------------------------------------------------------�������� ����
    for (i = 0; i < 12; i++)//���������� ����� (�������)
     {

        for (j = 0; j < 13; j++){
        if (world[0][j])    {world[0][j]='_'; }//������� �������
        if (world[10][j])   {world[10][j]='_'; }//������� �������
        if (world[i][0])    {world[i][0]='|';}//����� �������
        if (world[i][11])   {world[i][11]='|';}//������ �������
        world[i][j]=' ';
        cout << endl;


        }
    }
    maprefresh();
}

void maprefresh() {
//----------------------------------------------------------------------------���������� �����
    system("cls");
    for (i = 0; i < 11; i++)
    {                            // ������� ���� �������� �� ������� �����
        for (j = 0; j < 13; j++) // ���� ��� ������ ��������� ������
            cout << world[i][j];
        cout << endl; // ����� ������ ��������� j-� ������ ������ ������� �� ����� ������
    }
    cout<<"pX= "<<playerx<<"pY= "<<playery<<endl;
    if ((world[playery-1][playerx]==badguymodel)||(world[playery][playerx+1]==badguymodel)||(world[playery+1][playerx]==badguymodel)||(world[playery][playerx-1]==badguymodel))
    {setbadguylvl(1); setbattleisstart(1);}else{setbattleisstart(0);}
    cout<< "battleisstart "<<battleisstart<<endl;
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
world[5][5]=playermodel;
world[playerx][playery]=none;
playerx=5,playery=5;

maprefresh();
}

void moveup()//y+
{
world[playery][playerx]=none;
playery=playery-1;
checkposition();
world[playery][playerx]=playermodel;
maprefresh();
}

void movedown()//y+
{

world[playery][playerx]=none;
playery=playery+1;
checkposition();
world[playery][playerx]=playermodel;
maprefresh();
}

void moveleft()//x-
{

world[playery][playerx]=none;
playerx=playerx-1;
checkposition();
world[playery][playerx]=playermodel;
maprefresh();
}

void moveright()//x+
{
world[playery][playerx]=none;
playerx=playerx+1;
checkposition();
world[playery][playerx]=playermodel;
maprefresh();
}

void checkposition()
{
if (playery==0){playery=1;}//up
if (playery==10){playery=9;}
if (playerx==11){playerx=10;}
if (playerx==0){playerx=1;}

}

void badboyposgen()
{
badguycount=rand()%5;
for (i=0;i<badguycount;i++)
    {
    for(j=0;j<2;j++)
    {
        badguymatrix[i][j]=rand()%10;
    }
    }

cout<<"���������� ������ ������ "<<badguycount<<endl;

for (i=0;i<badguycount;i++)
{
    world[badguymatrix[i][0]][badguymatrix[i][1]]=badguymodel;
}
maprefresh();
}

void setbadguylvl(int setlvl)
{
 badguylvl = setlvl;
}

int getbadguylvl()
{
return badguylvl;
}



};
//------------------------------------------------------------------------------------------���----------------------------------------------
class battlestats : public The_Game
{

public:
int badguyhp = 85,badguyarmor = 25,numberofbadguy,a=228;
int playerhp= 100,playerarmor= 50;
int armorkoef = 5;
int badguylvl = 5;


WorldMap map;
picture Picture;

void damage_to_player(int badguydamage)
{
playerhp=playerhp-(badguydamage);
//cout<<endl<<"your HP = "<<playerhp<<endl<<endl;//<<"your Armor = "<<playerarmor<<endl;
}

void damage_to_badguy_lvl1(int playerdamage)
{
badguyhp=badguyhp-(playerdamage);
//cout<<endl<<"badguy HP = "<<badguyhp<<endl;//<<"badguy Armor = "<<playerarmor<<endl;
}

void battlefunction()
{
int damage=30;
shot:

badguylvl = map.getbadguylvl();
int temp;

if (badguylvl==1){damage=10;}
if (badguylvl==2){damage=25;}
if (badguylvl==3){damage=40;}
if (badguylvl==4){damage=70;}

cout<<" - �� ��������� � ����������"<<endl;

int player_shot_status = rand()%100;
int player_to_enemy_shot_status = rand()%100;

if (player_shot_status>60)
{
    cout<<" - ���������!"<<endl;
    if (((player_to_enemy_shot_status)<(100))&&((player_to_enemy_shot_status)>(20))){cout<<endl<<" - ��������� �������� � ����� "<<endl; damage_to_badguy_lvl1(25); goto badguyshot;}
    if (((player_to_enemy_shot_status)<(20))&&((player_to_enemy_shot_status)>(5))){cout<<endl<<" - ��������� ���������� "<<endl; damage_to_badguy_lvl1(25); temp = badguylvl; map.setbadguylvl(0);   }
    if (((player_to_enemy_shot_status)<(4))&&((player_to_enemy_shot_status)>(0))){cout<<endl<<" - ����������� ���������, ��������� ���� �� �����"<<endl;damage_to_badguy_lvl1(100); Sleep(2000);}
}else
{
    cout<<" - ������!"<<endl;
    goto badguyshot;
}






badguyshot:
int badguy_shot_status= rand()%100;
int badguy_to_player_shot_status= rand()%100;

switch (badguylvl)
{
case 1:
{
if (badguy_shot_status>70)
{
    cout<<" - ���������!"<<endl;
    damage_to_player(damage);
    if (((badguy_to_player_shot_status)<(100))&&((badguy_to_player_shot_status)>(31))){cout<<endl<<" "<<endl;}
    if (((badguy_to_player_shot_status)<(30))&&((badguy_to_player_shot_status)>(11))){cout<<endl<<" - �� ��������������, ������� ���� "<<endl; goto badguyshot;}
    if (((badguy_to_player_shot_status)<(10))&&((badguy_to_player_shot_status)>(0))){cout<<endl<<" - ����������� ���������, �� �������� �� �����"<<endl; damage_to_player(100); goto shot;}
}else
{
    cout<<" - ��������� ����������!"<<endl;
}
break;
}




case 2:
{
cout<<endl<<"��������� 2"<<endl<<endl;
if (badguy_shot_status==1)
{
    cout<<" - ���������!"<<endl;
    damage_to_player(damage);
    if (((badguy_to_player_shot_status)<(100))&&((badguy_to_player_shot_status)>(39))){cout<<endl<<" - ��������� ������������� "<<endl; goto shot;}
    if (((badguy_to_player_shot_status)<(100))&&((badguy_to_player_shot_status)>(39))){cout<<endl<<" - ����������� ���������, �� �������� �� �����"<<endl; damage_to_player(100); goto shot;}
}else
{
cout<<" - ��������� ����������!"<<endl;
}
break;
}

case 3:
{
cout<<endl<<"��������� 3"<<endl<<endl;
if (badguy_shot_status==1)
{
    cout<<" - ���������!"<<endl;
    damage_to_player(damage);
    if (((badguy_to_player_shot_status)<(100))&&((badguy_to_player_shot_status)>(39))){cout<<endl<<" - ��������� ������������� "<<endl; goto shot;}
    if (((badguy_to_player_shot_status)<(100))&&((badguy_to_player_shot_status)>(39))){cout<<endl<<" - ����������� ���������, �� �������� �� �����"<<endl; damage_to_player(100); goto shot;}
}else
{
    cout<<" - ��������� ����������!"<<endl;
}
break;
}

case 4:
{
if (badguy_shot_status==1)
{
    cout<<" - ���������!"<<endl;
    damage_to_player(damage);
    if (((badguy_to_player_shot_status)<(100))&&((badguy_to_player_shot_status)>(39))){cout<<endl<<" - ��������� ������������� "<<endl; goto shot;}
    if (((badguy_to_player_shot_status)<(100))&&((badguy_to_player_shot_status)>(39))){cout<<endl<<" - ����������� ���������, �� �������� �� �����"<<endl; damage_to_player(100); goto shot;}
}else
{
    cout<<" - ��������� ����������!"<<endl;
}
break;
}

case 0:
{
    cout<<"��������� ���������� ���"<<endl;
    break;}
}
map.setbadguylvl(temp);
temp=8;
//getchar();
}

void get_hp_all()
{
    cout<<" Player HP = "<<convert_to_heart(get_player_hp())<<endl;
    cout<<" Badguy HP = "<<convert_to_heart1(get_badguy_hp())<<endl<<endl;
    cout<<"  "<<"Player HP = "<<get_player_hp()<<" "<<" Bad guy HP = "<<get_badguy_hp()<<endl<<endl;
}

void set_badguy_hp(int set)
{
 badguyhp = set;
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

void get_battle_window()
{
system("cls");
Picture.openpicture(3);
}

string convert_to_heart(int heartset1)
{
string heart;
heartset1=get_player_hp();
int heartset=heartset1;
heart = "none";
if ((this->heartset1<99)&&(this->heartset1>91)){heart="|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|";}
if ((this->heartset1<90)&&(this->heartset1>81)){heart="|\003|\003|\003|\003|\003|\003|\003|\003|\003";}
if ((this->heartset1<80)&&(this->heartset1>71)){heart="\003\003\003\003\003\003\003\003";}
if ((this->heartset1<70)&&(this->heartset1>61)){heart="\003\003\003\003\003\003\003";}
if ((this->heartset1<60)&&(this->heartset1>51)){heart="\003\003\003\003\003\003";}

if ((this->heartset1<50)&&(this->heartset1>41)){heart="\003\003\003\003\003";}
if ((this->heartset1<40)&&(this->heartset1>31)){heart="\003\003\003\003";}
if ((this->heartset1<30)&&(this->heartset1>21)){heart="\003\003\003";}
if ((this->heartset1<20)&&(this->heartset1>11)){heart="\003\003";}
if ((this->heartset1<10)&&(this->heartset1>1)){heart="\003";}

return heart;
}

string convert_to_heart1(int heartset1)
{
string heart;
heartset1=get_player_hp();
int heartset=heartset1;
heart = "none";
if (this->heartset1<99){heart="|\003|\003|\003|\003|\003|\003|\003|\003|\003|\003|100";}
if (this->heartset1<90){heart="|\003|\003|\003|\003|\003|\003|\003|\003|\003|90";}
if (this->heartset1<80){heart="\003\003\003\003\003\003\003\003";}
if (this->heartset1<70){heart="\003\003\003\003\003\003\003";}
if (this->heartset1<60){heart="\003\003\003\003\003\003";}

if (this->heartset1<50){heart="\003\003\003\003\003";}
if (this->heartset1<40){heart="\003\003\003\003";}
if (this->heartset1<30){heart="\003\003\003";}
if (this->heartset1<20){heart="\003\003|20";}
if (this->heartset1<10){heart="\003|10";}

return heart;
}

};
//------------------------------------------------------------------------------------------����� ����---------------------------------------
class gamemode : public The_Game
{
public:
string menumatrix[5][5] = {
{"  "," ","  ","  "},
{"  "," ","Play","  "},
{"  "," ","Settings","  "},
{"  "," ","Exit","  "}};
int menuposx=1,menuposy=1;

gamemode()//_______________________________________________________________________________________________________Normal Game________________
{
The_Game Basic;
WorldMap Play;
battlestats battle;
picture Picture;
char menu=' ';
setcursorstartpos();

startmenu:
menu=getch();
switch (menu)
{
case 'w':

setupmenu();
{break;}
case 's':

setdownmenu();
{break;}
case 'e':
if (menuposy==1){goto play;}
//if (menuposy==2){goto Settings;}
if (menuposy==3){goto exit;}
{break;}

}
goto startmenu;

play:

Play.mapcreate();
Play.movestartpos();
Play.badboyposgen();


playgame:
if (Play.getbattleisstart() == 1){goto battleishere;}
Play.maprefresh();
cout<<"w - move.up "<<"s - move.down "<<"a - move.left "<<"d - move.right "<<endl;
move = _getch();


switch (move)  {
case 'w' :
     {Play.moveup();
     break;}
case 'a' :
    {Play.moveleft();
    break;}

case 's' :
    {Play.movedown();
    break;}
case 'd' :
    {Play.moveright();
    break;
    }
}
goto playgame;


    battleishere:
    battle.get_battle_window();

    battlestart:
    cout<<"������� ���������� = "<<Play.getbadguylvl()<<endl<<endl;
    battle.get_hp_all();
    cout<<"e - ������� ���������� "<<endl;
    Play.setbadguylvl(Play.getbadguylvl());
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
    cout<<endl<<"Player HP = "<<battle.get_player_hp()<<" Bad guy HP = "<<battle.get_badguy_hp()<<endl<<endl;


    Battle = _getch();

switch (Battle)  {
    case 'e':
     {battle.battlefunction();
     break;}

    case 'r':
     {Play.setbattleisstart(-1);
     break;}

    }

    if ((battle.get_player_hp() < 0)||(battle.get_badguy_hp()<0)){Play.setbattleisstart(-1);}

    if (Play.getbattleisstart() == -1){goto playgame;}

    goto battleishere;


    exit:
    string a="   ������� �� ���� ;)";
    cout<<endl<<a<<endl;
    Sleep(1000);
}
//----------------------------------------------------------------------------������ ����
gamemode(char d)//___________________________________________________________________________________________________Debag Menu________________
{
    WorldMap Play;
    battlestats battle;

start:


if (Play.getbattleisstart() == 1){goto battleishere;}

cout<<"w - move.up "<<endl;
cout<<"s - move.down "<<endl;
cout<<"a - move.left "<<endl;
cout<<"d - move.right "<<endl;
cout<<"r - map.refresh "<<endl;
cout<<"g - map.create "<<endl;
cout<<"i - move.startpos "<<endl;
cout<<"e - badboy.posgen "<<endl;
cout<<"h - goto battleishere: "<<endl;
cout<< "battleison "<<Play.getbattleisstart()<<endl;
move = _getch();;
cout<<"press "<<move<<" "<<endl;
switch (move)  {
case 'w' :
     {Play.moveup();
     break;}
case 'a' :
    {Play.moveleft();
    break;}

case 's' :
    {Play.movedown();
    break;}
case 'd' :
    {Play.moveright();
    break;
    }
case 'g' :
    {Play.mapcreate();
    break;
    }
case 'r' :
    {Play.maprefresh();
    break;
    }
case 'i' :
    {Play.movestartpos();
    break;
    }
case 'h' :
    {
    goto battleishere;
    Play.setbattleisstart(1);
    break;
    }
case 'e' :
    {Play.badboyposgen();
    break;
    }
}
goto start;
    battleishere:
    //system("cls");
    cout<<"q - bedguy.lvl1.stats "<<endl;
    cout<<"w - player.stats "<<endl;
    cout<<"e - battle.function "<<endl;
    cout<<"r - setbattleisstart = 5 "<<endl;
    cout<<"t - getbattleisstart "<<endl;
    cout<<"h - goto start: "<<endl;
    Battle = _getch();
switch (Battle)  {
    case 'q':
     {//battle.badguylvl1stats();
     cout<< "battleison "<<Play.getbattleisstart()<<endl;
     break;}
    case 'w':
    {
        //battle.damage_to_player();
        cout<< "battleison "<<Play.getbattleisstart()<<endl;
     break;}
    case 'e':
    { //battle.battlefunction();
    cout<< "battleison "<<Play.getbattleisstart()<<endl;
    break;
    }
    case 'r':
    { battle.get_player_hp();
    cout<<battle.get_player_hp()<<endl;
    break;
    }

    case 't':
    { Play.getbattleisstart();
    cout<<Play.getbattleisstart()<<endl;
    break;
    }
    case 'h' :
    {
    Play.setbattleisstart(-1);
    goto start;
    break;
    }
    }

    int stop;
    if (Play.getbattleisstart() == -1){goto start;}
    goto battleishere;
}

void setcursorstartpos()
{
menumatrix[menuposy][menuposx] = inputmodel;
getmenu();


}
void setupmenu()
{
menumatrix[menuposy][menuposx] = none;
menuposy=menuposy-1;
testmenupos();
menumatrix[menuposy][menuposx] = inputmodel;
getmenu();
}
void setdownmenu()
{
menumatrix[menuposy][menuposx] = none;
menuposy=menuposy+1;
testmenupos();
menumatrix[menuposy][menuposx] = inputmodel;
getmenu();
}
void testmenupos()
{
if (menuposy==0){menuposy=1;}//up
if (menuposy==4){menuposy=3;}//down
}
void getmenu()//----------------------------------------------------------------------------------���������� �����
{
    system("cls");
    picture pict;
    pict.openpicture(1);
    int i,j;
    for (i = 0; i < 4; i++)
    {                            // ������� ���� �������� �� ������� �����
        for (j = 0; j < 4; j++) // ���� ��� ������ ��������� ������
            cout << menumatrix[i][j];
        cout <<" "<< endl; // ����� ������ ��������� j-� ������ ������ ������� �� ����� ������
    }
}



};
//------------------------------------------------------------------------------------------main---------------------------------------------
int main()
{

setlocale(LC_ALL, "RUS");

char gamevariant=' ';
    picture vivod;
    vivod.openpicture(1);
//cout<<endl;

cout<<"������� ����: q- Normal Game | e- debug"<<endl;
gamevariant = _getch();

switch (gamevariant)
{
case 'q':
{
    gamemode();
    break;
}
case 'e':
{
    gamemode('e');
    break;
}
Sleep(11000);

}
}