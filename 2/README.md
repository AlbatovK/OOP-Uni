# OOP Lab 2

## Вариант 17 — `таблица ресурсов`

> Простой класс: Ресурс — представляется наименованием ресурса, потреблением (кг/д), производством (кг/д) и ценой (
> у.е./кг).

### Методы простого класса (помимо общих):

- `создание экземпляра класса с инициализацией наименованием, потреблением,
  производством и ценой`
- `создание экземпляра класса с инициализацией только наименованием и ценой`
- `(+) объединение двух одинаковых ресурсов — потребление и производство
  складываются, а цена выбирается наименьшая`
- `(<=>) сравнение двух ресурсов по наименованию`
- `Если используемый вами компилятор/стандарт языка ещё не поддерживает оператор “<=>”, вместо этого реализовать 2
  оператора: “==” и “<”`
- `вычисление ориентировочной прибыльности (в у.е.) ресурса за неделю (может быть
  отрицательной)`
- `(*) увеличение оборота (производства и потребления) ресурса в заданное число раз`

> Сложный класс: Таблица ресурсов – определяется множеством ресурсов, хранимым при
> помощи упорядоченной по наименованию ресурса таблицы.

### Методы сложного класса (помимо общих)

- `создание экземпляров класса с инициализацией заданным количеством ресурсов из
  массива ресурсов`
- `(+=) добавление нового ресурса в таблицу`
- `([]) получение ресурса по его наименованию (при помощи двоичного поиска;
  возврат по ссылке)`
- `проверка состояния таблицы (пустая, частично заполнена или полная)`
- `удаление ресурса с заданным наименованием из таблицы`
- `вычисление общей прибыльности по всем ресурсам`
- `(*) увеличение оборота всех ресурсов в заданное число раз`
- `переименование заданного ресурса (передаются старое и новое наименования)`

## License

```
MIT License

Copyright (c) 2024 Konstantin Albatov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
