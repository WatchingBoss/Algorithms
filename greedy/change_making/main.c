#include <stdio.h>
#include <stdlib.h>

void *xrealloc( void *ptr, int bytes ) {
	ptr = realloc( ptr, bytes );
	if ( ptr == NULL ) {
		perror( "realloc error" );
		exit( EXIT_FAILURE );
	}
	return ptr;
}

typedef struct {
	size_t coin, count, times;
} coin_value;

void add_coin( coin_value **c_v, size_t count, size_t coin, size_t *j ) {
	size_t temp_j = *j;

	coin_value *temp =
	    (coin_value *)xrealloc( *c_v, sizeof( coin_value ) * ( temp_j + 1 ) );
	temp[temp_j].coin  = coin;
	temp[temp_j].count = count;
	temp[0].times      = ++temp_j;

	*c_v = temp;
	*j   = temp_j;
}

coin_value *change_making( size_t coins[], size_t size, size_t value ) {
	coin_value *c_v = NULL;

	for ( size_t i = 0, j = 0; i < size; ++i ) {
		size_t count = 0;
		while ( value >= coins[i] ) {
			++count;
			value -= coins[i];
		}
		if ( count ) add_coin( &c_v, count, coins[i], &j );
	}

	return c_v;
}

int main( ) {
	size_t coins[] = { 25, 10, 5, 1 };
	size_t size    = sizeof coins / sizeof *coins;
	size_t value   = 0;

	printf( "What value you want to get: " );
	fscanf_s( stdin, "%zd", &value );

	coin_value *c_v = change_making( coins, size, value );

	printf( "To get %zd we need:\n", value );
	for ( size_t i = 0; i < c_v[0].times; ++i )
		printf( "\t%2zd coins of %zd denomination\n", c_v[i].count, c_v[i].coin );

	return 0;
}
