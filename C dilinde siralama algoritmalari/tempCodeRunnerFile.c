 int partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low - 1, j = high + 1;
 
    while (1) {
 
        do {
            i++;
        } while (arr[i] < pivot);
 
        do {
            j--;
        } while (arr[j] > pivot);
 
        if (i >= j)
            return j;
 
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
 
int partition_r(int arr[], int low, int high)
{
    srand(time(0));
    int random = low + rand() % (high - low);
 
    int temp = arr[random];
    arr[random] = arr[low];
    arr[low] = temp;
 
    return partition(arr, low, high);
}
 
void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int pi = partition_r(arr, low, high);
 
        quickSort(arr, low, pi);
        quickSort(arr, pi + 1, high);
    }
}