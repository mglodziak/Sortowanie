#ifndef SORT_H
#define SORT_H


//sortowania do typu
void SelectionSort( int *t, int nSize );
void BubbleSort( int *t, int nSize );
void InsertionSort( int *t, int nSize );
void MixedSort( int *t, int nSize );
void HalfSort( int *t, int nSize ); // sortowanie po³ówkowe
void HeapSort( int* tab, int nSize );
void Update( int* tab, int left, int right );

//sorty inne
void QuickSort( int* tab, int left_index, int right_index );
void MergeSort( int* pTab, int* ptmp, int nSize, int left_index, int right_index );
void Merge( int* pTab, int* ptmp, int nSize, int l, int m, int r );
int OtherMergeSort( int* tab, int nSize );
void CopySerie( int* tab, int* temp, int nSize, int* i, int* ix );
bool copy( int* tab, int* temp, int nSize, int* i, int* ix );

typedef void( *pF )(int*, int);
#endif
