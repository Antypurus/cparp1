#include "serial_matrix.hpp"
#include <stdio.h>

int main()
{
	int a[]{ 1,2,3,4 };
	serial_matrix<float>m(2000, 2000);
	serial_matrix<float>n(2000, 2000);
	auto b = ((m) * (n));
	int val = b->get_val(1, 1);
	printf("%d\n", val);
}