#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

class Carts
{
    public:
    pair<int,int> Pos;
    int direction = 0;
    int nextTurn = 0;
    int id = 0;
    Carts(pair<int,int> Pos_in,int direction_in, int id_in): Pos(Pos_in), direction(direction_in), id(id_in) {}
    void updatePos();
    void updateIntersection();
    void increaseDirection();
    void decreaseDirection();
    void updateCorner(bool);
};

void Carts::increaseDirection() {
    direction++;
    if (direction >3) 
    {
        direction = 0;
    }
}

void Carts::decreaseDirection() {
    direction--;
    if (direction < 0) 
    {
        direction = 3;
    }
}

void Carts::updateIntersection() 
    {
        switch (nextTurn) 
        {
            case 0:
                decreaseDirection();
                break;
            case 2:
                increaseDirection();
                break;
            default:
                break;    
        }
        
        nextTurn++;
        if(nextTurn >3)
        {
            nextTurn = 0;
        }
    };

void Carts::updatePos()
{
   // cout << "old positions: " << Pos.first << "x" << Pos.second << " direction" << direction << endl;
    switch (direction)
    {
        /* Moving Upwards */
        case 0:
            Pos.second--;
            break;
        /* Moving Right */
        case 1:
            Pos.first++;
            break;
        /* Moving Down */
        case 2:
            Pos.second++;
            break;
        /* Moving Left */
        case 3:
            Pos.first--;
            break;
        default:
            cout << "broken move!\n";
            break;
    }
    
}

void Carts::updateCorner(bool backslash)
{
    if (backslash) {
        switch (direction) 
        {
            case 0:
                decreaseDirection();
                break;
            case 1:
                increaseDirection();
                break;
            case 2:
                decreaseDirection();
                break;
            case 3:
                increaseDirection();
                break;
            default:
                cout << "You broken! " << direction << endl;
                break;    
        }
    }
    else 
    {   
        switch (direction) 
        {
            case 0:
                increaseDirection();
                break;
            case 1:
                decreaseDirection();
                break;
            case 2:
                increaseDirection();
                break;
            case 3:
                decreaseDirection();
                break;
            default:
                cout << "You broken 2! "  << direction << endl;
                break;    
        }
    }
}

class Corners
{
    public:
    pair<int,int> Pos;
    bool backslash = true;
    Corners(pair<int,int> inPos, bool backslash_in): Pos(inPos), backslash(backslash_in) {}
};

// finds the first collision, if any
bool checkCollision(Carts & myCart, vector<Carts> &cartsVec)
{
    for (auto cart: cartsVec)
    {
        if (myCart.Pos == cart.Pos  && !((myCart.direction == cart.direction) && (myCart.nextTurn == cart.nextTurn)))
        {
            return true;
        }
    }
    return false;
}

// finds the first collision, if any
bool checkCollision(vector<Carts> cartsVec,pair<int,int> & collisionPos)
{
    for (auto cart: cartsVec)
    {
        for(auto myCart : cartsVec)
        {
            if (myCart.Pos == cart.Pos && myCart.direction != cart.direction)
            {
                collisionPos = myCart.Pos;
                return true;
            }
        }
    }
    return false;
}


void checkIntersection(Carts &myCart, vector<pair<int,int>> intersections) 
{
    for (auto coord : intersections) 
    {
        if (myCart.Pos == coord) 
        {
            myCart.updateIntersection();
        }
    }
}

void checkCorners(Carts &myCart,  vector<Corners> corners) 
{
    for (auto coord : corners) 
    {
        if (myCart.Pos == coord.Pos) 
        {
            myCart.updateCorner(coord.backslash);
        }
    }
}


