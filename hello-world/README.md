# hello-world

Created to learn C and compile to Wasm.

## Usage (C)

```sh
clang hello.c -o hello
./hello
```

## Usage (Wasm)

```sh
emcc hello.c -o hello.js -s "EXPORTED_FUNCTIONS=['_main']" -s INVOKE_RUN=0
node main.mjs
```