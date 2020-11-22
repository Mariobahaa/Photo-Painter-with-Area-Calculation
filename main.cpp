#include <iostream>
#include "graphics.h"
#include <math.h>

using namespace std;
class point {
    int xpos;
    int ypos;
public:

    point(int x=0,int y=0)
    {
        xpos = x;
        ypos =y;
    }
    void setX(int x=0) {xpos = x;}
    void setY (int y=0) {ypos=y;}

    int getX() {return xpos;}
    int getY() {return ypos;}

};


class Shape{
    int color;
public:
    Shape(int c){color = c;}
    virtual void draw() = 0;
    virtual float calcArea()=0;
    int getColor() {return color;}
    void setColor(int c){color = c;}
};


class rect: public Shape{
    point BR;
    point UL;
    //int color;

public :
    rect(point u, point b,int c): Shape(c){
        BR = b;
        UL = u;
        //color = c;
    }

    void draw(){
        //initgraph();
        setcolor(getColor());
        rectangle(BR.getX(), BR.getY(),UL.getX(), UL.getY());

    }
    float calcArea()
    {
       return abs((float)abs(UL.getX()-BR.getX())*(float)abs(UL.getY()-BR.getY()));

    }

};



class Line: public Shape {
    point BR;
    point UL;
   // int color;

public :
    Line(point u, point b,int c): Shape(c){
        BR = b;
        UL = u;
        //color = c;
    }

    void draw(){
       // initgraph();
        setcolor(getColor());
        line(BR.getX(), BR.getY(),UL.getX(), UL.getY());

    }

    float calcArea(){
        return 0.0;
    }


};


class Triangle: public Shape {
    point a;
    point b;
    point c;
    //int color;

public :
    Triangle(point aa, point bb, point cc, int cl):Shape(cl){
        a =aa;
        b =bb;
        c =cc;
        //color = cl;
    }

    void draw(){
       // initgraph();
        Line L1(a,b,getColor());
        L1.draw();

        Line L2(b,c,getColor());
        L2.draw();

        Line L3(c,a,getColor());
        L3.draw();

    }
    float calcArea(){
        return(
               (float)abs(a.getX()*abs(b.getY()-c.getY()))+
               (float)abs(b.getX()*abs(c.getY()-a.getY()))+
            (float)abs(c.getX()*abs(a.getY()-b.getY())))/2.0;
    }

};


class Circle: public Shape {
    point center;
    int diameter;
    //int color;

public :
    Circle(point p, int r,int c): Shape(c){
        center = p;
        diameter = r ;
        // color = c;
    }

    void draw(){
        //initgraph();
        setcolor(getColor());
        circle(center.getX(),center.getY(), diameter);

    }

    float calcArea(){
        return (22.0/7.0)*(float)(diameter/2.0)*(float)(diameter/2.0);
    }


};

class Square : public rect{
    public:
    Square(point p,int side,int c): rect(p,point(p.getX()+side,p.getY()+side),c){}
};

class Picture{
    Shape ** shapes;
    int numOfShapes;
public:
    Picture(Shape**S, int n)
    {
        shapes = S;
        numOfShapes = n;
    }
    void paint()
    {
        initgraph();
        for(int i=0;i<numOfShapes;i++)
        {
            shapes[i]->draw();
        }
    }
    float sumAreas(){
        float Sum;
        for(int i=0;i<numOfShapes;i++)
        {
            Sum+= (float)shapes[i]->calcArea();
            //cout << (float)shapes[i]->calcArea() << endl;
        }
        return Sum;
    }
    ~Picture()
    {
        for(int i=0;i<numOfShapes;i++)
        {
            delete [] shapes[i];
        }
        delete [] shapes;
    }
};
int main()
{
   // system("cls");
    //initgraph();
    Shape * sh[8];

    sh[0] = new Circle(point(400,100),100,100);
    sh[1] = new Line(point(450,100),point(470,280),100);
    sh[2] = new Line(point(350,100),point(330,280),100);
    sh[3] = new Circle(point(400,280),140,100);
    sh[4] = new rect(point(300,380),point(500,500),100);
    sh[5] = new Line(point(385,350),point(385,420),100);
    sh[6] = new Line(point(415,350),point(415,420),100);
    sh[7] = new Triangle(point(485,475),point(475,490),point(495,490),100);

    Picture P(sh,8);
    P.paint();
    cout << "Sum of Areas = " << P.sumAreas() << endl;

    int x;
    cin >> x;
    return 0;
}
