#### Реализовать класс для работы с большими целыми числами
- Размер числа ограничен только размером памяти;
- Нужно поддержать семантику работы с обычным int32_t;
- Реализовать конструктор, принимающий std::string;
- std::vector и другие контейнеры использовать нельзя - управляйте памятью самостоятельно;
- Реализовать:
    - оператор вывода в поток;
    - сложение;
    - вычитание;
    - умножение (для искушенных слушателей можно попробовать реализовать алгоритм Карацубы, но за O(n^2) тоже сойдёт);
    - унарный минус;
    - все операции сравнения (сравнения только BigInt с другим BigInt, с int32_t не нужно реализовывать операторы сравнения);
    - копирующий и перемещающий конструкторы/операторы;
- Сложение/вычитание/умножение нужно сделать c BigInt, так и с int32_t (достаточно реализовать оператор, где int32_t будет с правой стороны (слева от BigInt не нужно), например: big_int1 + big_int2, или big_int1 + 123);