int main()
{
    map<char,int> charMap = {{'^',0},{'>',1}, {'v',2}, {'<',3}};

    /* Open File and add it to vector. */
    string _line;
    vector<string> DataLines;
    //ifstream myfile ("input.txt");
    //ifstream myfile ("Mag_Input.txt");
    ifstream myfile ("test1.txt");
    //ifstream myfile ("test2.txt");
    int x = 0;
    int y = 0;
    vector<pair<int,int>> IntersectionsVec;
    vector<Carts> CartsVec;
    vector<Corners> CornersVec;
    int cartId = 0;

    if (myfile.is_open())
    {
        while ( getline (myfile,_line) )
        {
            x=0;
            for(auto coord : _line)
            {
                switch (coord)
                {
                    case '\\':
                    case '/':
                        CornersVec.push_back(Corners(pair<int,int>(x,y),(coord == '\\')));
                        break;
                    case '+':
                        IntersectionsVec.push_back(pair<int,int>(x,y));
                        break;
                    case '^':
                    case '<':
                    case '>':
                    case 'v':
                        CartsVec.push_back(Carts(pair<int,int>(x,y),charMap[coord], cartId));
                        cartId++;
                        break;
                    default:
                        break;
                }
                x++;
            }
            y++;
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 

    cout<<"My Corners are at:\n";
    for(auto corner : CornersVec)
    {
        cout<< corner.Pos.first<<"x"<<corner.Pos.second<< " ";
    }
    cout<<"\nMy Intersections are at:\n";
    for(auto inter : IntersectionsVec)
    {
        cout<< inter.first<<"x"<<inter.second<< " ";
    }
    cout<<"\nAnd finally my carts are at:\n";
    for(auto carts : CartsVec)
    {
        cout<< carts.Pos.first<<"x"<<carts.Pos.second<< " facing direction: "<<carts.direction << '\n';
    }

    /* Sortera lista */
    /*sort(CartsVec.begin(),CartsVec.end());*/
    cout<<"\nCarts are at:\n";
    for(auto carts : CartsVec)
    {
        cout<< carts.Pos.first<<"x"<<carts.Pos.second<< " facing direction: "<<carts.direction << '\n';
    } 

    /* Uppdatera positioner efter den sorterade listan */
    bool collision = false;
    int it = 0;
    while (!collision) 
    {
        sort(CartsVec.begin(),CartsVec.end(), [](auto &left, auto &right)
        {
            if (left.Pos.second == right.Pos.second)
            {
                return left.Pos.first < right.Pos.first;
            }
            else
            {
                return (left.Pos.second < right.Pos.second);
            }
         } );

        for(auto &carts : CartsVec)
        {
            carts.updatePos();
            checkIntersection(carts, IntersectionsVec);
            checkCorners(carts, CornersVec);
            if (checkCollision(carts, CartsVec)) 
            {
                collision = true;
                cout << "The collision happens at: " << carts.Pos.first << "x" << carts.Pos.second << '\n';
            }
        }

        /*
        cout<<"\niteration "<<it<<", Carts are at:\n";
        for(auto carts : CartsVec)
        {
            cout<< "ID " << carts.id <<": "<< carts.Pos.first<<"x"<<carts.Pos.second<< " facing direction: "<<carts.direction << '\n';
        } 
        pair<int,int> collisionPos;
        if (checkCollision(CartsVec,collisionPos)) 
        {
            collision = true;
            cout << "The collision happens at: " << collisionPos.first << "x" << collisionPos.second << '\n';
        }*/
        it++;
    }
    cout<<" iterations: " <<it<<'\n'; 

/*
        cout << "befor sort: " << endl;
        for(auto carts : CartsVec)
        {
            cout<< carts.Pos.first<<"x"<<carts.Pos.second<< " facing direction: "<<carts.direction << '\n';
        } 
            
        cout << "after sort:\n";
        for(auto carts : CartsVec)
        {
            cout<< carts.Pos.first<<"x"<<carts.Pos.second<< " facing direction: "<<carts.direction << '\n';
        }
        
    }
    */
    /* kontrollera kollision efter varje flytt? */

}