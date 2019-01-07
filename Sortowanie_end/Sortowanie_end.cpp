#include "stdafx.h"
#include <stdio.h>
#include <math.h> 
#include <time.h>
#include <stdlib.h>
#include "Sort.h"
#include <string.h>
#include <iostream>
#include <string>

using namespace std;


#define DEBUG_TEST

int CreateTab( int** pTab, int nSize ); // tworzy tablicê
int CopyTab( int *pTab1, int* pTab2, int nSize ); // kopiuje pierwsza tablice do drugiej
void ShowTab( int *t, int nSize ); // wyœwietla tablicê
void PutinTab( int* pTab, int nSize, int zakres ); // wype³nia pierwsza tablice pseudolosowymi liczbami w zakresie rownym rozmiarowi tablicy
int Bigger( int nSize, int x ); //jesli podany rozmiar tablicy jest mniejszy od ilosci elementow kontrolnego wydruku, zwroci mniejszy argument

int main( int argc, char * argv[] )
{
	int ilosc_elementow_tablicy = 1000;
	int zakres = 100;
	int wyswietlane_elementy = 20;




	cout << "Witaj w programie do porownania szybkosci 9 roznych sortowan.";
	while (true)
	{
		cout << "Instrukcja: w parametrach podawaj jedynie liczby calkowite. W innym przypadku program wczyta jedynie te cyfry, ktore pojawia sie przed pierwszym znakiem innym niz cyfra";
		cout << "\n\nAby kontunuowac wybierz:\n\n";
		cout << "1 - Zmien liczbe elementow do posortowania. Obecna wartosc " << ilosc_elementow_tablicy<< " \n";
		cout << "2 - Zmien zakres elementow generowanych losowo. Obecna wartosc: 0 - " << zakres << "\n";
		cout << "3 - Zmien liczbe elementow do wyswietlenia dla kazdego sortowania (zalecana ponizej 30). Obecna wartosc " << wyswietlane_elementy << "\n";
		cout << "4 - Testuj sortowania\n";
		cout << "5 - Zakoncz program\n\n";

		int wybor;
		cin >> wybor;
		switch (wybor)
		{
			
		case 1: 
		{
			cout << "Podaj liczbe elementow do posortowania. Obecna wartosc " << ilosc_elementow_tablicy<<"\n"; 
			string temp1 = "0";
			getline( cin>>ws, temp1 );
			ilosc_elementow_tablicy = atoi( temp1.c_str() );
			if (ilosc_elementow_tablicy < 100)
			{
				cout << "Liczba elementow nie moze byc mniejsza niz 100. Obecna wartosc 100\n\n";
				ilosc_elementow_tablicy = 100;
				break;
			}
			system( "cls" );
			break;
		}
		case 2:
		{
			cout << "Podaj koncowy zakres elementow generowanych losowo. Obecna wartosc: 0 - " << zakres << "\n";
			string temp1 = "0";
			getline( cin >> ws, temp1 );
			zakres = atoi( temp1.c_str() );
			if (zakres < 3)
			{
				cout << "Zakres nie moze byc mniejszy niz 3. Obecna wartosc 3";
				zakres = 3;
				break;
			}
			system( "cls" );
			break;
		}
		case 3:
		{
			cout << "Podaj liczbe elementow do wyswietlenia. Obecna wartosc " << wyswietlane_elementy << "\n";
			string temp1 = "0";
			getline( cin >> ws, temp1 );
			wyswietlane_elementy = atoi( temp1.c_str() );
			if (wyswietlane_elementy < 2)
			{
				cout << "Liczba elementow wyswietlanych nie moze byc mniejsza niz 2. Obecna wartosc 2";
				wyswietlane_elementy = 2;
				break;
			}
			system( "cls" );
			break;
		}

		
		case 4:
		{
			pF ft[] = { SelectionSort, BubbleSort, InsertionSort, MixedSort, HalfSort, HeapSort };
			const char* Names[] = { "SelectionSort", "BubbleSort","InsertionSort", "MixedSort", "HalfSort",  "HeapSort" }; //tablica nazw sortowañ
			int tabSize = ilosc_elementow_tablicy;


			//----------------------------

			int* pTab1 = NULL;
			int* pTab2 = NULL;

			if (!CreateTab( &pTab1, tabSize )) //!!! popr
			{
				printf( "ERROR: Nie mozna zaalokowac pamieci tab1\n" );
				return 0;
			}
			PutinTab( pTab1, tabSize, zakres ); //!!! popr
			if (!CreateTab( &pTab2, tabSize ))
			{
				printf( "ERROR: Nie mozna zaalokowac pamieci tab2\n" );
				return 0;
			}
			int ftSize = sizeof( ft ) / sizeof( pF ); //rozmiar tablicy sortowania
#ifdef DEBUG_TEST
			printf( "Tablica wyjsciowa pierwsze %d elementow", Bigger( tabSize, wyswietlane_elementy ) );
			ShowTab( pTab1, Bigger( tabSize, wyswietlane_elementy ) );
			printf( "\n\nTrwa sortowanie, prosze czekac...\n\n" );
#endif
			clock_t start; //start "stopera"
			clock_t stop; // stop stopera
			double time; //czas dzia³ania programu
			for (int i = 0; i < ftSize; i++)
			{
				if (!CopyTab( pTab1, pTab2, tabSize ))
				{
					printf( "ERROR: blad kopiowania tablic\n" );
					return 0;
				} //kopiuje jedna tablice do drugiej
				start = clock();
				ft[i]( pTab2, tabSize ); //wywo³anie funkcji sortuj¹cej
				stop = clock();
				time = (double)(stop - start) / CLOCKS_PER_SEC;

#ifdef DEBUG_TEST
				ShowTab( pTab2, Bigger( tabSize, wyswietlane_elementy ) );
#endif
				printf( "\nCzas sortowania %s: %f\n", Names[i], time );
			}
			//------------- modu³ quick sort -------------------
			if (!CopyTab( pTab1, pTab2, tabSize )) //!!! popr
			{
				printf( "ERROR: blad kopiowania tablic\n" );
				return 0;
			}
			start = clock();
			QuickSort( pTab2, 0, tabSize - 1 );
			stop = clock() - start;
			time = ((double)stop) / CLOCKS_PER_SEC;

#ifdef  DEBUG_TEST
			ShowTab( pTab2, Bigger( tabSize, wyswietlane_elementy ) );
#endif

			printf( "\nCzas sortowania QuickSort: %lf sekund\n", time );
			//-------------------------------------------------


			//------------- modu³ merge sort -------------------

			int* tmp = (int*)malloc( tabSize * sizeof( int ) );
			if (!tmp)
			{
				printf( "\nBrak pamiêci!!\n" );
				return 0;
			}
			memset( tmp, 0, tabSize * sizeof( int ) );

			if (!CopyTab( pTab1, pTab2, tabSize )) //!!! popr5
			{
				printf( "ERROR: blad kopiowania tablic\n" );
				return 0;
			}
			start = clock();
			MergeSort( pTab2, tmp, tabSize, 0, tabSize - 1 );
			stop = clock() - start;
			time = ((double)stop) / CLOCKS_PER_SEC;

#ifdef DEBUG_TEST
			ShowTab( pTab2, Bigger( tabSize, wyswietlane_elementy ) );
#endif
			printf( "\nCzas sortowania Mergesort: %lf sekund\n", time );

			//-------------------------------------------------

			//------------- modu³ other merge sort -------------------
			if (!CopyTab( pTab1, pTab2, tabSize )) //!!! popr
			{
				printf( "ERROR: blad kopiowania tablic\n" );
				return 0;
			}
			start = clock();
			if (!OtherMergeSort( pTab2, tabSize )) //!!! popr
			{
				printf( "ERROR: blad przydzielania pamieci\n" );
				return 0;
			}
			stop = clock() - start;
			time = ((double)stop) / CLOCKS_PER_SEC;

#ifdef  DEBUG_TEST
			ShowTab( pTab2, Bigger( tabSize, wyswietlane_elementy ) );
#endif

			printf( "\nCzas sortowania OtherMergeSort: %lf sekund\n", time );
			//-------------------------------------------------

			free( pTab1 );
			free( pTab2 ); 
			break;
		}
		case 5:
			exit( 0 );
		}

	}
	return 0;
}
	
	
	
	
	//------------
int CreateTab( int **pTab, int nSize )
{
	*pTab = ( int* )malloc( nSize * sizeof( int ) );
	if( !pTab )
		return 0;

	memset( *pTab, 0, ( nSize ) * sizeof( int ) );
	return 1;
}
//------------
int CopyTab( int *pTab1, int* pTab2, int nSize )
{
	memcpy( pTab2, pTab1, ( nSize ) * sizeof( int ) );
	if( !pTab2 )
		return 0;
	return 1;
}
//------------
void ShowTab( int *t, int nSize )
{
	printf( "\n" );
	for( int i = 0; i < nSize; i++ )
	{
		printf( "%d ", *t++ );
	}
}
//------------
void PutinTab( int* pTab, int nSize, int zakres )
{
	srand( ( unsigned int )time( NULL ) );
	int* p = pTab;
	for( int i = 0; i < nSize; i++ )
	{
		*p++ = rand( ) % zakres;

	}
}
//------------
int Bigger( int nSize, int x )
{
	int res = ( nSize >= x ) ? x : nSize;
	return res;
}