# sway.module_graphics

[![Build Status](https://travis-ci.com/timcogames/sway.module_graphics.svg?branch=master)](https://travis-ci.com/timcogames/sway.module_graphics)
[![codecov](https://codecov.io/gh/timcogames/sway.module_graphics/branch/master/graph/badge.svg)](https://codecov.io/gh/timcogames/sway.module_graphics)
[![BCH compliance](https://bettercodehub.com/edge/badge/timcogames/sway.module_graphics?branch=master)](https://bettercodehub.com/)
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
