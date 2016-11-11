//
//  main.c
//  贪吃蛇2
//
//  Created by 中国曲奂 on 16/11/6.
//  Copyright © 2016年 曲奂. All rights reserved.
//
#include<time.h>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct node
{
    int i;
    int j;
    struct node*next;
}snake;

//全局变量
int score=0;
int endgamestatus=0;
int food_x,food_y;
snake*head;//蛇的头结点
snake*p;//遍历蛇身用的指针
int status='R';//蛇状态变量
int t,u;
/////////////////////////

char map[20][30];//定义地图
int  Bit_Self()//判断是否咬自己
{
    p=head->next;
    while(p)
    {
        if(p->i==head->i&&p->j==head->j)
            return 1;
        p=p->next;
    }
    return 0;
}
void create_map()//创造地图
{
    for(t=0;t<20;t++)
    {
        for(u=0;u<30;u++)
        {
            if(t==0||u==0||t==19||u==29)
                map[t][u]='*';
            else map[t][u]=' ';
        }
    }
}
void print_map()//打印地图
{
    for(t=0;t<20;t++)
    {
        for(u=0;u<30;u++)
        {
            printf("%c",map[t][u]);
        }
        printf("\n");
    }
}
void endgame()//游戏结束
{
    system("clear");
    if(endgamestatus==1)
        printf("您撞到墙了");
    if(endgamestatus==2)
        printf("您咬到了自己");
    printf("your score=%d",score);
    exit(0);
}
void crosswall()//判断撞墙
{
    if(head->i==0||head->j==0||head->i==19||head->j==29)
    {
        endgamestatus=1;
        endgame();
    }
}
void Creat_Food()//生成食物
{
    food_x=rand()%20;
    food_y=rand()%30;
    map[food_x][food_y]='@';
}
void Init_Snake()//初始化
{
    int i=1;
    snake*tail;
    head=(snake*)malloc(sizeof(snake));
    head->i=15;
    head->j=5;
    head->next=NULL;
    tail=NULL;
    for(i=1;i<4;i++)
    {
        tail=(snake*)malloc(sizeof(snake));
        tail->i=15+i*1;
        tail->j=5;
        tail->next=head;
        head=tail;
    }
    
    while(tail)
    {
        map[tail->i][tail->j]='#';
        tail=tail->next;
    }
}

void Snake_Moving()//蛇移动
{
    snake*newhead;
    newhead=(snake*)malloc(sizeof(snake));
    crosswall();
    if(Bit_Self())
    {
        endgamestatus=2;
        endgame();
    }
    if(status=='R')//向右走
    {
        if(head->i==food_x&&head->j==food_y)
        {
            score=score+10;
            newhead->i=head->i+1;
            newhead->j=head->j;
            newhead->next=head;
            head=newhead;
            p=head;
            while(p)
            {
                map[p->i][p->j]='#';
                p=p->next;
            }
            Creat_Food();
        }
        else
        {
            newhead->i=head->i+1;
            newhead->j=head->j;
            newhead->next=head;
            head=newhead;
            p=head;
            while(p->next->next)
            {
                map[p->i][p->j]='#';
                p=p->next;
            }
           map[p->next->i][p->next->j]=' ';
           free(p->next);
            p->next=NULL;
        }
    }
    if(status=='L')
    {
        if(head->i==food_x&&head->j==food_y)
        {
            score=score+10;
            newhead->i=head->i-1;
            newhead->j=head->j;
            newhead->next=head;
            head=newhead;
            p=head;
            while(p)
            {
                map[p->i][p->j]='#';
                p=p->next;
            }
            Creat_Food();
        }
        else
        {
            newhead->i=head->i-1;
            newhead->j=head->j;
            newhead->next=head;
            head=newhead;
            p=head;
            while(p->next->next)
            {
                map[p->i][p->j]='#';
                p=p->next;
            }
            map[p->next->i][p->next-> j]=' ';
            free(p->next);
            p->next=NULL;
        }
    }
    if(status=='D')
    {
        if(head->i==food_x&&head->j==food_y)
        {
            score=score+10;
            newhead->i=head->i+1;
            newhead->j=head->j;
            newhead->next=head;
            head=newhead;
            p=head;
            while(p)
            {
                map[p->i][p->j]='#';
                p=p->next;
            }
            Creat_Food();
        }
        else
        {
            newhead->i=head->i;
            newhead->j=head->j+1;
            newhead->next=head;
            head=newhead;
            p=head;
            while(p->next->next)
            {
                map[p->i][p->j]='#';
                printf("%c",map[p->i][p->j]);
                p=p->next;
            }
            map[p->next->i][p->next-> j]=' ';
            free(p->next);
            p->next=NULL;
        }
    }
    if(status=='U')
    {
        if(head->i==food_x&&head->j==food_y)
        {
            score=score+10;
            newhead->i=head->i;
            newhead->j=head->j-1;
            newhead->next=head;
            head=newhead;
            p=head;
            while(p)
            {
                map[p->i][p->j]='#';
                p=p->next;
            }
            Creat_Food();
        }
        else
        {
            newhead->i=head->i;
            newhead->j=head->j-1;
            newhead->next=head;
            head=newhead;
            p=head;
            while(p->next->next)
            {
                map[p->i][p->j]='#';
                p=p->next;
            }
            map[p->i][p->j]=' ';
            free(p->next);
            p->next=NULL;
        }
    }
}
void gamecircle()//游戏循环
{
    printf("w a s d分别对应上 左 下 右 ");
    print_map();
    while (1)
    {
        
        char key;
        scanf("%c",&key);
        switch(key)
        {
            case 'd':
                if(status!='L')
                    status='R';
                break;
            case 'a':
                if(status!='R')
                    status='L';
                break;
            case 'w':
                if(status!='D')
                    status='U';
                break;
            case 's':
                if(status!='U')
                    status='D';
                break;
            default:
            break;
        }
    
        sleep(1);
        system("clear");
        Snake_Moving();
        print_map();
    }
    
}

int main()
{
    create_map();
    Creat_Food();
    Init_Snake();
    gamecircle();
    endgame();
    return 0;
}
