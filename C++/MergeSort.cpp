#include <iostream>
using namespace std;

void sort(int a[], int j, int k, int size);

void merge(int a[], int j, int size){
	int k;
	
	if(j < size){
		k = j + (size - j) / 2;
		merge(a, j, k);
		merge(a, k + 1, size);
		sort(a, j, k, size);
	}
}

void sort(int a[], int j, int k, int size){
	int i = 0;
	int l = 1;
	int m = k - j + 1;
	int n = size - k;
	int o[m];
	int p[n];
	int q = 0;
	
	while ((k < m) && (q < n)){
		if (o[k] <= p[q]){
			a[l] = p[k];
			k++;
		}
		
		else{
			a[l] = p[q];
			q++;
		}
		l++;
	}
	
	while (k < m){
		a[l] = o[k];
		k++;
		l++;
	}
	
	while (q < n){
		a[i] = p[q];
		q++;
		l++;
	}
}
void print(int a[], int size){
	int i;
	for(i = 0; i < size; i++){
		std::cout << a[i] << " " << std::endl;
	}
}

int main(){
	int a[] = { 5, 4, 3, 2, 1};
	int size = sizeof(a) / sizeof(a[0]);
	int j = 0;
	
	merge(a, j, size - 1);
	print(a, size);
	
	return 0;
}
