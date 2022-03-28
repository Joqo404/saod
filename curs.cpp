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

struct record {
    char author[12];
    char title[32];
    char publisher[16];
    short int year;
    short int num_of_page;
};

struct Vertex {
    record* data;
    Vertex* left;
    Vertex* right;
    Vertex* root;
};

void scan_database(record* Array, record** A, int n)
{
	FILE* database;
	database = fopen("testBase1.dat", "rb");
	fread((record*)Array, sizeof(record), n, database);
	fclose(database);
	for (int i = 0; i < n; i++)
	{
		A[i] = &Array[i];
	}
}

/*void quicksort(record* arr, int l, int r) 
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
}*/

void print_database(record* A, int n)
{
	int temp = 0;
	for (int i = 0; i < n; i++)
	{
		cout << i << ". " << A[i].author << " " << A[i].title << " " << A[i].publisher << " " << A[i].year << "\n";

		if ((i % 20 == 0) && (i != 0))
		{
			cout << "\nContinue? 0/1: ";
			scanf("%d", &temp);
			if (temp == 0) break;
			else system("cls");
		}
	}
	system("pause");
}

void print_array(record** A, int n)
{
	int temp = 0;
	for (int i = 0; i < n; i++)
	{
		cout << i << ". " << A[i]->author << " " << A[i]->title << " " << A[i]->publisher << " " << A[i]->year << "\n";
		if ((i % 20 == 0) && (i != 0))
		{
			cout << "\nContinue? 0/1: ";
			scanf("%d", &temp);
			if (temp == 0) break;
			else system("cls");
		}
	}
	system("pause");
}

int main()
{
	int n = 4000, temp, ind, k = -1;
	
	record Array[n];
	record* A[n];

    
    scan_database(Array, A, n);
    
    while (1)
	{

		cout << "1 - Print BD " << endl;
		cout << "2 - Print Array " << endl;
		cout << "3 - Search " << endl;
		cout << "4 - Tree " << endl;
		cout << "5 - Coding " << endl;
		cout << "0 - End " << endl;
		scanf("%d", &temp);
		switch (temp)
		{
		case 1:
			print_database(Array, n);
			break;
		case 2:
			print_array(A, n);	
			break;
		/*case 3:
			search(A, n, k, ind);
			break;
		case 4:
			if(k < 0)
				cout << "Search first\n";
			else
				tree(&A[ind], k);
			break;
		case 5:
			coding(n);
            break;	*/
		default:
			return 1;
		}
		system("cls");
	}
    
    //print_data(exmp);
    
    cout << endl << endl << endl;
    return 0;
}
