import fs from 'node:fs';
import path from 'node:path';

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

for (const file of walk(root)) {
  const relative = path.relative(root, file).replaceAll('\\', '/');
  if (!phase.test(relative)) continue;

  const lines = fs.readFileSync(file, 'utf8').split('\n');
  lines.forEach((line, index) => {
    if (!/ImGui::\w+\(\s*"/.test(line)) return;
    if (line.includes('Translation::')) return;
    if (/\(\s*"##/.test(line)) return;
    console.log(`${relative}:${index + 1}: ${line.trim()}`);
  });
}
