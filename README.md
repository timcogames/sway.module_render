# sway.module_graphics [![Discord](https://discordapp.com/api/guilds/402238411639095297/widget.png)](https://discord.gg/vCMcgwQ)

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
`ENABLE_COVERAGE` | Enable coverage builds | `OFF`

Запускаем сборку

```console
cmake --build .
```
