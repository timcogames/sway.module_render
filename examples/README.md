#### Конфигурируем проект для сборки

```console
cmake -DCMAKE_BUILD_TYPE=Release -DMODULE_GRAPHICS_ENABLE_EXAMPLES=ON ../
```

#### Запускаем сборку

```console
cmake --build ./
```

#### Запускаем приложение

```console
./../bin/libmodule_graphics_examples_material
```
