import fs from 'node:fs';
import path from 'node:path';

const ar = JSON.parse(fs.readFileSync(path.resolve(import.meta.dirname, '..', 'translations', 'ar.json'), 'utf8'));
const root = path.resolve(import.meta.dirname, '..', 'src');

function walk(dir, out = []) {
  for (const e of fs.readdirSync(dir, { withFileTypes: true })) {
    const p = path.join(dir, e.name);
    if (e.isDirectory()) walk(p, out);
    else if (e.name.endsWith('.cpp')) out.push(p);
  }
  return out;
}

const hint = /InputTextWithHint\(\s*"((?:[^"\\]|\\.)*)"\s*,\s*"((?:[^"\\]|\\.)*)"/g;
const missing = new Set();

for (const file of walk(root)) {
  const text = fs.readFileSync(file, 'utf8');
  let match;
  hint.lastIndex = 0;
  while ((match = hint.exec(text))) {
    const value = match[2].replace(/\\(n|t|r|"|\\)/g, (_, c) => ({ n: '\n', t: '\t', r: '\r', '"': '"', '\\': '\\' })[c]);
    if (value && !value.startsWith('##') && !(value in ar)) {
      missing.add(value);
      console.log(path.relative(root, file).replaceAll('\\', '/'), '|', JSON.stringify(value));
    }
  }
}

console.log('missing hints:', missing.size);
