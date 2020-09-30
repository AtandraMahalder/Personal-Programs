//Atandra Mahalder
//Personal Assignment
//07/19/2020
//Basic program to map your distance from a set of given points

#include<stdio.h>
#include<stdlib.h>

int x_0, y_0;

typedef struct{
 int x, y;
}pt;

int compareTo(pt *p1, pt *p2);
void insert_sort(pt *arr, int start, int end);
void merge_sort(pt *arr, int start, int end, int t);
void sort(pt *arr, int length, int t);
int search(pt *arr, int len, pt *p);

int main(){
 int n, s, t; scanf("%d%d%d%d%d", &x_0, &y_0, &n, &s, &t);
 pt *arr = calloc(n, sizeof(pt));
 for(int i = 0; i<n ; ++i){
    scanf("%d%d", &arr[i].x, &arr[i].y);
 }
 pt *query = calloc(s, sizeof(pt));
 for(int i = 0; i<s; ++i){
    scanf("%d%d", &query[i].x, &query[i].y);
 }

 sort(arr, n, t);
 for(int i = 0; i<n ; ++i){
    printf("%d %d\n", arr[i].x, arr[i].y);
 }
 int rank;
 for(int i = 0; i<s; ++i){
    rank = search(arr, n, query + i);
    if(rank) printf("%d %d found at rank %d\n", query[i].x, query[i].y, rank);
    else printf("%d %d not found\n", query[i].x, query[i].y);
 }

 free(arr);
 free(query);

 return 0;
}

int compareTo(pt *p1, pt *p2){
 int p1_factor = (p1->x - x_0)*(p1->x - x_0) + (p1->y - y_0)*(p1->y - y_0);
 int p2_factor = (p2->x - x_0)*(p2->x - x_0) + (p2->y - y_0)*(p2->y - y_0);
 if(p1_factor < p2_factor) return -1;
 if(p1_factor > p2_factor) return 1;
 if(p1->x==p2->x && p1->y==p2->y) return 0;
 if(p1->x < p2->x) return -1;
 if(p1->x > p2->x) return 1;
 if(p1->y < p2->y) return -1;
 return 1;
}

void insert_sort(pt *arr, int start, int end){
 for(int i = start+1; i<=end; ++i){
    int j = i;
    while(j>start && compareTo(arr + j, arr + j-1)<0){
        pt m = arr[j];
        arr[j] = arr[j-1];
        arr[j-1] = m;
        --j;
    }
 }
}

void merge_sort(pt *arr, int start, int end, int t){
 if(end - start < t){
    insert_sort(arr, start, end);
    return;
 }

 int mid = start + (end - start)/2;
 merge_sort(arr, start, mid, t);
 merge_sort(arr, mid + 1, end, t);
 pt *aux = calloc(end - start + 1, sizeof(pt));
 int i = start;
 int j = mid + 1;
 for(int k = 0; k<=end-start; ++k){
    if(i==mid+1) aux[k] = arr[j++];
    else if(j==end+1) aux[k] = arr[i++];
    else if(compareTo(arr + i, arr + j)>0) aux[k] = arr[j++];
    else aux[k] = arr[i++];
 }
 for(int k = start; k<=end; ++k) arr[k] = aux[k-start];
 free(aux);
}

void sort(pt *arr, int length, int t){
 merge_sort(arr, 0, length-1, t);
}

int search(pt *arr, int len, pt *p){
 int i = 0, j = len-1;
 while(i<j){
    int mid = i + (j-i)/2;
    if(!compareTo(arr + mid, p)) return mid+1;
    else if(compareTo(arr + mid, p)>0) j = mid - 1;
    else i = mid + 1;
 }
 if(!compareTo(arr + i, p)) return i+1;
 return 0;
}
