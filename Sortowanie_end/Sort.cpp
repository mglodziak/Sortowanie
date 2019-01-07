
#include "sort.h"
#include "memory.h"
#include "stdlib.h"
#include "stdio.h"


void BubbleSort( int *t, int nSize ) // SORTOWANIE B¥BELKOWE
{
	int j;
	int temp; // zmienna tymczasowa

	for( int i = 0; i < nSize - 1; i++ )
	{
		for( j = nSize - 1; j>i; j-- )
			if( t[j - 1] > t[j] )
			{
				temp = *( t + j - 1 );
				t[j - 1] = t[j];
				t[j] = temp; //zamiana t[j-1] z t[j]
			}
	}
}
//-----
void SelectionSort( int* tab, int nSize )
{
	for( int i = 0; i <nSize - 1; i++ )
	{
		int min = tab[i];
		int x = i;

		for( int j = i + 1; j < nSize; j++ )
			if( tab[j] < min )
			{
				min = tab[j];
				x = j;
			}
		tab[x] = tab[i];
		tab[i] = min;
	}
}
//-----
void InsertionSort( int* tab, int nSize )
{
	for( int i = 1; i < nSize; ++i )
	{
		int x = tab[i];
		int j = i - 1;

		while( ( j >= 0 ) && ( tab[j] > x ) )
			tab[j + 1] = tab[j--];

		tab[j + 1] = x;
	}
}
//-----
void MixedSort( int* tab, int nSize )
{
	int l = 1;
	int p = nSize - 1;
	int k = nSize - 1;

	while( p > l )
	{
		for( int j = p; j >= l; j-- )
		{

			if( tab[j - 1] > tab[j] )
			{
				int x = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = x;
				k = j;
			}
		}
		l = k + 1;

		for( int j = l; j <= p; j++ )
		{
			if( tab[j - 1] > tab[j] )
			{
				int x = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = x;
				k = j;
			}
		}
		p = k - 1;
	}
}
//-----
void HalfSort( int* tab, int nSize )
{
	for( int i = 1; i < nSize; i++ )
	{

		int key = tab[i];
		int left = 0;
		int right = i - 1;
		int m;

		while( left <= right )
		{
			m = ( left + right ) / 2;
			if( key < tab[m] )
				right = m - 1;
			else
				left = m + 1;
		}

		for( int j = i - 1; j >= m; j-- )
			tab[j + 1] = tab[j];

		tab[left] = key;
	}

}
//-----
void HeapSort( int* tab, int nSize )
{
	int l = ( nSize / 2 ) + 1;

	for( l; l >= 0; l-- )
		Update( tab, l, nSize - 1 );

	for( int r = nSize - 1; r > 0; r-- )
	{
		int temp = tab[0];
		tab[0] = tab[r];
		tab[r] = temp;

		Update( tab, 0, r - 1 ); //UpDate( t, 0, r);
	}
}
//-----
void Update( int* tab, int left_index, int right_index )
{
	if( left_index == right_index ) return;
	int l = left_index;
	int j = ( l + 1 ) * 2 - 1;
	int x = tab[l];

	while( j <= right_index )
	{
		if( j < right_index )
			if( tab[j] < tab[j + 1] )
				j++;

		if( x>tab[j] ) break;

		tab[l] = tab[j];
		l = j;
		j = 2 * l + 1;
	}
	tab[l] = x; //warunek kopca zachowany
}
//-----
void QuickSort( int* tab, int left_index, int right_index )
{
	int l = left_index;
	int r = right_index;
	int x = tab[( left_index + right_index ) / 2];

	while( l <= r )
	{
		while( tab[l] < x ) l++;
		while( tab[r] > x ) r--;

		if( l <= r )
		{
			if( l != r )
			{
				int tmp = tab[l];
				tab[l] = tab[r];
				tab[r] = tmp;
			}
			l++;
			r--;
		}
	}

	if( left_index < r ) QuickSort( tab, left_index, r );
	if( l < right_index ) QuickSort( tab, l, right_index );
}
//-----
void MergeSort( int* pTab, int* ptmp, int nSize, int left_index, int right_index )
{
	if( left_index < right_index )
	{
		int middle = ( left_index + right_index ) / 2;
		MergeSort( pTab, ptmp, nSize, left_index, middle );
		MergeSort( pTab, ptmp, nSize, middle + 1, right_index );
		Merge( pTab, ptmp, nSize, left_index, middle, right_index );
	}
}
//-----
void Merge( int* pTab, int* ptmp, int nSize, int left, int m, int r )
{
	memcpy( ptmp, pTab, nSize * sizeof( *pTab ) ); //!!! poprawione memcpy

	int i = left;
	int j = m + 1;
	int k = left;

	while( i <= m && j <= r )
	{
		if( ptmp[i] < ptmp[j] )
			pTab[k++] = ptmp[i++];
		else
			pTab[k++] = ptmp[j++];
	}
	while( i <= m )
		pTab[k++] = ptmp[i++];
}

//-----
int OtherMergeSort( int* tab, int nSize )
{
	int* tmp1 = ( int* )malloc( nSize * sizeof( int ) ); //pomocnicze tablice
	if( !tmp1 )//!!!!!
		return 0;
	memset( tmp1, 0, nSize * sizeof( int ) );

	int* tmp2 = ( int* )malloc( nSize * sizeof( int ) ); //pomocnicze tablice
	if( !tmp2 )
		return 0;
	memset( tmp2, 0, nSize * sizeof( int ) );
	int nSerie;
	do
	{
		int i = 0;		// tab
		int j = 0;		// do tmp1
		int k = 0;		// do tmp2
		while( i < nSize )
		{
			while( ( i < nSize - 1 ) && ( tab[i] <= tab[i + 1] ) )
				tmp1[j++] = tab[i++];
			if( i < nSize )
				tmp1[j++] = tab[i++];
			while( ( i < nSize - 1 ) && ( tab[i] < tab[i + 1] ) )
				tmp2[k++] = tab[i++];
			if( i < nSize )
				tmp2[k++] = tab[i++];
		}

		int koniec1 = j;
		int koniec2 = k;
		nSerie = 0;
		i = j = k = 0;

		while( ( j < koniec1 ) && ( k < koniec2 ) )
		{
			bool koniec = false;
			while( !koniec )
			{
				if( tmp1[j] <= tmp2[k] )
				{
					koniec = copy( tab, tmp1, koniec1, &i, &j );
					if( koniec )
						CopySerie( tab, tmp2, koniec2, &i, &k );
				}
				else
				{
					koniec = copy( tab, tmp2, koniec2, &i, &k );
					if( koniec )
						CopySerie( tab, tmp1, koniec1, &i, &j );
				}
			}
			nSerie++;
		}

		while( j < koniec1 )
		{
			CopySerie( tab, tmp1, koniec1, &i, &j );
			nSerie++;
		}
		while( k < koniec2 )
		{
			CopySerie( tab, tmp2, koniec2, &i, &k );
			nSerie++;
		}
	} while( nSerie > 1 );

	free( tmp1 );
	free( tmp2 );
	return 1;
}
//------------------------------------------------------
void CopySerie( int* tab, int* temp, int nSize, int* ix, int* iy )
{
	bool end = false;
	do
	{
		end = copy( tab, temp, nSize, ix, iy );
	} while( !end );
}

bool copy( int* tab, int* temp, int nSize, int* ix, int* iy )
{
	tab[( *ix )++] = temp[( *iy )++];
	if( *iy == nSize )
		return true;

	return ( temp[*iy - 1] > temp[*iy] );
}
