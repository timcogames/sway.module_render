#### Конфигурируем проект для сборки

```console
cmake -D CMAKE_BUILD_TYPE=Release \
      -D CUSTOM_EMSCRIPTEN_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/emsdk/upstream/emscripten \
      -D GLOB_EMSCRIPTEN_PLATFORM=ON \
      -D GLOB_EMSCRIPTEN_USE_BINDINGS=ON \
      -D MODULE_RENDER_ENABLE_EXAMPLES=ON ../
```

#### Собираем проект

```console
cmake --build ./
```

#### Запускаем сервер

```console
python3 -m http.server 7800 --directory ./../bin
```

#### Запускаем приложение в браузере

```console
http://localhost:7800
```
