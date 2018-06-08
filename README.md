# sway.module_graphics [![Discord](https://discordapp.com/api/guilds/402238411639095297/widget.png)](https://discord.gg/vCMcgwQ)

#### Клонирование проекта

```console
git clone --recursive https://github.com/timcogames/sway.module_graphics.git
```

#### Сборка проекта

```console
mkdir build && cd ./build
cmake -DCMAKE_BUILD_TYPE=Release ../
make
```

```console
nm -gC ../bin/libmodule_graphics.so.*
```

#### Опции сборки

* `-DCMAKE_BUILD_TYPE=Debug`

