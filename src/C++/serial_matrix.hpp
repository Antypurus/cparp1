#include "matrix.hpp"
#include <cstdlib>
#include <algorithm>
#include <iterator>
//#include <Windows.h>

template<typename T>
class serial_matrix final: public matrix<T>
{
private:
    T* m_matrix; //array containing the actual matrix data
	unsigned char algorithm = 1; // 1 -> Regular Version Bad For Cache, 2 -> Iterative Line Based ALgorithm Good For Cache, 3 -> Block Algorithm Even Better For Cache 
public:
    //interaface methods
    std::unique_ptr<matrix<T>> operator*(const matrix<T>* matrix)const override;
    T& get_val(const size_t i,const size_t j) override;
	const T& get(const size_t i, const size_t j)const override;

	//non polimorfic operator
	std::unique_ptr<serial_matrix<T>> operator*(const serial_matrix<T>& matrix)const;

    //class methods
    serial_matrix(const size_t width,const size_t height,const unsigned char algorithm);
	serial_matrix(const size_t width, const size_t height, const T matrix_data[], const unsigned char algorithm);
	serial_matrix(const size_t width, const size_t height, T*&& matrix_data, const unsigned char algorithm);//move constructor for dynamic array
    ~serial_matrix() override;
};

template<typename T>
serial_matrix<T>::serial_matrix(const size_t width,const size_t height, const unsigned char algorithm):matrix<T>(width,height),algorithm(algorithm)
{
	this->m_matrix = (T*)malloc(width * height * sizeof(T));
	std::fill(this->m_matrix, this->m_matrix + (width*height), T());
}

template<typename T>
serial_matrix<T>::serial_matrix(const size_t width, const size_t height, const T matrix_data[], const unsigned char algorithm):matrix<T>(width, height), algorithm(algorithm)
{
	this->m_matrix = (T*)malloc(width * height * sizeof(T));
	std::copy(matrix_data, matrix_data+(width*height),this->m_matrix);
}

template<typename T>
inline serial_matrix<T>::serial_matrix(const size_t width, const size_t height, T*&& matrix_data, const unsigned char algorithm):matrix<T>(width, height), algorithm(algorithm)
{
	this->m_matrix = matrix_data;
}

template<typename T>
serial_matrix<T>::~serial_matrix()
{
	free(this->m_matrix);
}

template<typename T>
inline std::unique_ptr<matrix<T>> serial_matrix<T>::operator*(const matrix<T>* matrix)const
{
	T* res = (T*)malloc(matrix->get_width() * this->m_height * sizeof(T));
	std::fill(res, res + (matrix->get_width() * this->m_height), T());

	{

		size_t mA_height = this->m_height;
		size_t mB_height = matrix->get_height();
		size_t mB_width = matrix->get_width();

		if (this->algorithm == 1)
		{
			for (size_t matrix_A_line = 0; matrix_A_line < mA_height; ++matrix_A_line)
			{
				for (size_t matrix_B_col = 0; matrix_B_col < mB_width; ++matrix_B_col)
				{
					for (size_t matrix_B_line = 0; matrix_B_line < mB_height; ++matrix_B_line)
					{
						res[matrix_A_line * this->get_height() + matrix_B_col] += this->get(matrix_A_line, matrix_B_line) * matrix->get(matrix_B_line, matrix_B_col);
					}
				}
			}
		}
		else if (this->algorithm == 2)
		{
			for (size_t matrix_A_line = 0; matrix_A_line < mA_height; ++matrix_A_line)
			{
				for (size_t matrix_B_line = 0; matrix_B_line < mB_height; ++matrix_B_line)
				{
					for (size_t matrix_B_col = 0; matrix_B_col < mB_width; ++matrix_B_col)
					{
						res[matrix_A_line * this->get_height() + matrix_B_col] += this->get(matrix_A_line, matrix_B_line) * matrix->get(matrix_B_line, matrix_B_col);
					}
				}
			}
		}
		else if (this->algorithm == 3)
		{
			//blocl algorithm
		}
	}

	return std::make_unique<serial_matrix<T>>(matrix->get_width(),this->m_height,std::move(res), algorithm);
}

template<typename T>
inline T& serial_matrix<T>::get_val(const size_t line,const size_t column)
{
	return this->m_matrix[line * this->m_width + column];
}

template<typename T>
inline const T& serial_matrix<T>::get(const size_t line, const size_t column)const
{
	return this->m_matrix[line * this->m_width + column];
}

template<typename T>
inline std::unique_ptr<serial_matrix<T>> serial_matrix<T>::operator*(const serial_matrix<T>& matrix) const
{
	T* res = (T*)malloc(matrix.get_width() * this->m_height * sizeof(T));
	std::fill(res, res + (matrix.get_width() * this->m_height), T());

	//matrix calculation block
	{

		size_t mA_height = this->m_height;
		size_t mB_height = matrix.get_height();
		size_t mB_width = matrix.get_width();

		if (this->algorithm == 1)
		{
			for (size_t matrix_A_line = 0; matrix_A_line < mA_height; ++matrix_A_line)
			{
				for (size_t matrix_B_col = 0; matrix_B_col < mB_width; ++matrix_B_col)
				{
					for (size_t matrix_B_line = 0; matrix_B_line < mB_height; ++matrix_B_line)
					{
						res[matrix_A_line * this->get_height() + matrix_B_col] += this->get(matrix_A_line, matrix_B_line) * matrix.get(matrix_B_line, matrix_B_col);
					}
				}
			}
		}
		else if (this->algorithm == 2)
		{
			for (size_t matrix_A_line = 0; matrix_A_line < mA_height; ++matrix_A_line)
			{
				for (size_t matrix_B_line = 0; matrix_B_line < mB_height; ++matrix_B_line)
				{
					for (size_t matrix_B_col = 0; matrix_B_col < mB_width; ++matrix_B_col)
					{
						res[matrix_A_line * this->get_height() + matrix_B_col] += this->get(matrix_A_line, matrix_B_line) * matrix.get(matrix_B_line, matrix_B_col);
					}
				}
			}
		}
		else if (this->algorithm == 3)
		{
			//blocl algorithm
		}
	}

	return std::make_unique<serial_matrix<T>>(matrix.get_width(), this->m_height, std::move(res),this->algorithm);
}
