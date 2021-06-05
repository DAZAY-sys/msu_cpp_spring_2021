### Написать свой контейнер Vector аналогичный std::vector, аллокатор и итератор произвольного доступа для него.

Из поддерживаемых методов достаточно:
- operator[]
- push_back
- pop_back
- emplace_back
- empty
- size
- clear
- begin, rbegin
- end, rend
- resize
- reserve
- capacity

Интерфейс аллокатора и итератора смотрите в [документации](https://en.cppreference.com/w/).
