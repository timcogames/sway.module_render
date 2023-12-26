#### Конфигурируем проект для сборки

```console
cmake -D CMAKE_BUILD_TYPE=Release \
      -D MODULE_RENDER_ENABLE_EXAMPLES=ON ../
```

#### Запускаем сборку

```console
cmake --build ./
```

#### Запускаем приложение

```console
./../bin/libmodule_render_examples_material
```
