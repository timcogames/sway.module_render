# sway.module_graphics

[![codecov][codecov-svg]][codecov-url] [![BCH compliance][bettercodehub-svg]][bettercodehub-url] [![Documentation][codedocs-svg]][codedocs-url] [![License][license-svg]][license-url]

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
cmake -DCMAKE_BUILD_TYPE=Release -DMODULE_GAPI_GL_SHARED_LIB=ON -DMODULE_GRAPHICS_ENABLE_TESTS=OFF -DMODULE_GRAPHICS_ENABLE_EXAMPLES=ON ../
```

Опция сборки | Тип | Описание | По умолчанию
:---|:---|:---|:---:
`BOOST_ROOT` | `PATH` | Путь до корневой директории Boost библиотеки | `-`
`CMAKE_BUILD_TYPE` | `STRING` | Тип сборки | `Debug`
`MODULE_GRAPHICS_BUILD_SHARED` | `BOOL` | Сборка библиотеки общего пользования | `OFF`
`MODULE_GRAPHICS_ENABLE_COVERAGE` | `BOOL` | Включает поддержку сбора данных о покрытии кода тестами | `OFF`
`MODULE_GRAPHICS_ENABLE_TESTS` | `BOOL` | Включает построение тестов | `OFF`
`MODULE_GRAPHICS_ENABLE_EXAMPLES` | `BOOL` | Включает построение примеров | `OFF`

Запускаем сборку

```console
cmake --build ./
```

## Contributing

См. [CONTRIBUTING](./github/CONTRIBUTING.md)

[codecov-svg]: https://codecov.io/gh/timcogames/sway.module_graphics/branch/master/graph/badge.svg
[codecov-url]: https://codecov.io/gh/timcogames/sway.module_graphics
[bettercodehub-svg]: https://bettercodehub.com/edge/badge/timcogames/sway.module_graphics?branch=master
[bettercodehub-url]: https://bettercodehub.com/
[codedocs-svg]: https://codedocs.xyz/timcogames/sway.module_graphics.svg
[codedocs-url]: https://codedocs.xyz/timcogames/sway.module_graphics/
[license-svg]: https://img.shields.io/github/license/mashape/apistatus.svg
[license-url]: LICENSE
