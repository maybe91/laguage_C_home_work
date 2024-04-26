#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>


#define N 10
#define M 100
#define QUEUE_SIZE 100

int Stack_push(int stack[], int* top, int number, int max_size);
int Stack_pop(int stack[], int* top);


typedef struct {
    int dane[QUEUE_SIZE];
    int poczatek;
    int koniec;
    int rozmiar;
    int maksymalny_rozmiar;
} Kolejka;


void Queue__init(Kolejka *queue, int i) {
    queue->poczatek = 0;
    queue->koniec = -1;
    queue->rozmiar = 0;
}


int Queue__push(Kolejka* queue, int number) {
    if (queue->rozmiar == QUEUE_SIZE) {
        return -1;
    }
    queue->koniec = (queue->koniec + 1) % QUEUE_SIZE;
    queue->dane[queue->koniec] = number;
    queue->rozmiar++;
    return 0;
}


int Queue__pop(Kolejka* queue) {
    if (queue->rozmiar == 0) {
        return -2;
    }
    int value = queue->dane[queue->poczatek];
    queue->poczatek = (queue->poczatek + 1) % QUEUE_SIZE;
    queue->rozmiar--;
    return value;
}


void Queue__print(Kolejka* queue) {
    printf("Zawartość kolejki: ");
    for (int i = 0; i < queue->rozmiar; i++) {
        int index = (queue->poczatek + i) % QUEUE_SIZE;
        printf("%d ", queue->dane[index]);
    }
    printf("\n");
}



int get_digit(int liczba, int pozycja_cyfry) {
    return (liczba / (int)pow(10, pozycja_cyfry)) % 10;
}

void radix_sort(int arr[], int n) {
    int maksymalna_ilosc_cyfr = 3;
    int maksymalny_rozmiar = n;


    Kolejka queues[10];
    for (int i = 0; i < 10; i++) {
        Queue__init(&queues[i], maksymalny_rozmiar);
    }

    for (int pozycja_cyfry = 0; pozycja_cyfry < maksymalna_ilosc_cyfr; pozycja_cyfry++) {

        for (int i = 0; i < n; i++) {
            int cyfra = get_digit(arr[i], pozycja_cyfry);
            Queue__push(&queues[cyfra], arr[i]);
        }

        int index = 0;
        for (int i = 0; i < 10; i++) {
            while (queues[i].rozmiar > 0) {
                arr[index++] = Queue__pop(&queues[i]);
            }
        }
    }

}

bool czy_rownaja_sie_nawiasy(char otwarte, char zamkniete){
    return (otwarte == '(' && zamkniete == ')') ||
           (otwarte == '[' && zamkniete == ']') ||
           (otwarte == '{' && zamkniete == '}');
}
bool czy_to_jest_nawias(char nawias){
    return (nawias == '(') ||
            (nawias == ')') ||
            (nawias == '[') ||
            (nawias == ']') ||
            (nawias == '{') ||
            (nawias == '}');
}

bool czy_nawiase_parowane(const char* wyrazenie, int stack[], int* top, int size){
    for(int i = 0; i < strlen(wyrazenie); i++) {
        char nawias = wyrazenie[i];
        if (czy_to_jest_nawias(nawias)) {
        if (nawias == '(' || nawias == '[' || nawias == '{') {
            if (Stack_push(stack, top, nawias, size) == -1) {
                printf("stos jest przepelniony");
                return false;
            }
        } else if (nawias == ')' || nawias == ']' || nawias == '}') {
            int nawias_w_stosie = Stack_pop(stack, top);
            if (nawias_w_stosie == -2) {
                printf("stos jest pusty");
                return false;
            }
            if (!czy_rownaja_sie_nawiasy((char) nawias_w_stosie, nawias)) {
                printf("nawiasy sie nie rownaja");
                return false;
            }
        }
    }


    }
    printf("nawiasy sa rowne");
    printf("\n");
    return true;
}
int Stack_push(int stack[], int* top, int number, int max_size) {
    if (*top >= max_size - 1) {
        return -1;
    }
    stack[++(*top)] = number;
    return 0;
}

int Stack_pop(int stack[], int* top) {
    if (*top < 0) {
        return -2;
    }
    return stack[(*top)--];
}

void Stack_print(int stack[], int top) {
    printf("Stack:");
    for (int i = 0; i <= top; i++) {

        printf("%d ", stack[i]);
    }
    printf("\n");
}


void print_state(int step, int heap[], int sorted[], int heap_size, int sorted_size) {
    printf("Krok %d ", step);


    for (int i = 0; i < heap_size; i++) {
        printf("%2d ", heap[i]);
    }




    for (int i = 0; i < sorted_size; i++) {
        printf("   ");
    }

    for (int i = 0; i < sorted_size; i++) {
        printf("%2d ", sorted[i]);
    }

    printf("\n");
}


void max_heapify(int arr[], int i, int size) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        max_heapify(arr, largest, size);
    }
}

void build_max_heap(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        max_heapify(arr, i, size);
    }
}

void heapsort(int heap[], int sorted[], int size, bool track) {
    build_max_heap(heap, size);
    int sorted_size = 0;

    if (track) {
        print_state(1, heap, sorted, size, sorted_size);
    }

    for (int i = size - 1; i >= 0; i--) {
        int temp = heap[0];
        heap[0] = heap[i];
        heap[i] = temp;

        sorted[sorted_size++] = heap[i];
        heap[i] = -1;

        max_heapify(heap, 0, i);

        if (track) {
            print_state(size - i + 1, heap, sorted, i, sorted_size);
        }
    }
}



int main(int argc, char **argv) {


    bool track = false;
    int top = -1;
    while ((getopt(argc, argv, "")) != -1) {
        if (strcmp(argv[1], "--track") == 0) {
            track = true;
        }
    }

    Kolejka queue;
    Queue__init(&queue, 0);
    int stack[M];
    int heap[N];
    int sorted[N] = {0};

    srand(time(NULL));


    for (int i = 0; i < N; i++) {
        heap[i] = rand() % 20 - 10;
    }

    if (track) {
        print_state(0, heap, sorted, N, 0);
    }

    heapsort(heap, sorted, N, track);

    const char* wyrazenie = "{([])}";
    czy_nawiase_parowane(wyrazenie, stack, &top, M );


    int arr[] = {329, 457, 657, 839, 436, 720, 355};
    int n = sizeof(arr) / sizeof(arr[0]);

    radix_sort(arr, n);


    printf("Posortowana tablica: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");



    return 0;
}

