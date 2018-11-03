#include "stdafx.h"
#include "stdint.h"
#include "iostream"
#include "windows.h"
#include <algorithm>
#include <functional>  
#include "stdlib.h"
#include <ctime>
#include "cstdlib"
#include "handy.h"
#include "sortings.h"

template <class t>
void swap(t& a, t& b) {
	if (a != b) {
		t temp = a;
		a = b;
		b = temp;
		swap_count++;
	}
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

