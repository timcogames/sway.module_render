# sway.module_render

[![codecov][codecov-svg]][codecov-url] [![Documentation][codedocs-svg]][codedocs-url] [![License][license-svg]][license-url]

## Клонирование проекта

```console
git clone --recursive https://github.com/timcogames/sway.module_render.git
```

## Сборка проекта

Создаем директорию build и переходим в неё

```console
mkdir build && cd ./build
```

Конфигурируем проект для сборки

```console
cmake -D CMAKE_BUILD_TYPE=Release \
      -D GLOB_THIRD_PARTY_DIR=/Users/<USER_NAME>/Documents/Third-party \
      -D MODULE_RENDER_ENABLE_TESTS=OFF \
      -D MODULE_RENDER_ENABLE_EXAMPLES=ON ../
```

Опция сборки | Тип | Описание | По умолчанию
:---|:---|:---|:---:
`CMAKE_BUILD_TYPE` | `STRING` | Тип сборки | `Debug`
`MODULE_RENDER_BUILD_SHARED` | `BOOL` | Сборка библиотеки общего пользования | `OFF`
`MODULE_RENDER_ENABLE_COVERAGE` | `BOOL` | Включает поддержку сбора данных о покрытии кода тестами | `OFF`
`MODULE_RENDER_ENABLE_TESTS` | `BOOL` | Включает построение тестов | `OFF`
`MODULE_RENDER_ENABLE_EXAMPLES` | `BOOL` | Включает построение примеров | `OFF`

Запускаем сборку

```console
cmake --build ./
```

## Contributing

См. [CONTRIBUTING](./github/CONTRIBUTING.md)

[codecov-svg]: https://codecov.io/gh/timcogames/sway.module_render/branch/master/graph/badge.svg
[codecov-url]: https://codecov.io/gh/timcogames/sway.module_render
[codedocs-svg]: https://codedocs.xyz/timcogames/sway.module_render.svg
[codedocs-url]: https://codedocs.xyz/timcogames/sway.module_render/
[license-svg]: https://img.shields.io/github/license/mashape/apistatus.svg
[license-url]: LICENSE
