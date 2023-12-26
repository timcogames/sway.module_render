#### Конфигурируем проект для сборки

```console
cmake -D CMAKE_BUILD_TYPE=Release \
      -D MODULE_RENDER_ENABLE_TESTS=OFF \
      -D MODULE_RENDER_ENABLE_EXAMPLES=ON \
      ../
```

#### Собираем проект

```console
cmake --build ./
```
