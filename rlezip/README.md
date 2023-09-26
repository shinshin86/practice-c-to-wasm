# rlezip

Created to learn C and compile to Wasm.

## Usage (C)

```sh
# Creation of test data
bash gen_test_data.sh

clang rlezip.c -o rlezip
./rlezip
```

### test

```sh
bash test_script.sh
```

### generate test data

```sh
bash gen_test_data.sh
```

## Usage (Wasm)

```sh
# Creation of test data
bash gen_test_data.sh

emcc rlezip.c -o rlezip.js -s "EXPORTED_FUNCTIONS=['_main']" -s EXPORTED_RUNTIME_METHODS='["FS"]' -s INVOKE_RUN=0 --preload-file target_directory@/working/target_directory
node main.mjs
```