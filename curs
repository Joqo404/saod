/*
Егор Смирнов ИП - 013 ВАРИАНТ 81:
B 1 первая бд
C 1 по фамилиям, K = три первые буквы фамилии
S 2 quick sort
D 2 двоичное дерево
E 2 код шеннона
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;
const int N = 4000;

struct Record {
    char author[12];
    char title[32];
    char publisher[16];
    short int year;
    short int num_of_page;
};

struct Vertex {
    Record* data;
    Vertex* left;
    Vertex* right;
    Vertex* root;
};

Record* record()
{
    FILE* flopa;
    Record rec[N];
    flopa = fopen("testBase1.dat", "rb");
    int blopa = 0;
    blopa = fread((Record*)rec, sizeof(Record), N, flopa);
    if (!rec)
    {
        cerr << "opennig error";
        exit(1);
    }
    return rec;
}

void quicksort(Record* arr, int l, int r) 
{
    Record x;
    Record temp;
    int i = l;
    x = arr[i];
    //x = arr[i].author;
    int j = r;
    while (i <= j)
    {
        while (strcmp(arr[i].author , x.author) < 0)
        {
            i += 1;
        }
        while (strcmp(arr[j].author , x.author) > 0)
        {
            j -= 1;
        }
        if (i <= j)
        {
           
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i += 1;
            j -= 1;
        }
    }
    if (l < j)
    {
        quicksort(arr,l,j);
    }
    if (i < r) 
    {
        quicksort(arr,i,r);
    }
}





void print_data(Record rec[])
{
    int k = 0;
    for (int i = 0; i < 4000; i++)
    {
        cout<< i+1 <<") " << rec[i].author << " " << rec[i].title << " " << rec[i].publisher << " " << rec[i].year << " " << rec[i].num_of_page << endl;
        k++;
        if (k == 20)
        {
            cout << "if you want to continue press 1,press 2 if you want stop, press any button to search all data base";
            int temp = 0;
            cin >> temp;
            if (temp == 1)
            {
                k = 0;
            }
            if (temp == 2)
            {
                break;
            }
        }
    }
}

int main()
{
    Record* exmp;
    exmp = record();
    char key[12] = "Глебов М В";
    quicksort(exmp, 0, 3876);
    print_data(exmp);
    cout << endl << endl << endl;
    return 0;
}
