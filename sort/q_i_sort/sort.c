/*
 * Implementation of quicksort + insertion sort algorithm
 * Benchmark for 50 000 000 int elements (gcc):
 * with O3 optimisation flag
 * ONLY QUICKSORT             - 5.104 sec
 * QUICKSORT + INSERTION SORT - 4.513 sec
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/time.h>

static void sys_er( const char *er ) {
	perror( er );
	exit( EXIT_FAILURE );
}

static void *xmalloc( int bytes ) {
	void *ptr = malloc( bytes );
	if ( !ptr ) sys_er( "xmalloc: malloc" );
	return ptr;
}

static inline int getRandom( int min, int max ) { return rand( ) % ( max + 1 - min ) + min; }

static int *fillArr( int size ) {
	int *arr = (int *)xmalloc( size * sizeof( int ) );
	srand( time( NULL ) );
	for ( int i = 0; i < size; ++i ) arr[i] = getRandom( 1, size - 1 );
	return arr;
}

#define swap( a, b ) \
	int temp = a;    \
	a        = b;    \
	b        = temp;

static int partition( int *arr, int low, int high ) {
	int pivot = arr[high];
	int left = low - 1, right = high;
	while ( 1 ) {
		while ( arr[++left] < pivot ) {}
		while ( right && arr[--right] > pivot ) {}
		if ( left >= right ) break;
		swap(arr[left], arr[right]);
	}
	swap(arr[left], arr[high]);
	return left;
}

static void insertion_sort(int *left, int *right){
	int *pi = left + 1;
	while(pi <= right){
		int key = *pi;
		int *pj = pi - 1;

		while(pj >= left && *pj > key){
			*(pj + 1) = *pj;
			--pj;
		}

		*(pj + 1) = key;
		++pi;
	}
}

/* static void insertion_sort( int *left, int *right ) { */
/* 	int min = *left, *pmin = left, *pi = left + 1; */

/* 	while ( pi <= right ) { */
/* 		if ( *pi < min ) { */
/* 			pmin = pi; */
/* 			min  = *pi; */
/* 		} */
/* 		++pi; */
/* 	} */
/* 	*pmin = *left; */
/* 	*left = min; */

/* 	pi = left + 2; */
/* 	while ( pi <= right ) { */
/* 		int  h  = *pi; */
/* 		int *pj = pi - 1; */

/* 		while ( h < *pj ) { */
/* 			*( pj + 1 ) = *pj; */
/* 			--pj; */
/* 		} */
/* 		*( pj + 1 ) = h; */
/* 		++pi; */
/* 	} */
/* } */

static void quicksort( int *arr, int low, int high ) {
	if ( low >= high ) return;
	if(high - low <= 50){
		insertion_sort(&arr[low], &arr[high]);
		return;
	}
	int point = partition( arr, low, high );
	quicksort( arr, low, point - 1 );
	quicksort( arr, point + 1, high );
}

static inline void sort( int *arr, int len ) { quicksort( arr, 0, len - 1 ); }

static void printArr( int *arr, int size ) {
	printf( "First 10:    " );
	for ( int i = 0; i < 10; ++i ) printf( "%d  ", arr[i] );
	printf( "\nLast 10:     " );
	for ( int i = size - 10; i < size; ++i ) printf( "%d  ", arr[i] );
}

static double getTime( ) {
	static double  t0;
	struct timeval tv;
	gettimeofday( &tv, NULL );
	double h = t0;
	t0       = tv.tv_sec + tv.tv_usec / 1000000.;
	return t0 - h;
}

static void test( int *arr, int size ) {
	puts( "\nBefore sorting" );
	printArr( arr, size );

	getTime( );
	sort( arr, size );
	double time = getTime( );

	puts( "\nAfter sorting" );
	printArr( arr, size );

	printf( "\n\nQuicksort took %.4f to sort %d elements\n", time, size );
}

#define SIZE 50000000
int main( ) {
	int *arr  = fillArr( SIZE );
	test( arr, SIZE );

	return 0;
}
