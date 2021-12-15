#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;
#define parent(x) (x-1)/2
#define MAX_SIZE 6000000    //�������� ���� ����
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))    //SWAP�Լ� ����
vector<int> original;    //�����Լ��� ���� �����͸� ������ ���� �迭
int list[MAX_SIZE];    //�� ���� �˰��򿡼� ����� ������ �迭
int sorted[MAX_SIZE]; //�պ����Ŀ��� ����� �����͸� ������ �迭
clock_t start, finish, used_time = 0;    //���� �ð� ������ ���� ����

//�պ�����
void merge(int list[], int left, int mid, int right)
{
    int i, j, k, l;
    i = left, j = mid + 1; k = left;

    while (i <= mid && j <= right)
    {
        if (list[i] <= list[j])
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }

    if (i > mid)
        for (l = j; l <= right; l++)
            sorted[k++] = list[l];
    else
        for (l = i; l <= right; l++)
            sorted[k++] = list[l];

    for (l = left; l <= right; l++)
        list[l] = sorted[l];
}
void merge_sort(int list[], int left, int right)
{
    int mid;
    if (left < right)
    {
        mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

//������
int partition(int list[], int left, int right)
{
    int pivot = list[left], tmp, low = left, high = right + 1;

    do {
        do
            low++;
        while (low <= right && list[low] < pivot);

        do
            high--;
        while (high >= left && list[high] > pivot);
        if (low < high) SWAP(list[low], list[high], tmp);
    } while (low < high);

    SWAP(list[left], list[high], tmp);
    return high;
}
void quick_sort(int list[], int left, int right)
{
    if (left < right)
    {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}

//���� ����
void bubble_sort(int list[], int n)
{
    int i, j, tmp;
    cout << "bubble_sort start" << endl;
    for (i = n - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
            if (list[j] > list[j + 1])
                SWAP(list[j], list[j + 1], tmp);
    }
}

//���� ����
void selection_sort(int list[], int n)
{
    int i, j, least, tmp;
    cout << "selection_sort start" << endl;
    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[least]) least = j;
        SWAP(list[i], list[least], tmp);
    }
}

//���� ����
void insertion_sort(int list[], int n)
{
    int i, j, key;
    cout << "insertion_sort start" << endl;
    for (i = 1; i < n; i++)
    {
        key = list[i];
        for (j = i - 1; j >= 0 && list[j] > key; j--)
            list[j + 1] = list[j];
        list[j + 1] = key;
    }
}

void swap(int* val1, int* val2) { // ���� �Լ�
    int tmp = *val1;
    *val1 = *val2;
    *val2 = tmp;
}

void heapify(int list[], int n, int parent) {
    int largest = parent; //�θ� ���
    int l = 2 * parent + 1; //���� �ڽ�
    int r = 2 * parent + 2; //������ �ڽ�


    if (l < n && list[l] > list[largest]) {
        largest = l;
    }
    if (r < n && list[r] > list[largest]) {
        largest = r;
    }


    if (largest != parent) {

        swap(&list[parent], &list[largest]);

        heapify(list, n, largest);
    }
}

void heap_sort(int list[], int n) {

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(list, n, i);
    }
   
    for (int i = n - 1; i >= 0; i--) {

        swap(list[0], list[i]);
      
        heapify(list, i, 0);
    }
}

void shell_sort(int list[], int n) {
    int i, j, temp;
    int gap = n / 2;
    while (gap > 0) {
        for (i = gap; i < n; i++) {
            temp = list[i];
            j = i;
            while (j >= gap && list[j - gap] > temp) {
                list[j] = list[j - gap];
                j -= gap;
            }
            list[j] = temp;
        }
        gap /= 2;
    }
}

//���� �迭�� �����ϴ� �Լ�
void CopyArr()
{
    int i;
    for (i = 0; i < original.size(); i++)
        list[i] = original[i];
}

//���� �ð��� ���� �� ����ϴ� �Լ�
void CalcTime()
{
    used_time = finish - start;
    cout << "���� �Ϸ� �ҿ�ð� : " << (float)used_time / CLOCKS_PER_SEC << "sec\n\n";
}


void main()
{
    string str_buf;
    fstream fs;

    fs.open("data.csv", ios::in);

    while (!fs.eof()) {

        getline(fs, str_buf, '\n');
        original.push_back(atoi(str_buf.c_str()));
    }
    fs.close();

    CopyArr();
    start = clock();
    selection_sort(list, original.size());
    finish = clock();
    CalcTime();

    CopyArr();
    start = clock();
    insertion_sort(list, original.size());
    finish = clock();
    CalcTime();

    CopyArr();
    start = clock();
    bubble_sort(list, original.size());
    finish = clock();
    CalcTime();

    CopyArr();
    start = clock();
    cout << "merge_sort start" << endl;
    merge_sort(list, 0, original.size());
    finish = clock();
    CalcTime();

    CopyArr();
    start = clock();
    cout << "quick_sort start" << endl;
    quick_sort(list, 0, original.size());
    finish = clock();
    CalcTime();


    CopyArr();
    start = clock();
    cout << "heap_sort start" << endl;
    heap_sort(list, original.size());
    finish = clock();
    CalcTime();


    CopyArr();
    start = clock();
    cout << "shell_sort start" << endl;
    shell_sort(list, original.size());
    finish = clock();
    CalcTime();
    
}