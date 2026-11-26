import fs from 'node:fs';
import path from 'node:path';

const ar = JSON.parse(fs.readFileSync(path.resolve(import.meta.dirname, '..', 'translations', 'ar.json'), 'utf8'));
const root = path.resolve(import.meta.dirname, '..', 'src', 'game', 'frontend', 'submenus');
const phase = /^(Self|Vehicle|Teleport|Network|Players|World|Settings|Player)([\\/]|\.cpp)/;

function walk(dir, out = []) {
  for (const e of fs.readdirSync(dir, { withFileTypes: true })) {
    const p = path.join(dir, e.name);
    if (e.isDirectory()) walk(p, out);
    else if (e.name.endsWith('.cpp')) out.push(p);
  }
  return out;
}

const call =
  /(?:CommandItem|PlayerCommandItem|BoolCommandItem|IntCommandItem|FloatCommandItem|Vector3CommandItem|ListCommandItem|ColorCommandItem|StringCommandItem)>\("[a-z0-9_]+"_J,\s*"((?:[^"\\]|\\.)*)"/g;

const overrides = new Set();
for (const file of walk(root)) {
  const relative = path.relative(root, file).replaceAll('\\', '/');
  if (!phase.test(relative)) continue;

  const text = fs.readFileSync(file, 'utf8');
  let match;
  call.lastIndex = 0;
  while ((match = call.exec(text))) {
    const value = match[1];
    if (value && !value.startsWith('##')) overrides.add(value);
  }
}

console.log('overrides', overrides.size);
for (const value of [...overrides].sort()) console.log(JSON.stringify(value), value in ar ? '(translated)' : '');
