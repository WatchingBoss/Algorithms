#include <stdio.h>
#include <stdlib.h>

typedef struct coin_value
{
	size_t *coin, *count;
} coin_value;

void my_free(coin_value *c_v)
{
	free(c_v->coin);
	free(c_v->count);
}

void add_coin_count(coin_value **c_v, size_t i, size_t count, size_t coin)
{
	*c_v = realloc(*c_v, sizeof *c_v * (i + 1));
	(*c_v)->coin = realloc((*c_v)->coin, sizeof(size_t) * (i + 1));
	(*c_v)->count = realloc((*c_v)->count, sizeof(size_t) * (i + 1));
	(*c_v)->coin[i] = coin;
	(*c_v)->count[i] = count;
}

coin_value * change_making(size_t coins[], size_t size, size_t value)
{
	coin_value *c_v = malloc(sizeof(coin_value));

	for(size_t i = 0; i < size; ++i)
	{
		size_t count = 0;
		while(value >= coins[i])
		{
			++count;
			value -= coins[i];
		}

		printf("Address of c_v: %p\n", &c_v);

		add_coin_count(&c_v, i, count, coins[i]);
		printf("c_v Size: %ld \t coin Size: %ld \t count Size: %ld \n",
			   sizeof *c_v, sizeof *c_v->coin, sizeof *c_v->count);
		printf("Coin: %ld \tCount: %ld\n", c_v->coin[i], c_v->count[i]);
	}

	return c_v;
}

int main()
{
	size_t coins[] = {25, 10, 5, 1};
	size_t size = sizeof coins / sizeof *coins;
	size_t value = 147;

	coin_value *c_v = change_making(coins, size, value);

	printf("To get %ld we require:\n", value);
	for(size_t i = 0; i < sizeof c_v->coin / sizeof c_v->coin[0]; ++i)
		printf("%-2ld coins by %2ld denomination\n", c_v->count[i], c_v->coin[0]);

	my_free(c_v);

	return 0;
}
