#include <stddef.h>
#include <memory>

template<typename T>
class matrix
{
protected:
    size_t m_width;
    size_t m_height;
public:
    //interface methods
    matrix(const size_t width,const size_t height):m_width(width),m_height(height){};
    virtual std::unique_ptr<matrix<T>> operator*(const matrix<T>* matrix)const = 0;
    virtual T& get_val(const size_t i,const size_t j) = 0;
	virtual const T& get(const size_t i, const size_t j)const = 0;
	virtual ~matrix() {};

    //always the same methods
    const size_t get_width()const {return this->m_width;}
    const size_t get_height()const {return this->m_height;}
};