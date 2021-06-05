### Написать функцию для форматирования строки

Поддерживаться должен любой тип, который может быть выведен в поток вывода. Формат строки форматирования:
```
"{0} any text {1} {0}"
```
Номер в фигурных скобках - номер аргумента.

Правила:
- Фигурные скобки - зарезервированный символ, если встречаются вне контекста {n} выбрасывать исключение;
- Используйте variadic function (см. лекцию про шаблоны), чтобы передавать неизвестное число аргументов в функцию разных типов;
- То что, выводим, должно уметь записываться в std::ostream (то есть выводиться в поток при помощи оператора <<);
- Если первый аргумент format, не соответвует параметрам (например, их меньше чем задано в строке) или некорректное использование скобок, то кидать и обрабатывать свои исключения.