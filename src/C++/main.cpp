#include "serial_matrix.hpp"
#include "papi_interface.hpp"
#include <stdio.h>
#include <cstdlib>

int main(int argc,char** argv)
{
	int events = papi::start_using();
	unsigned int matrix_size = atoi(argv[1]);
	unsigned char algorithm = atoi(argv[2]);
	serial_matrix<float>m(matrix_size, matrix_size, algorithm);
	serial_matrix<float>n(matrix_size, matrix_size, algorithm);
	papi::start_measure(events);
	auto b = (m * n);
	papi::stop_measure(events);
	int val = b->get_val(1, 1);
	printf("%d\n", val);
	papi::stop_using(events);
}