#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Dizi elemanlarını yer değiştirir
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble Sort algoritması
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Geçerli eleman bir sonraki elemandan büyükse yerlerini değiştir
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}


void maxHeapify(int arr[], int n, int i) {
    int kok = i; // Kök düğüm olarak başla
    int soldugum = 2 * i + 1; // Sol çocuk düğüm
    int sagdugum = 2 * i + 2; // Sağ çocuk düğüm

    // Sol çocuk düğüm kökten daha büyükse largest güncelle
    if (soldugum < n && arr[soldugum] > arr[kok])
        kok = soldugum;

    // Sağ çocuk düğüm kökten daha büyükse largest güncelle
    if (sagdugum < n && arr[sagdugum] > arr[kok])
        kok = sagdugum;

    // largest kök değilse yer değiştir ve maxHeapify çağır
    if (kok != i) {
        swap(&arr[i], &arr[kok]);
        maxHeapify(arr, n, kok);
    }
}

// Heap Sort algoritması
void heapSort(int arr[], int n) {
    // Max Heap oluştur
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    // Heap'ten birer birer eleman çıkar ve sırala
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]); // En büyük elemanı sondan bir önceki pozisyona taşı
        maxHeapify(arr, i, 0); // Sondan bir önceki pozisyonda yeni maxHeapify çağır
    }
}

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Önceki elemanlarla karşılaştır ve doğru konuma yerleştir
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

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
 //quicsort algoritması
void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int pi = partition_r(arr, low, high);
 
        quickSort(arr, low, pi);
        quickSort(arr, pi + 1, high);
    }
}

// Selection Sort algoritması
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        // Minimum elemanı bul
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Minimum elemanı i. indekse taşı
        swap(&arr[i], &arr[minIndex]);
    }
}

void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < leftSize) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < rightSize) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int size) {
    if (size <= 1) {
        return;
    }
    int mid = size / 2;
    int left[mid];
    int right[size - mid];
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }
    mergeSort(left, mid);
    mergeSort(right, size - mid);
    merge(arr, left, mid, right, size - mid);
}


// Diziyi ekrana yazdır
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n; // boyut değişkeni
    
    printf("Dizinin boyutunu girin: ");
    scanf("%d", &n);

      clock_t start, end;
      double elapsed_time;

//dizi boyutunu bellekte yer ayırma 
    int* arr = (int*)malloc(n * sizeof(int));
    if(n==1000){

    for (int i = 0; i < n; i++) {
        arr[i] = n-i; // 0-1000 arasında ters sıralı sayılar
    }
 
    // Diziyi sırala
  // printf("Oluşturulan dizi: ");
   // printArray(arr, n); 
   
    // Bubble Sort
        start = clock();
        bubbleSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Bubble Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

        //heapshort 
        start = clock();
        heapSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Heap Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
         
         
         //insertionshort
        start = clock();
        insertionSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("İnsertion Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
       
       //quicshort
        start = clock();
        quickSort(arr, 0, n - 1);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Quic Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
        
        
        //selectionshort
        start = clock();
       selectionSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Selection Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

       //mergeshort
        start = clock();
        mergeSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Merge short ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);


    }



else if(n==10000)
{
        for (int i = 0; i < n; i++) {
        arr[i] = n-i; // 0-10000 arasında ters sıralı sayılar
    }
 
    // printf("Oluşturulan dizi: ");
   // printArray(arr, n); 
     // Bubble Sort
        start = clock();
        bubbleSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Bubble Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

        //heapshort 
        start = clock();
        heapSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Heap Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
         
         
         //insertionshort
        start = clock();
        insertionSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("İnsertion Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
       
       //quicshort
        start = clock();
        quickSort(arr, 0, n - 1);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Quic Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
        
        
        //selectionshort
        start = clock();
       selectionSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Selection Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

       //mergeshort
        start = clock();
        mergeSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Merge short ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

}
else if(n==50000)
{
        for (int i = 0; i < n; i++) {
        arr[i] = n-i; // 0-50000 arasında  ters sıralı sayılar
    }
 
   // printf("Oluşturulan dizi: ");
    //printArray(arr, n);

   // Bubble Sort
        start = clock();
        bubbleSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Bubble Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

        //heapshort 
        start = clock();
        heapSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Heap Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
         
         
         //insertionshort
        start = clock();
        insertionSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("İnsertion Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
       
       //quicshort
        start = clock();
        quickSort(arr, 0, n - 1);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Quic Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
        
        
        //selectionshort
        start = clock();
       selectionSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Selection Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

       //mergeshort
        start = clock();
        mergeSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Merge short ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

}
else if(n==100000)
{
        for (int i = 0; i < n; i++) {
        arr[i] = n-i; // 0-100000 arasında ters sıralı sayılar
    }
 
   // printf("Oluşturulan dizi: ");
    //printArray(arr, n);

   // Bubble Sort
        start = clock();
        bubbleSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Bubble Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

        //heapshort 
        start = clock();
        heapSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Heap Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
         
         
         //insertionshort
        start = clock();
        insertionSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("İnsertion Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
       
       //quicshort
        start = clock();
        quickSort(arr, 0, n - 1);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Quic Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
        
        
        //selectionshort
        start = clock();
       selectionSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Selection Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

       //mergeshort
        start = clock();
        mergeSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Merge short ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

}

else if(n==500000)
{
        for (int i = 0; i < n; i++) {
        arr[i] = n-i; // 0-500000 arasında sıralı sayılar
    }
 
   // printf("Oluşturulan dizi: ");
   // printArray(arr, n); 
    // Bubble Sort
        start = clock();
        bubbleSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Bubble Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

        //heapshort 
        start = clock();
        heapSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Heap Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
         
         
         //insertionshort
        start = clock();
        insertionSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("İnsertion Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
       
       //quicshort
        start = clock();
        quickSort(arr, 0, n - 1);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Quic Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
        
        
        //selectionshort
        start = clock();
       selectionSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Selection Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

       //mergeshort
        start = clock();
        mergeSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Merge short ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

}
else if(n==1000000)
{
        for (int i = 0; i < n; i++) {
        arr[i] = n-i; // 0-100000 arasında sıralı sayılar
    }
 
    //printf("Oluşturulan dizi: ");
    //printArray(arr, n); 
   // Bubble Sort
        start = clock();
        bubbleSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Bubble Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

        //heapshort 
        start = clock();
        heapSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Heap Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
         
         
         //insertionshort
        start = clock();
        insertionSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("İnsertion Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
       
       //quicshort
        start = clock();
        quickSort(arr, 0, n - 1);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Quic Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);
        
        
        //selectionshort
        start = clock();
       selectionSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Selection Sort ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

       //mergeshort
        start = clock();
        mergeSort(arr, n);
        end = clock();
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Milisaniye cinsinden süre
        printf("Merge short ile %d elemanlı dizi sıralama süresi: %.2f ms\n", n, elapsed_time);

}


    return 0;
}
