//Dat Nguyen
//Code::Block
//Dice Game
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

const string name[3]= {"Tom", "Dick", "Harry"};
const int personalities[3]= {1, 3, 36};

class Player
{
private:
    string gamer;
    int points;
    int numOfRollPerTurn;
    int dice1;
    int dice2;
public:
    void set(string);
    void newTurn();
    void roll();
    void print();
    string getname() {return gamer;}    //inline functions
    int getpoints() {return points;}
    int getTurnPoints() {return numOfRollPerTurn;}
    int getdice1() {return dice1;}
    int getdice2() {return dice2;}
};

int main()
{
    //srand(time(0));
    Player game[3];
    bool win = false;
    for(int k=0; k<3; k++) game[k].set(name[k]);

    while(win == false)
    {
        for(int i=0; i<3; i++)
        {
            cout << game[i].getname() << ", it is your turn" << endl;
            game[i].newTurn();
            int numturn = 0;

            do
            {
                numturn++;
                game[i].roll();

                if((game[i].getpoints()+game[i].getTurnPoints()) >= 100)
                {
                    win = true;
                    break;
                }

            }while(win == false && numturn < personalities[i] && (game[i].getdice1() != 1 && game[i].getdice2() != 1));

            game[i].print();

            if(game[i].getpoints() >= 100)
            {
                cout << endl << game[i].getname() << " won the game with " << game[i].getpoints() << " points" << endl;
                break;
            }
        }
    }
}

void Player::roll()
{
    dice1=rand()%6 + 1;
    dice2=rand()%6 + 1;
    cout << "   You rolled " << dice1 << " and " << dice2 << ".  That's ";

    int sum;
    if(dice1==1 && dice2==1)
    {
        sum = 0;
        cout << "a SKUNK!!!";
    }
    else if(dice1==1 || dice2==1)
    {
        sum = 0;
        cout << sum;
    }
    else
    {
        sum = dice1 + dice2;
        cout << sum;
    }

    numOfRollPerTurn += sum;
    cout << endl;

}

void Player::print()
{
    if(dice1==1 && dice2==1)
    {
        numOfRollPerTurn = 0;
        points = 0;
    }
    else if(dice1==1 || dice2==1) numOfRollPerTurn = 0;
    else points += numOfRollPerTurn;

    cout << "  Points for the turn = " << numOfRollPerTurn
         << "   Total points = " << points << endl << endl;
}

void Player::set(string n)
{

    gamer = n;
    points = 0;
}

void Player::newTurn()
{
    numOfRollPerTurn = 0;
}
