## Написать класс-матрицу, тип элементов int

В конструкторе задается количество рядов и строк. Поддерживаются оперции:
- получить количество строк(rows)/столбцов(columns);
- получить конкретный элемент;
- умножить на число(*=);
- вывод матрицы в поток (ostream);
- сложение двух матриц;
- сравнение на равенство/неравенство;

В случае ошибки выхода за границы бросается исключение:

```c++
throw std::out_of_range("")
```

Нужно самостоятельно выделять память при помощи new (вектор использовать нельзя!).
