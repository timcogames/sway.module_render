# sway.module_graphics

[![Documentation](https://codedocs.xyz/timcogames/sway.module_graphics.svg)](https://codedocs.xyz/timcogames/sway.module_graphics/)

### Клонирование проекта

```console
git clone --recursive https://github.com/timcogames/sway.module_graphics.git
```

### Сборка проекта

Создаем директорию build и переходим в неё

```console
mkdir build && cd ./build
```

Конфигурируем проект для сборки

```console
cmake -DCMAKE_BUILD_TYPE=Release ../
```

Опция сборки | Описание | По умолчанию
:---|:---|:---:
`BUILD_SHARED_LIBS` | Сборка библиотеки общего пользования | `OFF`
`ENABLE_COVERAGE` | Включает поддержку сбора данных о покрытии кода тестами | `OFF`
`ENABLE_TESTS` | Включает построение тестов | `OFF`

Запускаем сборку

```console
cmake --build .
```
