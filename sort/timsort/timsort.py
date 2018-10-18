#!/usr/bin/env python3
"""
Timsort algorithm implementaion in python
"""

import random
import time


def binary_search(arr, item, start, end):
    if start == end:
        if arr[start] > item:
            return start
        return start + 1
    if start > end:
        return start

    mid = round((start + end) / 2)

    if arr[mid] < item:
        return binary_search(arr, item, mid + 1, end)
    if arr[mid] < item:
        return binary_search(arr, item, start, mid - 1)
    return mid


def insertion_sort(arr):
    count = len(arr)
    for index in range(1, count):
        value = arr[index]
        pos = binary_search(arr, value, 0, index - 1)
        arr = arr[:pos] + [value] + arr[pos:index] + arr[index + 1:]
    return arr


def merge(left, right):
    if not left:
        return right
    if not right:
        return left
    if left[0] < right[0]:
        return [left[0]] + merge(left[1:], right)
    return [right[0]] + merge(left, right[1:])


def timsort(arr):
    runs, sorted_runs = [], []
    count = len(arr)
    new_run = [arr[0]]

    for elem in range(1, count):
        if elem == count - 1:
            new_run.append(arr[elem])
            runs.append(new_run)
            break
        if arr[elem] < arr[elem - 1]:
            if not new_run:
                runs.append([arr[elem]])
                new_run.append(arr[elem])
            else:
                runs.append(new_run)
                new_run.clear()
        else:
            new_run.append(arr[elem])

    for run in runs:
        sorted_runs.append(insertion_sort(run))

    sorted_arr = []
    for run in sorted_runs:
        sorted_arr = merge(sorted_arr, run)
    return sorted_arr
#    arr = sorted_arr.copy()


def printing(arr):
    print("First 10:")
    print(arr[:10], end=" ")
    print("\nLast 10:")
    print(arr[len(arr) - 10:], end=" ")
    print("\n")


def test_sort(number):
    arr = [random.randrange(1, number - 1) for i in range(number)]

    print("Before sorting: ")
    printing(arr)

    start = time.clock()
    arr = timsort(arr)
#    timsort(arr)
    end = time.clock()

    print("After sorting: ")
    printing(arr)

    print("Timsort took {:.5f} second to sort {} elements".format(end - start, number))


if __name__ == "__main__":
    test_sort(500)
