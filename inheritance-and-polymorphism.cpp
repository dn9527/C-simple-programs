//Dat Nguyen
//Code::Block
// inheritance and polymorphism
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;

const double pi = 3.141592654;
//**********************************************************
class GeometricSolid
{
public:
    GeometricSolid() {}
    virtual ~GeometricSolid() {}
    virtual string name() const = 0;
    virtual double volume() const = 0;
    virtual double surface_area() const = 0;
};

//**********************************************************************
class Circular : public GeometricSolid
{
public:
    Circular() : GeometricSolid() {}
    ~Circular() {}
    virtual string name() const = 0;
    virtual double volume() const = 0;
    virtual double surface_area() const = 0;
};
//*******************************************************************
class Cylinder : public Circular
{
private:
    double radius;
    double height;
public:
    Cylinder(double r, double h) : Circular(), radius(r), height(h) {}
    ~Cylinder() {}
    string name() const {return "cylinder";}
    double volume() const {return pi*radius*radius*height;}
    double surface_area() const {return 2*pi*radius*(radius+height);}
};
//**************************************************************
class Sphere : public Circular
{
private:
    double radius;
public:
    Sphere(double r) : Circular(), radius(r) {}
    ~Sphere() {}
    virtual string name() const {return "sphere";}
    virtual double volume() const {return pi*radius*radius*radius*4/3;}
    virtual double surface_area() const {return 4*pi*radius*radius;}
};
//***************************************************************
class Rectangular : public GeometricSolid
{
public:
    Rectangular() : GeometricSolid() {}
    ~Rectangular() {}
    virtual string name() const = 0;
    virtual double volume() const = 0;
    virtual double surface_area() const = 0;
};
//***************************************************************
class RectangularPrism : public Rectangular
{
private:
    double length;
    double width;
    double height;
public:
    RectangularPrism(double l, double w, double h) : Rectangular(), length(l), width(w), height(h) {}
    ~RectangularPrism() {}
    virtual string name() const {return "rectangular prism";}
    virtual double volume() const {return length*width*height;}
    virtual double surface_area() const {return 2*(length*width + length*height + width*height);}
};
//****************************************************************
class Cube : public RectangularPrism
{
public:
    Cube(double side) : RectangularPrism(side, side, side) {}
    ~Cube() {}
    string name() const {return "cube";}
};
//***************************************************************
int main(void)
{
    const string path("C:/temp/Ass#10.txt");
    ifstream infile(path.c_str());
    if(!infile)
    {
        cerr << "Cannot open " << path << endl;
        exit(1);
    }

    GeometricSolid* ptrSolid;
    string type;
    double d1, d2, d3;
    cout << setprecision(4) << fixed;
    while(infile)
    {
        infile >> type;
        if(infile.eof()) break;

        if(type == "cy")
        {
            infile >> d1 >> d2;
            ptrSolid = new Cylinder(d1, d2);
        }
        else if(type == "sp")
        {
            infile >> d1;
            ptrSolid = new Sphere(d1);
        }
        else if(type == "re")
        {
            infile >> d1 >> d2 >> d3;
            ptrSolid = new RectangularPrism(d1,d2,d3);
        }
        else
        {
            infile >> d1;
            ptrSolid = new Cube(d1);
        }

        cout << setw(20) << left << ptrSolid->name()
             << setw(15) << right << ptrSolid->surface_area()
             << setw(15) << ptrSolid->volume() << endl;

        delete ptrSolid;
    }
}
