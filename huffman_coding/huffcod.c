/*
 * Implementation of huffman coding greedy algorithm
 */

#include <stdio.h>
#include <stdlib.h>

#include "frequency.c"

#define PRINT_START 0
#define PRINT_TEMP_NODES 0

typedef unsigned char uchar_t;

uchar_t number_of_nodes = 1;

void system_error(char *e);

typedef struct Node
{
	char data;
	size_t freq;
	struct Node *left, *right;
} Node;

typedef struct Priority_Queue
{
	size_t size;
	Node **array;
} Priority_Queue;

Node * create_new_node(char data, size_t freq)
{
	Node *new_node = xmalloc(sizeof(Node));
	if(!new_node) system_error("xmalloc new_node error");

	new_node->left = new_node->right = NULL;
	new_node->data = data;
	new_node->freq = freq;

	return new_node;
}

Priority_Queue * create_pQueue(size_t amount)
{
	Priority_Queue * pQueue = xmalloc(sizeof(Priority_Queue));
	if(!pQueue) system_error("xmalloc pQueue error");

	pQueue->size = 0;
	pQueue->array = xmalloc(sizeof(Node) * amount);

	return pQueue;
}

void sequence_priority_queue(Priority_Queue *pQueue)
{
	int max = pQueue->size - 1;
	for(int i = 0; i < max; ++i)
	{
		for(int j = 0; j < max; ++j)
		{
			if(pQueue->array[j]->freq > pQueue->array[j+1]->freq)
			{
				Node *temp = pQueue->array[j];
				pQueue->array[j] = pQueue->array[j+1];
				pQueue->array[j+1] = temp;
			}
		}
	}
}

Priority_Queue * fill_priority_queue(char symbol[], size_t freq[], size_t amount)
{
	Priority_Queue *pQueue = create_pQueue(amount);

	for(size_t i = 0; i < amount; ++i)
	{
		pQueue->size++;
		pQueue->array[i] = create_new_node(symbol[i], freq[i]);
	}

	sequence_priority_queue(pQueue);

#if PRINT_START
	for(int i = 0; i < pQueue->size; ++i)
		printf("%c - %ld\n", pQueue->array[i]->data, pQueue->array[i]->freq);
	printf("\n");
#endif

	return pQueue;
}

void add_branches(Priority_Queue *pQueue)
{
	Node *left, *right = NULL;

	while(pQueue->size != 1)
	{
		left = pQueue->array[0];
		right = pQueue->array[1];

		Node *temp = create_new_node('$', pQueue->array[0]->freq + pQueue->array[1]->freq);
		temp->left = left;
		temp->right = right;

		for(size_t i = 0; i < pQueue->size - 1; ++i)
			pQueue->array[i] = pQueue->array[i+1];

		pQueue->array[0] = temp;
		pQueue->size--;
		++number_of_nodes;

		sequence_priority_queue(pQueue);

#if PRINT_TEMP_NODES
		for(int i = 0; i < pQueue->size; ++i)
			printf("%c - %ld\n", pQueue->array[i]->data, pQueue->array[i]->freq);
		printf("\n");
#endif
	}
}

Priority_Queue * create_tree(char symbol[], size_t freq[], size_t amount)
{
	Priority_Queue *pQueue = fill_priority_queue(symbol, freq, amount);
	add_branches(pQueue);

	return pQueue;
}

Node * put_tree_in_node(Priority_Queue *pQueue)
{
	Node *new_node = xmalloc(sizeof(Node));
	if(!new_node) system_error("new_node xmalloc error");
	new_node = pQueue->array[0];
	return new_node;
}

void print_codeword(Node *root, uchar_t codeword[], uchar_t top)
{
	if(root->left)
	{
		codeword[top] = 0;
		print_codeword(root->left, codeword, top + 1);
	}
	if(root->right)
	{
		codeword[top] = 1;
		print_codeword(root->right, codeword, top + 1);
	}
	if(!root->left && !root->right)
	{
		printf("%c ", root->data);
		for(int i = 0; i < top; ++i)
			printf("%d", codeword[i]);
		printf("\n");
	}
}

void huffman_coding(char symbol[], size_t freq[], size_t amount)
{
	Priority_Queue *pQueue = create_tree(symbol, freq, amount);

	Node *root = put_tree_in_node(pQueue);

	uchar_t codeword[number_of_nodes];

	print_codeword(root, codeword, 0);
}

int main()
{
	Sym_Freq *sfa = count_freq("text.txt");

#if CHECK
	for(int i = 0; i < sfa->freq->amount; ++i)
		printf("%2c - %ld\n", sfa->symbols[i], sfa->freq->freq[i]);
#endif

	huffman_coding(sfa->symbols, sfa->freq->freq, sfa->freq->amount);

	return 0;
}

void system_error(char *e)
{
	perror(e);
	exit(EXIT_FAILURE);
}

void * xmalloc(size_t size)
{
	void *ptr = malloc(size);
	if(!ptr)
		system_error("malloc ptr error");
	return ptr;
}
