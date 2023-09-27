#include <iostream>
#include <math.h>
#include <stdio.h>
#include <locale>
using namespace std;

class ChessPiece {
protected:
    string color,GetColor;  // ���� ������
    string name;
    int x,y;
public:
    // ����������� �� ���������
    ChessPiece() {
        color = "";
    }

    // ����������� � �����������
    ChessPiece(string color) {
        this-> color;
        GetColor = color;
    }

    // ������ ��� ������ � ����� "����"
    void getColor() {
        cout << GetColor;
    }

    // ����������� ����� move
    virtual void move() = 0;
};




// ����������� ����� ������
class Figure : public ChessPiece {
private:
    string name;  // �������� ������
    int x1,x; // ���������� �� ��� x
    int y1,y;  // ���������� �� ��� y

public:
    // ����������� �� ���������
    Figure() {
        name = "������";
        x = 0;
        y = 0;
    }

    // ����������� � �����������
    Figure(string name,string color, int x, int y) : ChessPiece(color) {
        this->name = name;
        this->x = x;
        this->y = y;
    }

    // ����� move ��� ������ ������
    void move() {
        cout << name << " ������������ �� ���������� (" << x << ", " << y << ")" << endl;
    }
};



int main() {
    setlocale(LC_ALL, "RUS");

    //�������� ������:
    int switcher,x,y;
    string name,color;
    cout<<"�������� �������� ������: "<<endl;
    cout<<"1 - �����"<<endl<<"2- ����"<<endl<<"3- ����"<<endl<<"4- �����"<<endl<<"5- ����� (��������)"<<endl<<"6- ������"<<endl;

    cin>>switcher;
    switch (switcher)  {
    case 1:
    {
        name = "�����";
         break;
    }

    ////////////////////////////////////
    case 2:
    {
        name = "����";
         break;
    }

    ////////////////////////////////////
    case 3:
    {
        name = "����";
         break;
    }

    ////////////////////////////////////
    case 4:
    {
        name = "�����";
         break;
    }

    ////////////////////////////////////
    case 5:
    {
        name = "����� (��������)";
         break;
    }

    ////////////////////////////////////
    case 6:
    {
        name = "������";
         break;
    }

    ////////////////////////////////////
    default :
     {
         break;
    }
    }


    cout<<"������� ���� ������:"<<endl<<"1-�����"<<endl<<"2-������"<<endl;

    cin>>switcher;

    switch (switcher)  {
    case 1:
    {
        color = "�����";
         break; 
    }
     case 2:
    {
        color = "������";
         break;
    }
    default :
     {
         break;
    }
    }


    cout<<"������� ���������� ������"<<endl;
    cout<<"X: "<<endl;
    cin>>x;
    cout<<"Y: "<<endl;
    cin>>y;
    // ����� ���������� � �������
    Figure figure(name,color,x,y);

    figure.getColor();//����� ����� ������
    cout<<" ";
    figure.move();//����� ������� ������


    cout<< endl;

 int exit;
 cin >> exit;
    return 0;
}