# multi-file-sample

Created to learn C and compile to Wasm.

## Usage (C)

```sh
clang hello.c main.c -o multisample
./multisample
```

## Usage (Wasm)

```sh
emcc hello.c main.c -s WASM=1 -s INVOKE_RUN=0 -o multisample.js
node main.mjs
```