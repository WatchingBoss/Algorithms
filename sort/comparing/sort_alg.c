void swap( int *prev, int *seq ) {
	int temp = *prev;
	*prev    = *seq;
	*seq     = temp;
}

void bubble_sort( int *arr, int count ) {
	for ( int i = 0; i < count - 1; ++i )
		for ( int j = 0; j < count - 1; ++j )
			if ( arr[j] > arr[j + 1] ) swap( &arr[j], &arr[j + 1] );
}

void selection_sort( int *arr, int count ) {
	for ( int i = 0; i < count - 1; ++i ) {
		int min = i;
		for ( int j = i + 1; j < count; ++j )
			if ( arr[j] < arr[min] ) min = j;
		swap( &arr[min], &arr[i] );
	}
}

void insertion_sort( int *arr, int count ) {
	for ( int i = 1; i < count; ++i ) {
		int key = arr[i], j = i - 1;
		while ( j >= 0 && arr[j] > key ) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}

static int q_partition( int *arr, int low, int high) {
	int pivot = arr[high], left = low - 1, right = high;
	while ( 1 ) {
		while ( arr[++left] < pivot ) {}
		while ( right && arr[--right] > pivot ) {}
		if ( left >= right ) break;
		swap( &arr[left], &arr[right] );
	}
	swap( &arr[left], &arr[high] );
	return left;
}

static void q_sort( int *arr, int low, int high ) {
	if ( low >= high ) return;
	int point = q_partition( arr, low, high);
	q_sort( arr, low, point - 1 );
	q_sort( arr, point + 1, high );
}

void quicksort( int *arr, int count ) { q_sort( arr, 0, count - 1 ); }

static void h_heapify( int *arr, int count, int index ) {
	int largest = index, left = index * 2 + 1, right = index * 2 + 2;

	if ( left < count && arr[left] > arr[largest] ) largest = left;
	if ( right < count && arr[right] > arr[largest] ) largest = right;

	if ( largest == index ) return;
	swap( &arr[largest], &arr[index] );
	h_heapify( arr, count, largest );
}

void heapsort( int *arr, int count ) {
	for ( int i = count / 2 - 1; i >= 0; --i ) h_heapify( arr, count, i );
	for ( int i = count - 1; i >= 0; --i ) {
		swap( &arr[0], &arr[i] );
		h_heapify( arr, i, 0 );
	}
}

static void m_merging( int *arr, int count, int low, int mid, int high ) {
	int temp[count];
	int first = low, index = low, second = mid + 1;

	for ( ; first <= mid && second <= high; ++index ) {
		if ( arr[first] <= arr[second] )
			temp[index] = arr[first++];
		else
			temp[index] = arr[second++];
	}

	while ( first <= mid ) temp[index++] = arr[first++];
	while ( second <= high ) temp[index++] = arr[second++];

	for ( int i = low; i <= high; ++i ) arr[i] = temp[i];
}

static void m_merge( int *arr, int count, int low, int high ) {
	if ( low >= high ) return;
	int mid = ( low + high ) / 2;
	m_merge( arr, count, low, mid );
	m_merge( arr, count, mid + 1, high );
	m_merging( arr, count, low, mid, high );
}

void merge_sort( int *arr, int count ) { m_merge( arr, count, 0, count - 1 ); }
