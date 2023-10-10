const fs = require('fs/promises');
const addModule = require('./add.js');

async function createAddModule() {
  const buffer = await fs.readFile('add.wasm');
  addModule.wasmBinary = buffer;

  return new Promise((resolve) => {
    addModule.onRuntimeInitialized = () => {
      console.log('Runtime initialized');
      resolve(addModule);
    };
  });
}

(async () => {
  const module = await createAddModule();
  const add = module.cwrap('add', 'number', ['number', 'number']);
  console.log(add(10, 20)); // Output: 30
})();