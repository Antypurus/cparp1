#include "serial_matrix.hpp"
#include <stdio.h>
#include <cstdlib>

int main(int argc,char** argv)
{
	int matrix_size = atoi(argv[1]);
	serial_matrix<float>m(matrix_size, matrix_size);
	serial_matrix<float>n(matrix_size, matrix_size);
	auto b = (m * n);
	int val = b->get_val(1, 1);
	printf("%d\n", val);
}