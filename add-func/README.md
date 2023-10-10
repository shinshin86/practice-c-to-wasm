# add-func

Created to learn C and compile to Wasm.

## Usage (Wasm)

```sh
emcc -O3 -s WASM=1 -s EXPORTED_FUNCTIONS="['_add']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap']" -o add.js add.c
node main.js
```