#include <iostream>
#include<graphics.h>
#include<winbgim.h>
#include<cmath>
using namespace std;
struct matrice{
int R,G,B;
};
matrice a[100][100],b[100][100];
struct arbore{
int culoare,coloana;
arbore*unu;
arbore*doi;
arbore*trei;
arbore*patru;
};
int nr=0;
int w=1450,h=800;
arbore*S;


int estearborenull(arbore*S)
{
    return(S==NULL);
}


void initializare(arbore*&S)
{
    if(!estearborenull(S))
        S=NULL;

}


int nrniveluri(arbore*S)
{
    if(S==NULL)
        return 0;
    else
    {
        int n1,n2,n3,n4;
        n1=nrniveluri(S->unu);
        n2=nrniveluri(S->doi);
        n3=nrniveluri(S->trei);
        n4=nrniveluri(S->patru);
        return 1+max(max(n1,n2),max(n3,n4));
    }
}


int nrcoloane(arbore*S)
{
    if(S==NULL)
        return 0;
    else
    {
        int n1,n2,n3,n4;
        n1=nrcoloane(S->unu);
        n2=nrcoloane(S->doi);
        n3=nrcoloane(S->trei);
        n4=nrcoloane(S->patru);
        return 1+n1+n2+n3+n4;
    }
}


void coloana(arbore*S)
{
    if(S!=NULL)
    {
        coloana(S->unu);
        coloana(S->doi);
        nr++;
        S->coloana=nr;
        coloana(S->trei);
        coloana(S->patru);
    }
}


void deseneaza(int x,int niv,int nivt,int colt,int col)
{
    setcolor(WHITE);
    circle(col*(w/colt)-(w/(colt*2)),niv*(h/nivt)-(h/(nivt*2)),5);
    setfillstyle(1,x);
    floodfill(col*(w/colt)-(w/(colt*2)),niv*(h/nivt)-(h/(nivt*2)),WHITE);

}


void parcurgerearbore(arbore*S,int niv,int nivt,int colt)
{
    if(S!=NULL)
    {
        setcolor(COLOR(250,250,250));
        if(S->unu!=NULL)
            line(S->coloana*(w/colt)-(w/(colt*2)),niv*(h/nivt)-(h/(nivt*2)),S->unu->coloana*(w/colt)-(w/(colt*2)),(niv+1)*(h/nivt)-(h/(nivt*2)));
        if(S->doi!=NULL)
            line(S->coloana*(w/colt)-(w/(colt*2)),niv*(h/nivt)-(h/(nivt*2)),S->doi->coloana*(w/colt)-(w/(colt*2)),(niv+1)*(h/nivt)-(h/(nivt*2)));
        if(S->trei!=NULL)
            line(S->coloana*(w/colt)-(w/(colt*2)),niv*(h/nivt)-(h/(nivt*2)),S->trei->coloana*(w/colt)-(w/(colt*2)),(niv+1)*(h/nivt)-(h/(nivt*2)));
        if(S->patru!=NULL)
            line(S->coloana*(w/colt)-(w/(colt*2)),niv*(h/nivt)-(h/(nivt*2)),S->patru->coloana*(w/colt)-(w/(colt*2)),(niv+1)*(h/nivt)-(h/(nivt*2)));
        deseneaza(S->culoare,niv,nivt,colt,S->coloana);
        parcurgerearbore(S->unu,niv+1,nivt,colt);
        parcurgerearbore(S->doi,niv+1,nivt,colt);
        parcurgerearbore(S->trei,niv+1,nivt,colt);
        parcurgerearbore(S->patru,niv+1,nivt,colt);
    }
}


void adaugarearbore(arbore* &S,matrice a[100][100],int i1,int i2,int j1,int j2,int n)
{
    int i,j,red=0,green=0,blue=0,p;
    p=n*n;
    if(n==0)
        return;
    if(S==NULL)
    {
        S=new arbore;
        for(i=i1;i<=i2;i++)
            for(j=j1;j<=j2;j++)
        {
            red=red+a[i][j].R;
            green=green+a[i][j].G;
            blue=blue+a[i][j].B;
        }
        red=red/p;
        green=green/p;
        blue=blue/p;
        S->culoare=COLOR(red,green,blue);
        S->unu=NULL;
        S->doi=NULL;
        S->trei=NULL;
        S->patru=NULL;
        if(red==a[i1][j1].R && green==a[i1][j1].G && blue==a[i1][j1].B)
            return;
    }
    adaugarearbore(S->unu,a,i1,i1+n/2-1,j1,j1+n/2-1,n/2);
    adaugarearbore(S->doi,a,i1,i1+n/2-1,j2-n/2+1,j2,n/2);
    adaugarearbore(S->trei,a,i2-n/2+1,i2,j1,j1+n/2-1,n/2);
    adaugarearbore(S->patru,a,i2-n/2+1,i2,j2-n/2+1,j2,n/2);
}


int main()
{
    int i,j,x,n=16;
    initwindow(w,h);
    readimagefile("test16.bmp",1,1,n,n);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
           {
              x=getpixel(j,i);
              a[i][j].R=RED_VALUE(x);
              a[i][j].G=GREEN_VALUE(x);
              a[i][j].B=BLUE_VALUE(x);

           }
    adaugarearbore(S,a,1,n,1,n,n);
    coloana(S);
    parcurgerearbore(S,1,nrniveluri(S),nrcoloane(S));
    readimagefile("test16.bmp",0,0,100,100);
    cout<<nrcoloane(S);
    getch();
    return 0;
}
