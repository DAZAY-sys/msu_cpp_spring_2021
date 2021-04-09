#include "matrix.hpp"

Matrix::Proxy::Proxy(size_t b = 0)
{
    if (b != 0)
    {
        try {
            data = new int32_t[b];
            col_num = b;
            for (size_t i = 0; i < b; i++)
                data[i] = 0;
        }
        catch (std::bad_alloc) {
            std::cout<<"BAD_ALLOC IN PROXY";
        }
    }

}

void Matrix::Proxy::operator = (Proxy p)
{
    this->col_num = p.col_num;
    this->data = new int32_t[p.col_num];
    for (size_t j = 0; j < p.col_num; j++)
    {
        this->data[j] = p.data[j];
    }
}

Matrix::Matrix(size_t a = 0, size_t b = 0)
{
    this->row_number = a;
    this->column_number = b;

    try {
        rows = new Proxy[a];

        for (size_t k = 0; k < a; k++)
            rows[k] = Proxy(b);
    }
    catch (std::bad_alloc) {
        std::cout<<"BAD_ALLOC IN MATRIX<<std::endl";
    }
}

Matrix::~Matrix()
{
    delete[] this->rows;
    this->rows = 0;
}

Matrix::Proxy::~Proxy()
{
    delete[] this->data;
    this->data = 0;
}

size_t Matrix::getRows()
{
    return this->row_number;
}
size_t Matrix::getColumns()
{
    return this->column_number;
}

Matrix::Proxy& Matrix::operator[](size_t i)
{
    if (i > row_number)
        throw std::out_of_range("");
    return rows[i - 1];
}

int32_t& Matrix::Proxy::operator[](size_t j)
{
    if (j > col_num)
        throw std::out_of_range("");
    return data[j - 1];
}

void Matrix::operator *=(uint32_t n)
{
    for (size_t i = 0; i < this->row_number; i++)
        for (size_t j = 1; j <= this->column_number; j++)
            (this->rows)[i][j] *= n;
}

Matrix operator + (Matrix &m1, Matrix &m2)
{
    if (m1.row_number != m2.row_number or m1.column_number != m2.column_number)
        throw std::out_of_range("");

    Matrix result(m1.row_number, m1.column_number);
    for (size_t i = 1; i <= m1.row_number; i++)
        for (size_t j = 1; j <= m1.column_number; j++)
            result[i][j] = m1[i][j] + m2[i][j];
    return result;
}

bool operator == (Matrix &m1, Matrix &m2)
{
    if (m1.row_number != m2.row_number or m1.column_number != m2.column_number)
        throw std::out_of_range("");

    for (size_t i = 1; i <= m1.row_number; i++)
        for (size_t j = 1; j <= m1.column_number; j++)
            if (m1[i][j] != m2[i][j])
                return false;
    return true;
}

bool operator != (Matrix &m1, Matrix &m2)
{
    if (m1.row_number != m2.row_number or m1.column_number != m2.column_number)
        throw std::out_of_range("");

    for (size_t i = 1; i <= m1.row_number; i++)
        for (size_t j = 1; j <= m1.column_number; j++)
            if (m1[i][j] != m2[i][j])
                return true;
    return false;
}

std::ostream& operator << (std::ostream &out, Matrix &m)
{
    out << "Matrix" << std::endl;
    for (size_t i = 1; i <= m.row_number; i++){
        out << " | ";
        for (size_t j = 1; j <= m.column_number; j++)
        {
            out << m[i][j] << ' ';
        }
        out << "| " << std::endl;
    }
    return out;
}


