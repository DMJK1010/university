/*
 * Sort_Program:main.c
 *
 *  Created on: 2024. 5.22.(01:14) - 합병정렬, 기수정렬 구현 필요
 *      Author: Junha Kim
 *
 *	선택 / 삽입 / 버블 / 쉘 / 합병 / 퀵 / 기수 정렬 프로그램
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<time.h>
#include<windows.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_ARR_SIZE 11
#define MAX_QUEUE_SIZE 100

typedef int element;

typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int sorted[MAX_ARR_SIZE];

////////////////////// selection_sort //////////////////////
void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[least]) least = j;
		SWAP(list[i], list[least], temp);
	}
}
////////////////////// selection_sort 끝 //////////////////////


////////////////////// insertion_sort //////////////////////
void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j]; 		// 레코드의 오른쪽 이동
		list[j + 1] = key;
	}
}
////////////////////// insertion_sort 끝 //////////////////////


////////////////////// bubble_sort //////////////////////
void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) 	// 앞뒤의 레코드를 비교한 후 교체
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}
////////////////////// bubble_sort 끝 //////////////////////


////////////////////// shell_sort //////////////////////
inc_insertion_sort(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}

void shell_sort(int list[], int n)   // n = size
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)		// 부분 리스트의 개수는 gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}
////////////////////// shell_sort 끝 //////////////////////


////////////////////// merge_sort //////////////////////
void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	// 분할 정렬된 list의 합병
	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}
	if (i > mid) 	// 남아 있는 레코드의 일괄 복사
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else 	// 남아 있는 레코드의 일괄 복사
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	// 배열 sorted[]의 리스트를 배열 list[]로 복사
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;              // 리스트의 균등분할
		merge_sort(list, left, mid);     // 부분리스트 정렬
		merge_sort(list, mid + 1, right);//부분리스트 정렬
		merge(list, left, mid, right);    // 합병
	}
}

////////////////////// shell_sort 끝 //////////////////////


////////////////////// quick_sort //////////////////////
int partition(int list[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (low <= right && list[low] < pivot);
		do
			high--;
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);

	SWAP(list[left], list[high], temp);
	return high;
}

void quick_sort(int list[], int left, int right)
{
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}
////////////////////// quick_sort 끝 //////////////////////


////////////////////// radix_sort //////////////////////
#define BUCKETS 10
#define DIGITS 4
void radix_sort(int list[], int n)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) init_queue(&queues[b]);	// 큐들의 초기화

	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++)				// 데이터들을 자리수에 따라 큐에 입력
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		for (b = i = 0; b < BUCKETS; b++)			// 버켓에서 꺼내어 list로 합친다.
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;				// 그 다음 자리수로 간다.
	}
}

////////////////////// radix_sort 끝 //////////////////////

void random_arr(int* arr) {
	srand(time(NULL));
	for (int i = 0; i < MAX_ARR_SIZE; i++) {
		arr[i] = rand() % 100;
	}
	printf("배열을 섞었습니다.\n");
}

void print_arr(int* arr) {
	printf("정렬 결과 = ");
	for (int i = 0; i < MAX_ARR_SIZE; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int Main_menu(int* arr) {
	int sel;

	char* menu[] = {
		"\n====================Main menu====================\n",
		"=  0. 종료        1. 선택 정렬   2. 삽입 정렬   =\n",
		"=  3. 버블 정렬   4. 쉘 정렬     5. 합병 정렬   =\n",
		"=  6. 퀵 정렬     7. 기수 정렬   8. 배열 초기화 =\n",
		"=  9. 화면 초기화                               =\n",
		"=================================================\n"
	};
	for (int i = 0; i < 6; i++) {
		printf("%s", menu[i]);
	}
	printf("array     = ");

	for (int i = 0; i < MAX_ARR_SIZE; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	printf("입력: ");
	scanf("%d", &sel);
	return sel;
}

void Main_run() {
	int num;
	int* arr = (int*)malloc(sizeof(int) * MAX_ARR_SIZE);
	random_arr(arr);
	while ((num = Main_menu(arr))) {
		switch (num) {
		case 1:
			selection_sort(arr, MAX_ARR_SIZE);
			print_arr(arr);
			break;
		case 2:
			insertion_sort(arr, MAX_ARR_SIZE);
			print_arr(arr);
			break;
		case 3:
			bubble_sort(arr, MAX_ARR_SIZE);
			print_arr(arr);
			break;
		case 4:
			shell_sort(arr, MAX_ARR_SIZE);
			print_arr(arr);
			break;
		case 5:
			merge_sort(arr, 0, MAX_ARR_SIZE);
			print_arr(arr);
			break;
		case 6:
			quick_sort(arr, 0, MAX_ARR_SIZE - 1);
			print_arr(arr);
			break;
		case 7:
			radix_sort(arr, MAX_ARR_SIZE);
			print_arr(arr);
			break;
		case 8:
			random_arr(arr);
			break;
		case 9:
			system("cls");
			break;
		default:
			printf("잘못된 입력입니다.\n");
			break;
		}
	}
	free(arr);
}

int main() {

	Main_run();

	return 0;
}
