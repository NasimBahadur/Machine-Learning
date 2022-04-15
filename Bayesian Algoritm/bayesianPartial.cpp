#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<vector>
#include<iostream>
#include<fstream>
using namespace std ;

vector <string> avalue, cvalue ;
double prior_value;

int numberofobject = 0 ;
double prior(string cl);

int findOccurance(string att, string cl)
{
    FILE *fptr;
    char a[100], c[100] ;
    int count = 0 ;
    if ((fptr = fopen("data.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    while (fscanf(fptr, "%s %s", &a, &c)!= EOF){
        string s = "", s2 = "" ;
        for(int i=0; i<strlen(a); i++) s += a[i] ;
        for(int i=0; i<strlen(c); i++) s2 += c[i] ;
        if(s == att && s2 == cl) count++ ;
    }
    fclose(fptr);
    return count ;
}


int findOccurance2(string cl)
{
    FILE *fptr;
    char a[100], c[100] ;
    int count = 0 ;
    if ((fptr = fopen("data.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    while (fscanf(fptr, "%s %s", &a, &c)!= EOF){
        string s2 = "" ;
        for(int i=0; i<strlen(c); i++) s2 += c[i];
        if(s2 == cl) count++ ;
    }
    fclose(fptr);
    return count ;
}
int test()
{
    char m[100],n[100];
    cout<<" Enter attribute and class "<<endl;
    cin>>m>>n;
    FILE *fptr;
    char a[100], c[100] ;
    double b;
    int count = 0 ;
    if ((fptr = fopen("likelyhood.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    while (fscanf(fptr, "%s %s %lf", &a, &c, &b)!= EOF){
        string s = "", s2 = "" ;
        for(int i = 0 ; i < strlen(a) ; i++) s += a[i] ;
        for(int i = 0 ; i < strlen(c) ; i++) s2 += c[i] ;
        if(s == m && s2 == n){
            double zoom = b*prior(n);
            cout<<" The chances of said attribute and class to occur are " << zoom << endl;
        }
    }
}

double prior(string cl)
{
    FILE *fptr;
    char  c[100] ;
    double b;
    int count = 0 ;
    if ((fptr = fopen("prior.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    while (fscanf(fptr, "%s %lf",&c, &b)!= EOF){
        string s2 = "" ;
        for(int i = 0 ; i < strlen(c) ; i++) s2 += c[i] ;
        if(s2 == cl) return b;
    }
}



int main() {
    char a[100], c[100];
    FILE *fptr;
    ofstream fileout,fileout1;
    if ((fptr = fopen("data.txt", "r")) == NULL) { /*file is read here*/
        printf("Error! opening file");
        exit(1);
    }
    string s = "" ;
    while (fscanf(fptr, "%s %s", &a, &c)!= EOF){
         printf("%s %s", a, c);
         printf("\n") ;
         numberofobject++ ;

         bool flag = false ;
         string s = "" ;
         for(int i = 0 ; i < strlen(a) ; i++){
            s += a[i] ;
            /*char array is converted into string*/
         }
         for(int i = 0 ; i < avalue.size() ; i++){
            if(s == avalue[i]) {
                flag = true ;
                /*only hold the identical value of the attribute*/
            }
         }
         if(!flag) avalue.push_back(s) ;

         flag = false ;
         s = "" ;
         for(int i=0; i<strlen(c); i++) s += c[i];
         for(int i=0; i<cvalue.size(); i++)
            if(s == cvalue[i])
                flag = true ;
         if(!flag) cvalue.push_back(s) ;
    }
    printf("%d\n", numberofobject) ;
    for(int i = 0 ; i < avalue.size() ; i++)
        cout<< avalue[i] << endl ;

    for(int i = 0 ; i < cvalue.size() ; i++)
        cout<< cvalue[i] << endl ;

    fileout.open("likelyhood.txt");
    fileout1.open("prior.txt");

    for(int i = 0 ; i < cvalue.size() ; i++){
        for(int j = 0 ; j < avalue.size() ; j++){
            int n = findOccurance(avalue[j], cvalue[i]) ;
            int m = findOccurance2(cvalue[i]) ;
            prior_value = (1.00*m) / numberofobject ;
            /*Prior knowledge*/
            double likelihood = (1.00*n) / m ;
            fileout << avalue[j] << " " << cvalue[i] << " "  << likelihood << " "<< endl;
            /*write the likelihood knowledge in likelihood.txt*/
        }
            fileout1 << cvalue[i] << " "  << prior_value << endl;
    }

    fileout.close();
    fileout1.close();
    fclose(fptr);
    int decide;
    cout<<" Do you want to test (press 1 if yes) " <<endl;
    cin>>decide;
    if(decide==1){
        cout<<"How many times do you want to test?"<<endl;
        cin>>decide;
        for(int i=0; i<decide; i++) test();
    }
    return 0;
}

