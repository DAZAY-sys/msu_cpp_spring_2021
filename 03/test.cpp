#include <cassert>
#include "matrix.hpp"

void DefaultTest()
{
    Matrix m(2, 7);
    std::cout << m;
    assert(m.getRows() == 2);
    assert(m.getColumns() == 7);
}

void OperationTest()
{
    Matrix m1(1, 2);
    Matrix m2(1, 2);
    m1[1][1] = 10;
    m1[1][2] = 2;

    m2[1][1] = 7;
    m2[1][2] = 5;

    Matrix sum = m1 + m2;
    m1 *= 2;

    std::cout << sum << m1;

    assert(sum[1][1] == 17);
    assert(sum[1][2] == 7);
    assert(m1[1][1] == 20);
    assert(m1[1][2] == 4);
}

void BigOperationTest()
{
    Matrix m1(3, 2);
    Matrix m2(3, 2);

    m1[1][1] = 1;
    m1[1][2] = 2;
    m1[2][1] = 3;
    m1[2][2] = 4;
    m1[3][1] = 5;
    m1[3][2] = 6;

    m2[1][1] = 10;
    m2[1][2] = 20;
    m2[2][1] = 30;
    m2[2][2] = 40;
    m2[3][1] = 50;
    m2[3][2] = 60;

    m1 *= 2;
    Matrix sum = m1 + m2;

    std::cout << sum;

    assert(m1[1][1] == 2 && m1[1][2] == 4);
    assert(m1[2][1] == 6 && m1[2][2] == 8);
    assert(m1[3][1] == 10 && m1[3][2] == 12);

    assert(sum[1][1] == 12 && sum[1][2] == 24);
    assert(sum[2][1] == 36 && sum[2][2] == 48);
    assert(sum[3][1] == 60 && sum[3][2] == 72);
}

void WrongOperationDimensionTest()
{
    Matrix m1(2, 4), m2(1, 3);
    try{
        Matrix sum = m1 + m2;
    }
    catch(std::out_of_range){
        std::cout << "OUT OF RANGE THROW" << std::endl;
    }

    try{
        bool check = (m1 == m2);
    }
    catch(std::out_of_range){
        std::cout << "OUT OF RANGE THROW" << std::endl;
    }
}

void BoolTest()
{
    Matrix m1 (3, 1), m2(3, 1);

    assert((m1 == m2) == true);
    m2[2][1] = 3;
    std::cout << m1 << m2;
    assert((m1 != m2) == true);
}

void ColumnOutOfRange()
{
    Matrix m1(2,7);
    try{
        std::cout << m1[1][10];
    }
    catch(std::out_of_range){
        std::cout<<"COLUMN OUT OF RANGE THROW"<<std::endl;
    }
}

void RowOutOfRange()
{
    Matrix m1(2,7);
    try{
        std::cout << m1[10][1];
    }
    catch(std::out_of_range){
        std::cout<<"ROW OF RANGE THROW"<<std::endl;
    }
}

int main()
{
    std::cout << "Test DefaultTest:"<<std::endl;
    DefaultTest();
    std::cout <<std::endl;

    std::cout << "Test OperationTest:"<<std::endl;
    OperationTest();
    std::cout <<std::endl;

    std::cout << "Test BigOperationTest:"<<std::endl;
    BigOperationTest();
    std::cout <<std::endl;

    std::cout << "Test WrongOperationDimensionTest:"<<std::endl;
    WrongOperationDimensionTest();
    std::cout <<std::endl;

    std::cout << "Test BoolTest:"<<std::endl;
    BoolTest();
    std::cout <<std::endl;

    std::cout << "ColumnOutOfRange:"<<std::endl;
    ColumnOutOfRange();
    std::cout <<std::endl;

    std::cout << "RowOutOfRange:"<<std::endl;
    RowOutOfRange();
    std::cout <<std::endl;

    std::cout << "SUCCESS\n";
    return 0;
}
