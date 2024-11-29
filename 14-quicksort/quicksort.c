#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int comparisonCount = 0;  // �� Ƚ��
int moveCount = 0;        // �̵� Ƚ��
int rounds = 0;           // ��� ȣ�� ����
int isFirst = 0;          // ù ��° ���� ���� Ȯ��

// ���� ���ڻ̱�
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0~999 ������ ����
    }
}

// �迭 ��� (40~60 ��ġ ��)
void printArray(int array[], int n) {
    if (rounds % 10 == 0 && isFirst == 0) { // 10���� �� ���� ���

        for (int i = 40; i < 60; i++) {
            printf("%d ", array[i]);
        }
        printf("\n\n");
    }
    rounds++;
}

// ��Ƽ�� ����
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];
    moveCount++;  // �ǹ� �̵�

    do {
        do {
            low++;
            comparisonCount++;  // ��
        } while (low <= right && list[low] < pivot);

        do {
            high--;
            comparisonCount++;  // ��
        } while (high >= left && list[high] > pivot);

        if (low < high) {
            SWAP(list[low], list[high], temp);
            moveCount += 2;  // �̵� 
        }
    } while (low < high);

    SWAP(list[left], list[high], temp);  //��ġ ����
    moveCount += 2;  // �̵� 

    return high;
}

// �� ���� ����
void doQuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);

        // �迭 ���
        printArray(list, SIZE);

        doQuickSort(list, left, q - 1);
        doQuickSort(list, q + 1, right);
    }
}

int main() {
    int array[SIZE];
    int totalComparisons = 0, totalMoves = 0;

    srand(time(NULL));

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;  // �� Ƚ�� �ʱ�ȭ
        moveCount = 0;        // �̵� Ƚ�� �ʱ�ȭ
        rounds = 0;           // ���� �ʱ�ȭ

        if (i == 0) {
            printf("Quick Sort Run\n");
            isFirst = 0;  // ù ��° �������� ����
            doQuickSort(array, 0, SIZE - 1);

            // ��� ���
            printf("\nResult: ");
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", array[j]);
            }
            printf("\n");
            isFirst = 1;  // ��� �����ϱ� ����
        }
        else {
            doQuickSort(array, 0, SIZE - 1);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    // ��� �� Ƚ��, �̵� Ƚ�� 
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
