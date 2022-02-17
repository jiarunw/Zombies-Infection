//
//  resource.cpp
//  resource
//
//  Created by Joe Wang on 11/15/21.
//

#include "resource.h"

#define GETMAPINDEX(X, Y) ((Y)*800 + (X))
const double Pi=3.1415927;

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


void drawbox(int x1, int y1, int x2, int y2, int r, int g, int b)
{
    glColor3ub(r,g,b);
    glBegin(GL_QUADS);
    glVertex2i(x1,y1);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glEnd();
}

void draw_box_from_center(int x,int y,int height, int width)
{
//    glColor3ub(255,0,0);
    glBegin(GL_QUADS);
    glVertex2i(x-width,y-height);
    glVertex2i(x+width,y-height);
    glVertex2i(x+width,y+height);
    glVertex2i(x-width,y+height);
    glEnd();
}
void DrawMap(int *map,int Window_X, int Window_Y)
{
    

}


void DrawCircle(int x,int y,int r)
{
    glBegin(GL_TRIANGLE_FAN);
    double d_x = double(x);
    double d_y = double(y);
    double d_r = double(r);

    for(int i=0; i<64; ++i)
    {
        double a=(double)i*Pi/32.0;
        double c=cos(a);
        double s=sin(a);
        glVertex2d(d_x+c*d_r,d_y+s*d_r);
    }
    glEnd();
}


Bomb::Bomb()
{
    x = 0;
    y = 0;
    h = 0;
    w = 0;
    range = 0;
    state = 0;
    value = 0;
    x_base = x;
    y_base = y;
    x_size = w;
    y_size = h;
};
int Bomb::GetHurt()
{
    return hurt;
}

void Bomb::init()
{
    
    x = rand()%700;
    y = rand()%500;
    h = 18;
    w = 18;
    range = 20;
    state = 0;
    value = 3;
    x_base = x;
    y_base = y;
    x_size = w;
    y_size = h;
    hurt = 10;
    id = value;
    base_value = -10;
    ifdraw =1;
}

void Bomb::Draw()
{
    if(ifdraw==1)
    {
        int r = 16;
        glColor3ub(0,0,0);
        draw_box_from_center(x,y,h,w);
        glColor3ub(255,0,0);
        DrawCircle(x, y, r);
        glColor3ub(0,0,0);
        glLineWidth(4.0);
        glBegin(GL_LINES);
        glVertex2i(x,y);
        glVertex2i(x,y-h-h/3);
        glEnd();
        glBegin(GL_LINES);
    //    glVertex2i(x,y);
        glVertex2i(x,y-h-h/3);
        glVertex2i(x+w/2,y-h-h/3);
        glEnd();
        
        glPointSize(5.0);
        glBegin(GL_POINTS);
    //    glVertex2i(x,y);
    //    glVertex2i(x,y-h-h/3);
        glVertex2i(x+w/2,y-h-h/3);
        glEnd();
    }
    
    
}


int* Bomb::GetBox()
{
    if(state==0)
    {
        GETMAPINDEX(x,y);
        int *ans;
        int len = 4*h*w;
        
        ans = new int[len];
        int count = 0;
        for(int i =x-w;i<(x+w);i++)
        {
            for(int j =y-h;j<(y+h);j++)
            {
                ans[count] = GETMAPINDEX(i,j);
    //            printf("%i,",ans[count]);
                count++;
            }
        }
        length = count;
        printf("length: %i,  count %i\m", len, count);
        return ans;
    }else{
        int *ans;
        ans = new int[1];
        ans[0] = 0;
        length =1;
        return ans;
    }
    
}

void Bomb::Explosion()
{
    int* ans = GetBox();
    glPointSize(2.0);
    glColor3ub(0,0,0);
    glBegin(GL_POINTS);
    int px;
    int py;
    for(int j=5; j<80;j+=2)
    {
        for(int i=0;i<length;i+=8)
        {

            px = GetX()-2*GetXsize() +rand()%j+rand()%20-10;
            py = GetY()-2*GetYsize() +rand()%j+rand()%20-10;
            
            glColor3ub(j, 0, 0);
            glVertex2i(px,py);
        }
    }
    
    state=1;
    
    glVertex2i(x,y);
    
    
    glEnd();
    

}

void Bomb::Action(void)
{
    //Explosion();
//    ifdraw = -1;
//    Kill();
    Kill();
}

int * Hprecover::GetBox()
{
    GETMAPINDEX(x,y);
    int *ans;
    int len = 4*height*width;
    
    ans = new int[len];
    int count = 0;
    for(int i =x-width;i<(x+width);i++)
    {
        for(int j =y-height;j<(y+height);j++)
        {
            ans[count] = GETMAPINDEX(i,j);
//            printf("%i,",ans[count]);
            count++;
        }
    }
    length = count;
    printf("length: %i,  count %i\m", len, count);
    return ans;
//    int x1 = x-height
    
    
}

