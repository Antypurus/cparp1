#include "serial_matrix.hpp"
#include <stdio.h>
#include <cstdlib>

int main(int argc,char** argv)
{
	unsigned int matrix_size = atoi(argv[1]);
	unsigned char algorithm = atoi(argv[2]);
	serial_matrix<float>m(matrix_size, matrix_size, algorithm);
	serial_matrix<float>n(matrix_size, matrix_size, algorithm);
	auto b = (m * n);
	int val = b->get_val(1, 1);
	printf("%d\n", val);
}