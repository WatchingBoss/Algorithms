/*
 * Implementation of quicksort sorting algorithm
 * Benchmark for 1 000 000 int elements (gcc):
 * No optimisation:      0.17 sec
 * O3 optimisation flag: 0.08 sec
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

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

static void quicksort( int *arr, int low, int high ) {
	if ( low >= high ) return;
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

int main( ) {
	int  size = 1000000;
	int *arr  = fillArr( size );
	test( arr, size );

	return 0;
}