int Hprecover::GetLength()
{
    int *ans;
    int len = 4*height*width;
    
    ans = new int[len];
    return len;
}

void Hprecover::Action()
{
    /*if(ifdraw==1)
    {
        glColor3ub(0,100,0);
        for(int i=0;i<5;i+=1)
        {
            draw_box_from_center(x, y-i, height+i/2,width+i/2);
            draw_box_from_center(x, y-i, width+i/2,height+i/2);
        }
        
    }*/
//    ifdraw = -1;
    Kill();
}
//Hprecover::~

Hprecover::Hprecover()
{
    x = 0;
    y = 0;
    height = 0;
    width = 0;
    value = 0;
    x_base = x;
    y_base = y;
    x_size = width;
    y_size = height;
}

int Hprecover::GetRecover()
{
    return recover;
}

void Hprecover::init()
{
    x = rand()%700;
    y = rand()%500;
    height = 16;
    width = 6;
    value = 2;
    x_base = x;
    y_base = y;
    x_size = width;
    y_size = height;
    recover = 10;
    id = value;
    base_value = 10;
    ifdraw=1;
    
}

void Hprecover::Draw()
{
    if(ifdraw==1)
    {
        glColor3ub(255,0,0);
        draw_box_from_center(x, y, height,width);
        draw_box_from_center(x, y, width,height);
    }
    

}



int * Green::GetBox()
{
    GETMAPINDEX(x,y);
    int *ans;
    int len = 2*h*w;
    
    ans = new int[len];
    int count = 0;
    for(int i =x-w/2;i<(x+w/2*3);i++)
    {
        for(int j =y-h;j<(y);j++)
        {
            ans[count] = GETMAPINDEX(i,j);
//            printf("%i,",ans[count]);
            count++;
        }
    }
    ans = new int[count];
    int count2 = 0;
    for(int i =x-w/2;i<(x+w/2*3);i++)
    {
        for(int j =y-h;j<(y);j++)
        {
            ans[count2] = GETMAPINDEX(i,j);
//            printf("%i,",ans[count]);
            count2++;
        }
    }
    length = count2;
    printf("length: %i,  count %i\n", count, count2);
    return ans;
}

void Green::init()
{
    x = rand()%700;
    y = rand()%500;
    h = rand()%5+20;
    w = rand()%5+20;
    value = 4;
    x_base = x;
    y_base = y;
    x_size = w;
    y_size = h;
    id = value;
    base_value = 0;
    ifdraw =1;
    move_value = 8;
    
};
void Green::Action()
{
    move_value *= -1;

}

Green::Green()
{
    x = 0;
    y = 0;
    h = 0;
    w = 0;
    value = 0;
    x_base = x;
    y_base = y;
    x_size = w;
    y_size = h;
    move_value =0;
}

void Green::Draw()
{
    if(ifdraw==1)
    {
        glColor3ub(0,255,0);
        glBegin(GL_TRIANGLES);
        glVertex2i(x,y);
        glVertex2i(x+w/2+move_value, y-h);
        glVertex2i(x+w,y );
    //    glVertex2i(x2, y1);
        glEnd();
        glColor3ub(0,255,0);
        glBegin(GL_TRIANGLES);
        glVertex2i(x,y);
        glVertex2i(x-w/2+move_value, y-h/2);
        glVertex2i(x+w,y );
    //    glVertex2i(x2, y1);
        glEnd();
        glColor3ub(0,255,0);
        glBegin(GL_TRIANGLES);
        glVertex2i(x,y);
        glVertex2i(x+w+w/2+move_value, y-h/2);
        glVertex2i(x+w,y );
    //    glVertex2i(x2, y1);
        glEnd();
    }
    
};


void write_to_map(int* pos,int length,int* map, int target)
{
//    int len = 0;
    for(int i =0; i<length;i++)
    {
        map[pos[i]] = target;
    }
}

bool check_map(int*pos,int length, int* map)
{
    for(int i =0; i<length;i++)
    {
//        map[pos[i]] = target;
        if(map[pos[i]]!=0){return true;}
        
    }
    return false;
}

void Box::init()
{
    x = rand()%700;
    y = rand()%500;
    h = 18;
    w = 18;
    range = 20;
    state = 0;
    value = 5;
    x_base = x;
    y_base = y;
    x_size = w;
    y_size = h;
    id = value;
    base_value = rand()%3;
    ifdraw =1;
}

Box::Box()
{
    x = 0;
    y = 0;
    h = 0;
    w = 0;
    range = 0;
    state = 0;
    value = 0;
    x_base = x;
    y_base = y;
    x_size = w;
    y_size = h;
}

