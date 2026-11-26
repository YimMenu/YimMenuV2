import fs from 'node:fs';
import path from 'node:path';

const root = path.resolve(import.meta.dirname, '..', 'src');

function walk(dir, out = []) {
  for (const e of fs.readdirSync(dir, { withFileTypes: true })) {
    const p = path.join(dir, e.name);
    if (e.isDirectory()) walk(p, out);
    else if (e.name.endsWith('.cpp') || e.name.endsWith('.hpp')) out.push(p);
  }
  return out;
}

let problems = 0;
for (const file of walk(root)) {
  if (file.endsWith('Translation.cpp') || file.endsWith('Translation.hpp') || file.endsWith('TranslationData.hpp') || file.endsWith('TranslationData.cpp')) continue;

  const text = fs.readFileSync(file, 'utf8');
  const uses = /\bTranslation::(Tr|TrLabel|TrOptionalLabel)\b/.test(text);
  const includes = /#include\s+"core\/translation\/Translation.hpp"/.test(text);

  if (uses && !includes) {
    console.log('missing include:', path.relative(root, file));
    problems++;
  }
}

console.log('problems', problems);
