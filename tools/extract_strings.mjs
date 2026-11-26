// Extracts translatable strings from the YimMenuV2 sources.
// Usage: node tools/extract_strings.mjs > tools/extracted.json
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

function unescapeCpp(s) {
  return s.replace(/\\(n|t|r|"|\\)/g, (_, c) => ({ n: '\n', t: '\t', r: '\r', '"': '"', '\\': '\\' })[c]);
}

const files = walk(root);
const rel = (p) => path.relative(path.resolve(root, '..'), p).replaceAll('\\', '/');

// --- 1. command definitions -------------------------------------------------
// Matches: static SomeCommand _Var{"name", "Label", "Description", ...};
const cmdRe = /\bstatic\s+([A-Za-z_][\w:]*)\s+(\w+)\s*\{/g;
const commands = new Map();
for (const f of files) {
  const text = fs.readFileSync(f, 'utf8');
  let m;
  cmdRe.lastIndex = 0;
  while ((m = cmdRe.exec(text))) {
    const type = m[1];
    const start = cmdRe.lastIndex;
    // find matching closing brace of this initializer
    let depth = 1, i = start;
    while (i < text.length && depth > 0) {
      if (text[i] === '{') depth++;
      else if (text[i] === '}') depth--;
      i++;
    }
    const body = text.slice(start, i - 1);
    const strings = [];
    const sre = /"((?:[^"\\]|\\.)*)"/g;
    let s;
    while ((s = sre.exec(body))) strings.push(unescapeCpp(s[1]));
    if (strings.length >= 2 && /^[a-z][a-z0-9_]*$/.test(strings[0])) {
      commands.set(strings[0], {
        type,
        var: m[2],
        name: strings[0],
        label: strings[1],
        description: strings[2] ?? '',
        file: rel(f),
      });
    }
  }
}

// --- 2. command references per submenu file ---------------------------------
const submenuRoot = path.join(root, 'game', 'frontend', 'submenus');
const submenuFiles = walk(submenuRoot);
const used = new Map(); // name -> Set(file)
for (const f of submenuFiles) {
  const text = fs.readFileSync(f, 'utf8');
  const re = /"([a-z0-9_]+)"_J/g;
  let m;
  while ((m = re.exec(text))) {
    if (!used.has(m[1])) used.set(m[1], new Set());
    used.get(m[1]).add(rel(f));
  }
}

// --- 3. raw UI strings ------------------------------------------------------
const uiCalls = [
  /\bImGui::Text\("((?:[^"\\]|\\.)*)"\)/g,
  /\bImGui::TextUnformatted\("((?:[^"\\]|\\.)*)"\)/g,
  /\bImGui::TextDisabled\("((?:[^"\\]|\\.)*)"\)/g,
  /\bImGui::BulletText\("((?:[^"\\]|\\.)*)"\)/g,
  /\bImGui::Button\("((?:[^"\\]|\\.)*)"/g,
  /\bImGui::Checkbox\("((?:[^"\\]|\\.)*)"/g,
  /\bImGui::SetTooltip\("((?:[^"\\]|\\.)*)"/g,
  /\bImGui::SeparatorText\("((?:[^"\\]|\\.)*)"\)/g,
  /\bImGui::BeginCombo\("((?:[^"\\]|\\.)*)"/g,
  /\bImGui::InputText\("((?:[^"\\]|\\.)*)"/g,
  /\bImGui::InputTextMultiline\("((?:[^"\\]|\\.)*)"/g,
  /\bButton\("((?:[^"\\]|\\.)*)"/g,
  /\bstd::make_shared<Button>\("((?:[^"\\]|\\.)*)"/g,
  /\bstd::make_shared<TabItem>\("((?:[^"\\]|\\.)*)"\)/g,
  /\bstd::make_shared<CollapsingHeaderItem>\("((?:[^"\\]|\\.)*)"\)/g,
  /\bstd::make_shared<Category>\("((?:[^"\\]|\\.)*)"\)/g,
  /\bstd::make_shared<Group>\("((?:[^"\\]|\\.)*)"/g,
  /\bTabItem\("((?:[^"\\]|\\.)*)"\)/g,
];

const uiStrings = [];
for (const f of submenuFiles) {
  const text = fs.readFileSync(f, 'utf8');
  for (const re of uiCalls) {
    re.lastIndex = 0;
    let m;
    while ((m = re.exec(text))) {
      const value = unescapeCpp(m[1]);
      if (!value || value.startsWith('##') || value.startsWith('###')) continue;
      if (/^[A-Za-z_]\w*$/.test(value) && !value.includes(' ')) {
        // likely an id or a format-only string; keep anyway if it has a space
      }
      uiStrings.push({ file: rel(f), text: value });
    }
  }
}

const dedupe = (arr) => [...new Set(arr)];
const report = {
  commands: [...commands.values()],
  ui: uiStrings,
  usedBySubmenus: Object.fromEntries([...used].map(([k, v]) => [k, [...v]])),
};

fs.writeFileSync(path.join(import.meta.dirname, 'extracted.json'), JSON.stringify(report, null, 2));
console.log('commands:', commands.size);
console.log('ui strings:', uiStrings.length, 'unique:', dedupe(uiStrings.map((u) => u.text)).length);
console.log('referenced command names:', used.size);
