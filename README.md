# sway.module_graphics

[![Build Status][travis-svg]][travis-url] [![codecov][codecov-svg]][codecov-url] [![BCH compliance][bettercodehub-svg]][bettercodehub-url] [![Documentation][codedocs-svg]][codedocs-url] [![License][license-svg]][license-url]

## Клонирование проекта

```console
git clone --recursive https://github.com/timcogames/sway.module_graphics.git
```

## Сборка проекта

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

## Contributing

См. [CONTRIBUTING](./github/CONTRIBUTING.md)

[travis-svg]: https://travis-ci.com/timcogames/sway.module_graphics.svg?branch=master
[travis-url]: https://travis-ci.com/timcogames/sway.module_graphics
[codecov-svg]: https://codecov.io/gh/timcogames/sway.module_graphics/branch/master/graph/badge.svg
[codecov-url]: https://codecov.io/gh/timcogames/sway.module_graphics
[bettercodehub-svg]: https://bettercodehub.com/edge/badge/timcogames/sway.module_graphics?branch=master
[bettercodehub-url]: https://bettercodehub.com/
[codedocs-svg]: https://codedocs.xyz/timcogames/sway.module_graphics.svg
[codedocs-url]: https://codedocs.xyz/timcogames/sway.module_graphics/
[license-svg]: https://img.shields.io/github/license/mashape/apistatus.svg
[license-url]: LICENSE