void Box::Action()
{
   /* if(ifdraw==1)
    {
        for(int i=0;i<5;i++)
        {
            int r = 5;
            glColor3ub(0,0,200);
            draw_box_from_center(x,y,h-i,w-i);
            glColor3ub(255,0,0);
            DrawCircle(x, y, r-i);
            glColor3ub(0,0,0);
        }
        

    }*/
    Kill();
}

void Box::Draw()
{
    if(ifdraw==1)
    {
        int r = 5;
        glColor3ub(0,0,200);
        draw_box_from_center(x,y,h,w);
        glColor3ub(255,0,0);
        DrawCircle(x, y, r);
        glColor3ub(0,0,0);
    }
    

}

int* Box::GetBox()
{
    if(state==0)
    {
        GETMAPINDEX(x,y);
        int *ans;
        int len = 4*h*w;
        
        ans = new int[len];
        int count = 0;
        for(int i =x-w;i<(x+w);i++)
        {
            for(int j =y-h;j<(y+h);j++)
            {
                ans[count] = GETMAPINDEX(i,j);
    //            printf("%i,",ans[count]);
                count++;
            }
        }
        length = count;
        printf("length: %i,  count %i\m", len, count);
        return ans;
    }else{
        int *ans;
        ans = new int[1];
        ans[0] = 0;
        length =1;
        return ans;
    }
}


void pushtovector(vector<Resource*> &resource_list,int number, Resource *resource )
{
    for(int i=0;i<number;i++)
    {
        printf("hi %i\n",i);
        
        resource[i].init();
        resource_list.push_back(&resource[i]);
        printf("initialed\n");
    }
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


//Check the example main code for function usage.
//
////
//int main(void)
//{
//    int Window_X = 800;
//    int Window_Y = 600;
//    srand(time(NULL));
//    int hprecover_number = 5;
//    int green_number = 5;
//    int bomb_number = 5;
//    int box_number = 5;
//    int vector_count;
//
//    vector_count = hprecover_number+box_number+bomb_number+green_number;
//
//    vector<Resource*> resource_list;
//
//    Hprecover *hprecover;
//    hprecover = new Hprecover[hprecover_number];
//
//    Green *green;
//    green = new Green[green_number];
//
//    Box *box;
//    box = new Box[box_number];
//
//    Bomb *bomb;
//    bomb = new Bomb[bomb_number];
//
//    for(int i=0;i<box_number;i++)
//    {
//        box[i].init();
//        resource_list.push_back(&box[i]);
//    }
//    for(int i=0;i<hprecover_number;i++)
//    {
//        hprecover[i].init();
//        resource_list.push_back(&hprecover[i]);
//    }
//    for(int i=0;i<bomb_number;i++)
//    {
//        bomb[i].init();
//        resource_list.push_back(&bomb[i]);
//    }
//    for(int i=0;i<green_number;i++)
//    {
//        green[i].init();
//        resource_list.push_back(&green[i]);
//    }
//
//
//
//    FsOpenWindow(0, 0, 800, 600, 1);



//
//    for(;;)
//    {
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        FsPollDevice();
//        auto key = FsInkey();
//        if(FSKEY_ESC==key)
//        {
//            break;
//        }
//        if(FSKEY_3==key)
//        {
//            for(int i =0; i<vector_count;i++)
//            {
//                if(resource_list[i]->GetId()==3)
//                {
//                    printf("hello\n");
//                    resource_list[i]->Action();
////                    resource_list[i]->Ex
//                }
//            }
//        }
//        if(FSKEY_2==key)
//        {
//            for(int i =0; i<vector_count;i++)
//            {
//                if(resource_list[i]->GetId()==2)
//                {
//                    printf("hello\n");
//                    resource_list[i]->Action();
////                    resource_list[i]->Ex
//                }
//            }
//        }
//        if(FSKEY_4==key)
//        {
//            for(int i =0; i<vector_count;i++)
//            {
//                if(resource_list[i]->GetId()==4)
//                {
//                    printf("hello\n");
//                    resource_list[i]->Action();
////                    resource_list[i]->Ex
//                }
//            }
//        }
//        if(FSKEY_5==key)
//        {
//            for(int i =0; i<vector_count;i++)
//            {
//                if(resource_list[i]->GetId()==5)
//                {
//                    printf("hello\n");
//                    resource_list[i]->Action();
////                    resource_list[i]->Ex
//                }
//            }
//        }
//
//
//
//        for(int i =0; i<vector_count;i++)
//        {
//            resource_list[i]->Draw();
//            printf("%ith: X %i Y %i Xsize %i Ysize %i id %i value %i \n",i,resource_list[i]->GetX(),resource_list[i]->GetY(),resource_list[i]->GetXsize(),resource_list[i]->GetYsize(),resource_list[i]->GetId(), resource_list[i]->GetValue());
//        }
//
//
//
//        FsSleep(25);
//        FsSwapBuffers();
//
//    }

//}


