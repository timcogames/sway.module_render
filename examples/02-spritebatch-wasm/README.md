#### Конфигурируем проект для сборки

```console
cmake -D CMAKE_BUILD_TYPE=Release \
      -D GLOB_THIRD_PARTY_DIR=/Users/<USER_NAME>/Documents/Third-party \
      -D GLOB_EMSCRIPTEN_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/emsdk/upstream/emscripten \
      -D GLOB_EMSCRIPTEN_PLATFORM=ON \
      -D GLOB_EMSCRIPTEN_USE_BINDINGS=OFF \
      -D MODULE_CORE_LIB_TYPE=object \
      -D MODULE_CORE_ENVIRONMENT= \
      -D MODULE_CORE_COMPILATION= \
      -D MODULE_RMS_LIB_TYPE=object \
      -D MODULE_RENDER_LIB_TYPE=static \
      -D MODULE_RENDER_ENVIRONMENT=node \
      -D MODULE_RENDER_COMPILATION=async \
      -D MODULE_RENDER_MT=ON \
      -D MODULE_RENDER_ENABLE_TESTS=OFF \
      -D MODULE_RENDER_ENABLE_EXAMPLES=ON \
      ../
```

#### Собираем проект

```console
cmake --build ./
```

#### Запускаем сервер

```console
# deprecated
python3 -m http.server 7800 --directory ./../bin

python3 ./server.py
```

#### Запускаем приложение в браузере

```console
http://localhost:7800
```
