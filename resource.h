//
//  resource.h
//  resource
//
//  Created by Joe Wang on 11/15/21.
//

#ifndef resource_hpp
#define resource_hpp

#include "fssimplewindow.h"
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
    virtual void Action()=0; // action when collision, include Kill if needed
    int GetX(void);
    int GetY(void);
    int GetXsize(void);
    int GetYsize(void);
    int GetId(void); //get object id; Hprecover = 2, Bomb =3, Green =4, Box =5;
    int GetValue(void); //get value(recover or hurt or weapen id or nothing)
//    virtual void Action(void)=0;
    void Kill(void);

};

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
//    void Kill();
    void Action();
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
    void Action();
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
    void Action();
    
};

class Box: public Resource
{
public:
    int x,y,w,h,length,range,state,value;
    Box();
    void Draw();
    void init();
    void Action();
    int* GetBox();
//    void Explosion(void);
};

#endif /* resource_hpp */
