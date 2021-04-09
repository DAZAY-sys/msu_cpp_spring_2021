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
    Matrix m1(1,2), m2(1,2);
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

void WrongDimensionsTest()
{
    Matrix m1(1,2), m2(1,2);
    try{
        std::cout << m1[2][2];
    }
    catch(std::out_of_range){
        std::cout<<"OUT OF RANGE THROW"<<std::endl;
    }

    try{
        std::cout << m1[1][3];
    }
    catch(std::out_of_range){
        std::cout<<"OUT OF RANGE THROW"<<std::endl;
    }
}

void WrongOperationDimensionTest()
{
    Matrix m1(2,4), m2(1,3);
    try{
        Matrix sum = m1 + m2;
    }
    catch(std::out_of_range){
        std::cout<<"OUT OF RANGE THROW"<<std::endl;
    }

    try{
        bool check = (m1 == m2);
    }
    catch(std::out_of_range){
        std::cout<<"OUT OF RANGE THROW"<<std::endl;
    }
}

void BoolTest()
{
    Matrix m1 (3,1), m2(3,1);

    assert((m1 == m2) == true);
    m2[2][1] = 3;
    std::cout << m1 << m2;
    assert((m1 != m2) == true);
}

int main()
{
    std::cout << "Test DefaultTest:"<<std::endl;
    DefaultTest();
    std::cout <<std::endl;

    std::cout << "Test OperationTest:"<<std::endl;
    OperationTest();
    std::cout <<std::endl;

    std::cout << "Test WrongDimensionsTest:"<<std::endl;
    WrongDimensionsTest();
    std::cout <<std::endl;

    std::cout << "Test WrongOperationDimensionTest:"<<std::endl;
    WrongOperationDimensionTest();
    std::cout <<std::endl;

    std::cout << "Test BoolTest:"<<std::endl;
    BoolTest();
    std::cout <<std::endl;

    std::cout << "SUCCESS\n";
    return 0;
}
