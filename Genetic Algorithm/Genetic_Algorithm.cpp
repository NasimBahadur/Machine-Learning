#include<bits/stdc++.h>
using namespace std;

int a[8]={0}, b[8]={0}, c[8];

struct chromosome
{
    int a, b;
    double fitness ;
} temp, dvalue[6], par[6];


int f(int a, int b)
{
    return 2*a*a + 3*b - 38 ;
}

void Fitness()
{
    for(int i = 0 ; i < 6 ; i++)
    {
        int fVal = abs(f(dvalue[i].a, dvalue[i].b)) ;
        dvalue[i].fitness = 1.00/fVal ;
    }
}

void copyToPar(int x, int y)
{
    par[y].a = dvalue[x].a ;
    par[y].b = dvalue[y].b ;
}

void Parent()
{
    for(int i = 0 ; i < 6 ; i++)
    {
        for(int j = 0 ; j < 6 ; j++)
        {
            if(dvalue[i].fitness < dvalue[j].fitness)
            {
                temp = dvalue[i] ;
                dvalue[i] = dvalue[j] ;
                dvalue[j] = temp ;
            }
        }
    }

    int cur = 0 ;
    for(int i = 0 ; i < 6 ; i++)
    {
        int randVal = rand() % 9 ;
        if(randVal == 0 || randVal == 6 || randVal == 7)
        {
            copyToPar(0, i) ;
        }
        else if(randVal == 1 || randVal == 8)
            copyToPar(1, i) ;
        else if(randVal == 2)
            copyToPar(2, i) ;
        else if(randVal == 3)
            copyToPar(3, i) ;
        else if(randVal == 4)
            copyToPar(4, i) ;
        else if(randVal == 5)
            copyToPar(5, i) ;
    }
}

void binary_conversion(int ar[],int i,int n){
    while(n!=0)
    {
        ar[i] = n%2;
        n = n/2;
        i--;
    }
}

void crossOver(int x, int y)
{
    int p=dvalue[x].a, q=dvalue[x].b, s=dvalue[y].a, t=dvalue[y].b, i=3, j=7;
    binary_conversion(a,i,p);
    binary_conversion(a,j,q);
    binary_conversion(b,i,s);
    binary_conversion(b,j,t);

    int r = rand() % 8;

    for(int i = 0; i<r; i++)
        c[i] = a[i];

    for(int i = r; i<8; i++)
        c[i] = b[i];

    p = c[0]*8 + c[1]*4 + c[2]*2 + c[3]*1;
    q = c[4]*8 + c[5]*4 + c[6]*2 + c[7]*1;

    dvalue[x].a = p;
    dvalue[x].b = q;
}

void choose_parent()
{
    for(int i=0; i<6; i++)
    {
        crossOver(i,i+1);
    }
    crossOver(5,0);
}

void mutation()
{
    int gen = 8 * 6;
    int mutation = gen*0.1;
    vector<int> r;
    for(int i = 0; i<mutation; i++)
    {
        int c = rand() % gen;
        r.push_back(c);
    }
    for(int j = 0; j<mutation; j++)
    {
        int c=r[j]/8, n=r[j]%8, a[8]={0}, p=dvalue[c].a, q=dvalue[c].b, i=3, k=7;
        binary_conversion(a,i,p);
        binary_conversion(a,k,q);
        (a[n] == 1)?a[n] = 0:a[n] = 1;
        p = a[0]*8 + a[1]*4 + a[2]*2 + a[3]*1;
        q = a[4]*8 + a[5]*4 + a[6]*2 + a[7]*1;
        dvalue[c].a = p;
        dvalue[c].b = q;
    }
}

int main()
{
    for(int i = 0 ; i < 6 ; i++)
    {
        int x = rand() % 10 ;
        int y = rand() % 10 ;
        dvalue[i].a = x ;
        dvalue[i].b = y ;
        dvalue[i].fitness = 0 ;
    }

    for(int i = 0 ; i < 400 ; i++)
    {
        printf("Iteration: %d\n", i) ;
        for(int j = 0 ; j < 6 ; j++)
        {
            if(f(dvalue[j].a, dvalue[j].b) == 0)
            {
                printf("Result : %d %d\n", dvalue[j].a, dvalue[j].b) ;
                return 0;
            }
        }
        Fitness() ;
        Parent() ;
        choose_parent() ;
        mutation() ;
        for(int j = 0 ; j < 6 ; j++)
            printf("C%d : %d %d\n",j,dvalue[j].a,dvalue[j].b );
    }
    return 0;
}
