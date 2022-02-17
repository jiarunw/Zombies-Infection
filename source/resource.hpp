//
//  resource.hpp
//  resource
//
//  Created by Joe Wang on 11/15/21.
//

#ifndef resource_hpp
#define resource_hpp

#include "fssimplewindow.h"
//#include "ysglfontdata.h"
#include "yssimplesound.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
using namespace std;
class Resource
{
public:
    int x_base,y_base,x_size,y_size,id,base_value,ifdraw;
    void get(int &x_,int &y_,int &x_size_,int &y_size);
    virtual void Draw()=0; // draw object
    virtual void init()=0; //init object
    int GetX(void);
    int GetY(void);
    int GetXsize(void);
    int GetYsize(void);
    int GetId(void);
    int GetValue(void);
    void Kill(void);

};

void Resource::Kill() //kill object
{
    x_base =0;
    y_base =0;
    x_size =0;
    y_size =0;
    id = 0;
    base_value =0;
    ifdraw = -1;
}

int Resource::GetValue() //get value(recover or hurt or weapen id or nothing)
{
    return base_value;
}

int Resource::GetId() //get object id; Hprecover = 2, Bomb =3, Green =4, Box =5;
{
    return id;
}

int Resource::GetX(void) //get x
{
    return x_base;
}

int Resource::GetY(void) //get y
{
    return y_base;
}
int Resource::GetXsize(void) //get x_size
{
    return x_size;
}
int Resource::GetYsize(void) //get y_size
{
    return y_size;
}

void Resource::get(int &x_,int &y_,int &x_size_,int &y_size_)
{
    x_ = x_base;
    y_ = y_base;
    x_size_ = x_size;
    y_size_ = y_size;
}

class Hprecover: public Resource
{
public:
    int x,y,height,width,length,value,recover;
    Hprecover();
    void Draw();
    void init();
    int* GetBox();
    int GetLength();
    int GetRecover();
    void Kill();
//    ~HpRestore();
};

class Green: public Resource
{
public:
    int x,y,w,h,length,value;
    Green();
    void Draw();
    void init();
    int* GetBox();
};

class Bomb: public Resource
{
public:
    int x,y,w,h,length,range,state,value,hurt;
    Bomb();
    void Draw();
    void init();
    int* GetBox();
    void Explosion(void);
    int GetHurt();
    
};

class Box: public Resource
{
public:
    int x,y,w,h,length,range,state,value;
    Box();
    void Draw();
    void init();
    int* GetBox();
//    void Explosion(void);
};

#endif /* resource_hpp */
