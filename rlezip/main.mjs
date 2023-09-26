import rlezip from './rlezip.js';
import fs from 'node:fs/promises';

rlezip.onRuntimeInitialized = async () => {
  rlezip._main();

  const compressedData = rlezip.FS.readFile('/working/output.zip');
  await fs.writeFile('output.zip', compressedData);
}
