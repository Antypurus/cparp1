#include "serial_matrix.hpp"
#include <stdio.h>

int main()
{
	int a[]{ 1,2,3,4 };
	matrix<int>* m = new serial_matrix<int>(2000, 2000);
	matrix<int>* n = new serial_matrix<int>(2000, 2000);
	auto b = ((*m) * (*n));
	int val = b->get_val(1, 1);
	printf("%d\n", val);
}