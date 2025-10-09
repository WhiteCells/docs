SDL 3.3 版本在 `main` 分支，`SDL_mixer` 需要 SDL 3.3 版本。

```sh
git clone git@github.com:libsdl-org/SDL.git
git clone git@github.com:libsdl-org/SDL_ttf.git
git clone git@github.com:libsdl-org/SDL_image.git
git clone git@github.com:libsdl-org/SDL_mixer.git
```



```sh
cd SDL
cmake -B build -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --build build -j$(nproc)
cmake --install build

cd SDL_ttf
cmake -B build -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --build build -j$(nproc)
cmake --install build

cd SDL_image
cmake -B build -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --build build -j$(nproc)
cmake --install build

cd SDL_mixer
cmake -B build -DCMAKE_INSTALL_PREFIX=/usr/local -DSDL_DIR=/path/SDL3/lib/cmake/SDL3
cmake --build build -j$(nproc)
cmake --install build
```

