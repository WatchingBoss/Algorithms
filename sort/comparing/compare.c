#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "sort_alg.c"

static void sys_er( const char *er ) {
	perror( er );
	exit( EXIT_FAILURE );
}

static void *xmalloc( int bytes ) {
	void *ptr = malloc( bytes );
	if ( !ptr ) sys_er( "xmalloc: malloc error" );
	return ptr;
}

static inline int rand_int( int min, int max ) { return rand( ) % ( max + 1 - min ) + min; }

static int *fill_array( int number ) {
	int *arr = (int *)xmalloc( number * sizeof( int ) );
	srand( time( NULL ) );
	for ( int i = 0; i < number; ++i ) arr[i] = rand_int( 1, number - 1 );
	return arr;
}

static void user_input( int *number ) {
	printf( "Enter number of elements: " );
	scanf( "%d", number );
}

static float call_sort( int *arr, int count, void ( *func_ptr )( int *, int ) ) {
	clock_t start = 0, end = 0;

	start = clock( );
	func_ptr( arr, count );
	end = clock( );

	float sort_time = (float)( ( (float)end - (float)start ) / CLOCKS_PER_SEC );
	return sort_time;
}

static void use_sort( int count, void ( *func_ptr )( int *, int ), const char *name ) {
	const int times         = 10;
	float     sort_time_sum = 0;
	for ( int i = 0; i < times; ++i ) {
		int *arr = fill_array( count );
		sort_time_sum += call_sort( arr, count, func_ptr );
		free( arr );
	}

	float avg_time = sort_time_sum / (float)times;

	printf( "%-15s: "
	        "\e[92;1m"
	        "%f"
	        "\e[0;m"
	        " seconds\n",
	        name, avg_time );
}

static void compare( int count ) {
	printf( "\nSorting %d elements: \n", count );

	if ( count <= 50000 ) use_sort( count, bubble_sort, "Bubble sort" );
	if ( count <= 100000 ) {
		use_sort( count, selection_sort, "Selection sort" );
		use_sort( count, insertion_sort, "Insertion sort" );
	}
	if ( count <= 1500000 ) {
		use_sort( count, heapsort, "Heapsort" );
		use_sort( count, merge_sort, "Merge sort" );
	}
	use_sort( count, quicksort, "Quicksort" );
}

int main( ) {
	int number = 0;
	user_input( &number );

	compare( number );

	return 0;
}
