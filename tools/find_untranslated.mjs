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

const calls =
  /ImGui::(Text|TextDisabled|TextUnformatted|BulletText|SetTooltip|Button|Checkbox|BeginCombo|BeginListBox|InputText|InputTextMultiline|InputTextWithHint|InputInt|InputScalar|SliderFloat|SeparatorText|BeginTabItem|SmallButton|Selectable|OpenPopup|BeginPopupModal)\("((?:[^"\\]|\\.)*)"/g;

const missing = new Map();
for (const file of walk(root)) {
  const relative = path.relative(root, file).replaceAll('\\', '/');
  if (!phase.test(relative)) continue;

  const text = fs.readFileSync(file, 'utf8');
  let match;
  calls.lastIndex = 0;
  while ((match = calls.exec(text))) {
    const value = match[2];
    if (!value || value.startsWith('##') || value === '%s') continue;
    if (!(value in ar)) {
      if (!missing.has(value)) missing.set(value, []);
      missing.get(value).push(relative);
    }
  }
}

fs.writeFileSync(path.join(import.meta.dirname, 'untranslated.json'), JSON.stringify([...missing.keys()], null, 2));
console.log('wrote', missing.size);
