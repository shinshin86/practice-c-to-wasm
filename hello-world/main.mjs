import hello from './hello.js';

hello.onRuntimeInitialized = () => {
  hello._main();
}
