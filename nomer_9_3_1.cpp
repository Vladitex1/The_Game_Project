#include <iostream>
#include <math.h>
#include <stdio.h>
#include <locale>
using namespace std;

class ChessPiece {
protected:
    string color,GetColor;  // Цвет фигуры
    string name;
    int x,y;
public:
    // Конструктор по умолчанию
    ChessPiece() {
        color = "";
    }

    // Конструктор с параметрами
    ChessPiece(string color) {
        this-> color;
        GetColor = color;
    }

    // Методы для работы с полем "цвет"
    void getColor() {
        cout << GetColor;
    }

    // виртуальный метод move
    virtual void move() = 0;
};




// Производный класс Фигура
class Figure : public ChessPiece {
private:
    string name;  // Название фигуры
    int x1,x; // Координата по оси x
    int y1,y;  // Координата по оси y

public:
    // Конструктор по умолчанию
    Figure() {
        name = "Фигура";
        x = 0;
        y = 0;
    }

    // Конструктор с параметрами
    Figure(string name,string color, int x, int y) : ChessPiece(color) {
        this->name = name;
        this->x = x;
        this->y = y;
    }

    // Метод move для вывода фигуры
    void move() {
        cout << name << " переместился на координаты (" << x << ", " << y << ")" << endl;
    }
};



int main() {
    setlocale(LC_ALL, "RUS");

    //Создание фигуры:
    int switcher,x,y;
    string name,color;
    cout<<"выберите название фигуры: "<<endl;
    cout<<"1 - Пешка"<<endl<<"2- Конь"<<endl<<"3- Слон"<<endl<<"4- Ладья"<<endl<<"5- Ферзь (Королева)"<<endl<<"6- Король"<<endl;

    cin>>switcher;
    switch (switcher)  {
    case 1:
    {
        name = "пешка";
         break;
    }

    ////////////////////////////////////
    case 2:
    {
        name = "Конь";
         break;
    }

    ////////////////////////////////////
    case 3:
    {
        name = "Слон";
         break;
    }

    ////////////////////////////////////
    case 4:
    {
        name = "Ладья";
         break;
    }

    ////////////////////////////////////
    case 5:
    {
        name = "Ферзь (Королева)";
         break;
    }

    ////////////////////////////////////
    case 6:
    {
        name = "Король";
         break;
    }

    ////////////////////////////////////
    default :
     {
         break;
    }
    }


    cout<<"ВВедите цвет фигуры:"<<endl<<"1-белый"<<endl<<"2-черный"<<endl;

    cin>>switcher;

    switch (switcher)  {
    case 1:
    {
        color = "Белый";
         break; 
    }
     case 2:
    {
        color = "Черный";
         break;
    }
    default :
     {
         break;
    }
    }


    cout<<"введите коорданаты фигуры"<<endl;
    cout<<"X: "<<endl;
    cin>>x;
    cout<<"Y: "<<endl;
    cin>>y;
    // Вывод информации о фигурах
    Figure figure(name,color,x,y);

    figure.getColor();//вывод цвета фигуры
    cout<<" ";
    figure.move();//вывод позиции фигуры


    cout<< endl;

 int exit;
 cin >> exit;
    return 0;
}