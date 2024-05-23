#include<HashTable.h>
int main() {
	vector<int> arr = { 1, 2, 3, 1, 2, 1, 4, 5, 6, 5 };
	HashTable<int, int> duplicates = countDuplicates(arr);

	duplicates.print();

	return 0;
}