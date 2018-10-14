#include "stdafx.h"
#include "stdint.h"
#include "iostream"
#include "windows.h"
#include <algorithm>
#include <functional>  
#include "stdlib.h"
#include <ctime>
#include "cstdlib"
static int64_t comps_count = 0;
static int64_t swap_count = 0;


void resetCounters() {
	comps_count=0, swap_count = 0;
}

template <class t>
t* copyArray(const t* input, size_t size) {
	t* output = new t[size];
	for (int i = 0; i < size; i++) {
		output[i] = input[i];
	}
	return output;
}

template <class t>
void printArray(const t* input, size_t size) {
	for (size_t i = 0; i < size; i++) {
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}

template <class t>
void swap(t& a, t& b) {
	if (a != b) {
		t temp = a;
		a = b;
		b = temp;
		swap_count++;
	}
}

template <class t>
t* selsort(const t* input, size_t size) {
	t* result = copyArray(input, size);
	resetCounters();
	size_t i, j;
	int32_t min_index;
	for (i = 0; i < size-1; i++) {
		min_index = i;
		for (j = i + 1; j < size; j++) {
			comps_count++;
			if (result[j] < result[min_index]) {
				min_index = j;
			}
		}
		swap(result[min_index], result[i]);
	}
	return result;
}

template <class t>
t* swapsort(const t* input, size_t size) {
	t* result = copyArray(input, size);
	resetCounters();
		for (size_t i = 0; i < size - 1; i++) {
			for (size_t j = i+1; j < size; j++) {
				comps_count++;
				if (result[i] > result[j]) {
					swap(result[i], result[j]);
				}
			}
		}
	return result;
}

template <class t>
t* shellsort(const t* input, size_t size){
	t* result = copyArray(input, size);
	resetCounters();
	t i, j, step, tmp;
	for (step = size / 2; step > 0; step /= 2)
		for (i = step; i < size; i++)
		{
			tmp = result[i];
			for (j = i; j >= step; j -= step)
			{
				comps_count++;
				if (tmp < result[j - step])
					result[j] = result[j - step];
				else {
					break;
				}
			}
			result[j] = tmp;
		}
	return result;
}

template <class t>
t split(t* arr, size_t left, size_t right) {
	t pivot = left;
	for (int i = left + 1; i < right; i++) {
		comps_count++;
		if (arr[i] < arr[pivot]) {
			if (pivot + 1 != i) {
				swap(arr[pivot], arr[pivot + 1]);
			}
			swap(arr[pivot], arr[i]);
			pivot++;
		}
	}
	return pivot;
}

template <class t>
t* quicksort(const t* input, size_t left, size_t right, t* result, bool first_run = true) {
	if (first_run) {
		result = copyArray(input, right);
		resetCounters();
		first_run = false;
	}
	if (right - left < 2) {
		return result;
	}
	else {
		int pivot = split(result, left, right);
		quicksort(result, left, pivot, result, first_run);
		quicksort(result , pivot + 1, right, result, first_run);
	}
	return result;
}


template <class t>
t* swapsort_1(const t* input, size_t size) {
	t* result = copyArray(input, size);
	bool made_swap;
	for (size_t i = 0; i < size - 1; i++) {
		made_swap = false;
		for (size_t j = 0; j < size - 1 ; j++) {
			comps_count++;
			if (result[j] > result[j+1]) {
				swap(result[j], result[j+1]);
				made_swap = true;
			}
		}
		if (!made_swap) {
			break;
		}
	}
	return result;
}

template <class t>
t* swapsort_2(const t* input, size_t size) {
	t* result = copyArray(input, size);
	resetCounters();
	size_t last_index = size;
	size_t j;
	for (size_t i = 0; i < size-1; i++) {
		for (j = 0; j < size - i - 1; j++) {
			comps_count++;
			if (result[j] > result[j + 1]) {
				swap(result[j], result[j + 1]);
				last_index = j;
			}
		}
	}
	return result;
}

template <class t>
t* insertionsort(const t* input, size_t size){
	t* result = copyArray(input, size);
	resetCounters();
	size_t key, j;
	for (size_t i = 1; i < size ; i++)
	{
		key = result[i];
		j = i - 1;
		comps_count += 2;
		while (j >= 0 && result[j] > key) {
			comps_count+=2;
			result[j + 1] = result[j];
			j=j-1;
		}
		result[j + 1] = key;
	}
	return result;
}

template <class t>
void heapify(t* input, size_t n, size_t i){
	int32_t largest = i; 
	int32_t l = 2 * i + 1; 
	int32_t r = 2 * i + 2;

	comps_count ++;
	if (l < n && input[l] > input[largest]) {
		largest = l;
	}
	comps_count++;
	if (r < n && input[r] > input[largest]) {
		largest = r;
	}
	if (largest != i)
	{
		swap(input[i], input[largest]);
		heapify(input, n, largest);
	}
}

template <class t>
t* heapSort(const t* input, size_t n, t* result, bool first_run=true){
	if (first_run) {
		result = copyArray(input, n);
		resetCounters();
		first_run = false;
	}
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(result, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		swap(result[0], result[i]);

		heapify(result, i, 0);
	}
	return result;
}



int main(){
	srand(time(0));
	SetConsoleOutputCP(1251);
	std::cout << "Сортировка: от 5 до 45 элементов с шагом 5\n";
	for (size_t i = 1; i <= 3; i++)
	{
		switch (i) {
			case 1: {
				std::cout << "Отсортированный массив:\n";
				break;
				}
			case 2: {
				std::cout << "Неотсортированный массив:\n";
				break;
			}
			case 3: {
				std::cout << "Обратно упорядоченный массив:\n";
				break;
			}
		}
		for (size_t n = 5; n <= 45; n = n + 5) {
			int32_t* array = new int32_t[n];
			int32_t* result = new int32_t[n];
			for (size_t i = 0; i < n; i++) {
				array[i] = rand() % 100;
			}
			switch (i) {
				case 1: {
					array = quicksort(array, 0, n, array);
					break;
				}
				case 2: {
					break;
				}
				case 3: {
					std::sort(array, array + n, std::greater<int>());
					break;
				}
			}
			result = insertionsort(array, n);
			std::cout << comps_count << "\t";
			result = selsort(array, n);
			std::cout << comps_count << "\t";
			result = swapsort(array, n);
			std::cout << comps_count << "\t";
			result = swapsort_1(array, n);
			std::cout << comps_count << "\t";
			result = swapsort_2(array, n);
			std::cout << comps_count << "\t";
			result = shellsort(array, n);
			std::cout << comps_count << "\t";
			result = quicksort(array, 0, n, result);
			std::cout << comps_count << "\t";
			result = heapSort(array, n, result);
			std::cout << comps_count << "\t";

			delete[] array, result;
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	return 0;
}

