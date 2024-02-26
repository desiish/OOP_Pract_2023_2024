#include <iostream>

//Да се напише функция, която сортира масив от числа по подадена сортировка.

using std::cout;

void bubbleSort(int* arr, size_t size) {
    unsigned lastSwapedIndex = size - 1;
    for (int i = 0; i < size - 1; i++)
    {
        int currentIterLastSwapped = 0;
        for (int j = 0; j < lastSwapedIndex; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                currentIterLastSwapped = j;
            }
        }
        if (currentIterLastSwapped == 0)
            return;
        lastSwapedIndex = currentIterLastSwapped;
    }
}

void selectionSort(int* arr, size_t size) {
    for (size_t i = 0; i < size - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(int* arr, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        int key = arr[i];
        size_t j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

enum class SortType {
    BUBBLE_SORT,
    SELECTION_SORT,
    INSERTION_SORT,
    UNKNOWN
};

enum class ResponseCode {
    OK,
    INVALID_SORTING_TYPE
};

struct Response {
    int* arr;
    size_t size;
    ResponseCode code;
};

Response sort(int* arr, size_t size, SortType type) {
    switch (type) {
    case SortType::BUBBLE_SORT: bubbleSort(arr, size); break;
    case SortType::INSERTION_SORT: insertionSort(arr, size); break;
    case SortType::SELECTION_SORT: selectionSort(arr, size); break;
    default: return { arr, size, ResponseCode::INVALID_SORTING_TYPE };
    }

    return { arr, size, ResponseCode::OK };
}
