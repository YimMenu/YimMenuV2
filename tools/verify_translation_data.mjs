import fs from 'node:fs';
import path from 'node:path';

const file = path.resolve(import.meta.dirname, '..', 'src', 'core', 'translation', 'TranslationData.cpp');
const text = fs.readFileSync(file, 'utf8');

const lines = text.split('\n').filter((l) => l.trimStart().startsWith('{') && l.trimEnd().endsWith('},'));
console.log('entries in file:', lines.length);

const decode = (literal) => {
  // C++ string literal (possibly split into adjacent literals)
  const parts = [...literal.matchAll(/"((?:[^"\\]|\\.)*)"/g)].map((m) => m[1]);
  const bytes = [];
  for (const part of parts) {
    for (let i = 0; i < part.length; i++) {
      const c = part[i];
      if (c === '\\') {
        const n = part[++i];
        if (n === 'x') {
          bytes.push(parseInt(part.slice(i + 1, i + 3), 16));
          i += 2;
        } else if (n === 'n') bytes.push(10);
        else if (n === 't') bytes.push(9);
        else if (n === 'r') bytes.push(13);
        else if (n === '"') bytes.push(34);
        else if (n === '\\') bytes.push(92);
        else throw new Error('unknown escape ' + n);
      } else {
        bytes.push(c.charCodeAt(0));
      }
    }
  }
  return Buffer.from(bytes).toString('utf8');
};

const table = lines.map((line) => {
  const body = line.trim().replace(/^\{/, '').replace(/\},$/, '');
  let inString = false;
  let escaped = false;
  let split = -1;
  for (let i = 0; i < body.length - 2; i++) {
    const c = body[i];
    if (inString) {
      if (escaped) escaped = false;
      else if (c === '\\') escaped = true;
      else if (c === '"') {
        if (body[i + 1] === ',' && body[i + 2] === ' ') {
          split = i + 1;
          break;
        }
        inString = false;
      }
    } else if (c === '"') {
      inString = true;
    }
  }
  if (split < 0) throw new Error('bad line: ' + line);
  return [decode(body.slice(0, split)), decode(body.slice(split + 1))];
});

const ar = JSON.parse(fs.readFileSync(path.resolve(import.meta.dirname, '..', 'translations', 'ar.json'), 'utf8'));
console.log('translations in source:', Object.keys(ar).length);

let mismatches = 0;
for (const [english, arabic] of table) {
  if (!(english in ar)) {
    console.log('unexpected key:', JSON.stringify(english));
    mismatches++;
  } else if (arabic.length === 0) {
    console.log('empty value:', english);
    mismatches++;
  }
}

// binary search simulation
function lookup(key) {
  let lo = 0;
  let hi = table.length;
  while (lo < hi) {
    const mid = (lo + hi) >> 1;
    if (table[mid][0] < key) lo = mid + 1;
    else hi = mid;
  }
  return lo < table.length && table[lo][0] === key ? table[lo][1] : null;
}

for (const key of ['God Mode', 'Self', 'Network', 'Teleport to Waypoint', 'Wheel Color', 'Unknown!']) {
  console.log(key, '=>', lookup(key));
}

console.log('mismatches', mismatches);
