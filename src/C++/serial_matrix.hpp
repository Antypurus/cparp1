#include "matrix.hpp"
#include <cstdlib>
#include <algorithm>

template<typename T>
class serial_matrix: protected matrix<T>
{
private:
    T* m_matrix; //array containing the actual matrix data
public:
    //interaface methods
    matrix<T>* operator*(const matrix<T>& matrix) override;
    T& get_val(const size_t i,const size_t j) override;

    //class methods
    serial_matrix(const size_t width,const size_t height);
	serial_matrix(const size_t width, const size_t height, const T* matrix_data);
    ~serial_matrix() override;
};

template<typename T>
serial_matrix<T>::serial_matrix(const size_t width,const size_t height):matrix<T>(width,height){
    this->m_matrix = (T*)malloc(width*height);
}

template<typename T>
serial_matrix<T>::serial_matrix(const size_t width, const size_t height, const T* matrix_data){
	this->m_matrix = (T*)malloc(width*height);
	std::copy(&matrix_data[0], &matrix_data[width*height - 1], &this->m_matrix[0]);
}

template<typename T>
serial_matrix<T>::~serial_matrix()
{
    free(this->m_matrix);
}

template<typename T>
inline matrix<T>* serial_matrix<T>::operator*(const matrix<T>& matrix)
{
	return NULL;
}

template<typename T>
inline T& serial_matrix<T>::get_val(const size_t i,const size_t j)
{
    return this->m_matrix[i*this->m_width + j];
}