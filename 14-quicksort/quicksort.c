#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int comparisonCount = 0;  // 비교 횟수
int moveCount = 0;        // 이동 횟수
int rounds = 0;           // 재귀 호출 라운드
int isFirst = 0;          // 첫 번째 실행 여부 확인

// 랜덤 숫자뽑기
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0~999 사이의 난수
    }
}

// 배열 출력 (40~60 위치 값)
void printArray(int array[], int n) {
    if (rounds % 10 == 0 && isFirst == 0) { // 10번에 한 번만 출력

        for (int i = 40; i < 60; i++) {
            printf("%d ", array[i]);
        }
        printf("\n\n");
    }
    rounds++;
}

// 파티션 수행
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];
    moveCount++;  // 피벗 이동

    do {
        do {
            low++;
            comparisonCount++;  // 비교
        } while (low <= right && list[low] < pivot);

        do {
            high--;
            comparisonCount++;  // 비교
        } while (high >= left && list[high] > pivot);

        if (low < high) {
            SWAP(list[low], list[high], temp);
            moveCount += 2;  // 이동 
        }
    } while (low < high);

    SWAP(list[left], list[high], temp);  //위치 변경
    moveCount += 2;  // 이동 

    return high;
}

// 퀵 정렬 수행
void doQuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);

        // 배열 출력
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
        comparisonCount = 0;  // 비교 횟수 초기화
        moveCount = 0;        // 이동 횟수 초기화
        rounds = 0;           // 라운드 초기화

        if (i == 0) {
            printf("Quick Sort Run\n");
            isFirst = 0;  // 첫 번째 실행으로 설정
            doQuickSort(array, 0, SIZE - 1);

            // 결과 출력
            printf("\nResult: ");
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", array[j]);
            }
            printf("\n");
            isFirst = 1;  // 출력 방지하기 위함
        }
        else {
            doQuickSort(array, 0, SIZE - 1);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    // 평균 비교 횟수, 이동 횟수 
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
