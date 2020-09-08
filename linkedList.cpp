//Dat Nguyen
//Code::Block
//Linked List
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;
//**************************************************************************
class Item
{
private:
    int itemNo;
    int quantity;
    Item* next;
public:
    Item() {}
    Item(const int, Item*);
    bool operator<(const int) const;
    int get_itemNo() const {return itemNo;}
    int get_quantity() const {return quantity;}
    Item* get_next() const {return next;}
    void set_next(Item*);
    void increaseQuantity();
    void decreaseQuantity();
};

Item::Item(const int n, Item* ptr) : itemNo(n), quantity(1), next(ptr)
{ }

bool Item::operator<(const int n) const
{
    return itemNo < n;
}

void Item::set_next(Item* ptr)
{
    next = ptr;
}

void Item::increaseQuantity()
{
    quantity++;
}

void Item::decreaseQuantity()
{
    quantity--;
}
//**************************************************************************
class Inventory
{
public:
    Item* top;
public:
    Inventory();
    ~Inventory();
    bool addItem(const int);
    bool subtractItem(const int);
    Item* get_top() const;
    Item* find(int item) const;
    void verify(const string, const int);
    friend ostream& operator<<(std::ostream&, const Inventory&);

};

Inventory::Inventory() : top(nullptr)
{ }

Inventory::~Inventory()
{
    Item* temp = top;
    while (temp != nullptr)
    {
        top = top->get_next();
        delete temp;
        temp = top;
    }
}

Item* Inventory::find(int item) const
{
    Item* temp = top;
    while (temp != nullptr)
    {
        if (temp->get_itemNo() == item) return temp;
        temp = temp -> get_next();
    }
    return 0;
}

bool Inventory::addItem(const int item)
{
    if (find(item))
    {
        find(item)->increaseQuantity();
        return false;
    }

    Item* temp = top;
    Item* temp2;
    if(top == nullptr)
    {
        temp = new Item(item, top);
        top = temp;
        return true;
    }

    while(*temp < item)
    {
        temp2 = temp;
        temp = temp->get_next();
        if(temp == nullptr) break;
    }

    if(temp == nullptr)
    {
        temp = new Item(item, nullptr);
        temp2->set_next(temp);
        return true;
    }

    if(!(*top < item))
    {
        temp = new Item(item, top);
        top = temp;
        return true;
    }
    else
    {
        temp = new Item(item, temp2->get_next());
        temp2->set_next(temp);
        return true;
    }
}

Item* Inventory::get_top() const
{
    return top;
}

bool Inventory::subtractItem(const int item)
{
    if (!find(item)) return false;

    Item* temp = top;
    Item* temp2;
    if (top->get_itemNo() == item)
    {
        if(top->get_quantity() > 1)
        {
            top->decreaseQuantity();
            return true;
        }
        else
        {
            top = top->get_next();
            delete temp;
            return true;
        }
    }

    while (temp->get_itemNo() != item)
    {
        temp2 = temp;
        temp = temp->get_next();
    }

    if(temp->get_quantity() > 1)
    {
        temp->decreaseQuantity();
        return true;
    }
    else
    {
        temp2->set_next(temp->get_next());
        delete temp;
        return true;
    }
}

void Inventory::verify(const string s, const int n)
{
    if(!s.empty())
    {
        string hold = s.substr(0, s.find(' '));
        if(hold == "print") cout << *this << endl;
        else if(hold == "add")
        {
            hold = s.substr(s.find(' ')+1, 4);
            if(isdigit(hold[0])) addItem(atoi(hold.c_str()));
        }
        else if(hold == "subtract")
        {
            hold = s.substr(s.find(' ')+1, 4);
            if(isdigit(hold[0])) subtractItem(atoi(hold.c_str()));
        }
        else cout << "Bad transaction: " << hold << " in line #" << n << endl;
    }
}

ostream& operator<<(ostream& out, const Inventory& object)
{
    Item* temp = object.get_top();
    out << endl << endl
        << "Item  Quantity" << endl;
    while (temp != 0)
    {
        out << setfill('0') << setw(4) << temp->get_itemNo()
            << setfill(' ') << setw(8) << temp->get_quantity() << endl;
        temp = temp->get_next();
    }
    out << endl;
    return out;
}
//**************************************************************************
int main()
{
    const string path = "C:/temp/Ass#9.txt";
    ifstream infile(path.c_str());
    if(!infile)
    {
        cerr << "Sorry, can't open the input file " << path
             << "\nPress enter to stop the program" << endl;
        exit(1);
    }

    Inventory storage;
    string holdLine;
    unsigned int line = 0;
    cout << endl << endl;
    while(infile)
    {
        getline(infile, holdLine);
        line++;
        if(infile.eof()) break;
        storage.verify(holdLine, line);
    }

    infile.close();
}

