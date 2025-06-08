#include "../include/Operations.h"
#include <algorithm>
#include <cstring>

// Helper for dual-pivot quicksort
void dualPivotQuickSort(Entry* arr, int low, int high) {
    if (low < high) {
        // Choose two pivots
        if (arr[low] > arr[high]) std::swap(arr[low], arr[high]);
        Entry pivot1 = arr[low];
        Entry pivot2 = arr[high];
        int lt = low + 1, gt = high - 1, i = lt;
        while (i <= gt) {
            if (arr[i] < pivot1) std::swap(arr[i++], arr[lt++]);
            else if (arr[i] > pivot2) std::swap(arr[i], arr[gt--]);
            else i++;
        }
        std::swap(arr[low], arr[--lt]);
        std::swap(arr[high], arr[++gt]);
        dualPivotQuickSort(arr, low, lt - 1);
        dualPivotQuickSort(arr, lt + 1, gt - 1);
        dualPivotQuickSort(arr, gt + 1, high);
    }
}

void Operations::sort(Entry *entries, int len) {
    dualPivotQuickSort(entries, 0, len - 1);
}

// Binary search for range of exact matches
int* Operations::search(Entry *entries, int len, std::string searchable_name) {
    int left = 0, right = len - 1, found = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (entries[mid].name == searchable_name) {
            found = mid;
            break;
        } else if (entries[mid].name < searchable_name) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    if (found == -1) return nullptr;
    // Find range
    int start = found, end = found;
    while (start > 0 && entries[start - 1].name == searchable_name) --start;
    while (end < len - 1 && entries[end + 1].name == searchable_name) ++end;
    int* result = new int[2]{start, end};
    return result;
}
