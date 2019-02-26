#include "serial_matrix.hpp"
#include <stdio.h>

int main()
{
	int a[]{ 1,2,3,4 };
	serial_matrix<int> m(2, 2, a);
	int val = m.get_val(1, 1);
	printf("%d\n", val);
}