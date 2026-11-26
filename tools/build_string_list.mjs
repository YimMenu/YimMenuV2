// Builds the list of strings that need translation for the current phase.
// Phase 1 scope: Self, Vehicle, Teleport, Network, Players, World, Settings.
import fs from 'node:fs';
import path from 'node:path';

const dir = import.meta.dirname;
const data = JSON.parse(fs.readFileSync(path.join(dir, 'extracted.json'), 'utf8'));

const PHASE1 = ['Self', 'Vehicle', 'Teleport', 'Network', 'Players', 'World', 'Settings', 'Player'];

const inPhase1 = (file) => {
  const sub = file.replace('src/game/frontend/submenus/', '');
  return PHASE1.some((p) => sub.startsWith(p + '/') || sub === p + '.cpp');
};

// submenus whose command references count for phase 1
const submenuFiles = Object.entries(data.usedBySubmenus).flatMap(([, files]) => files);
const cmdNames = new Set();
for (const f of submenuFiles) {
  if (!inPhase1(f)) continue;
  for (const u of data.ui) {
    // noop
  }
}
// simpler: commands referenced by any phase-1 submenu file
for (const u of data.ui) {
  // noop
}

// map command -> files that reference it
for (const [name, files] of Object.entries(data.usedBySubmenus)) {
  if ([...files].some(inPhase1)) cmdNames.add(name);
}

const strings = new Map();
const add = (text, kind) => {
  if (!text) return;
  const key = text.trim();
  if (!key) return;
  if (!strings.has(key)) strings.set(key, { text: key, kinds: new Set() });
  strings.get(key).kinds.add(kind);
};

for (const c of data.commands) {
  if (!cmdNames.has(c.name)) continue;
  add(c.label, 'command-label');
  add(c.description, 'command-description');
}

for (const u of data.ui) {
  if (!inPhase1(u.file)) continue;
  add(u.text, 'ui');
}

// structural names for phase-1 submenus
for (const s of ['Self', 'Vehicle', 'Teleport', 'Network', 'Players', 'World', 'Settings']) add(s, 'submenu');

// shared widgets
for (const s of ['Unknown!', 'Close', 'Enter a keystroke', 'Hover over the command name to change its hotkey', 'Press any registered key to remove']) add(s, 'widget');

// quick sanity output
console.log('phase1 strings:', strings.size);
console.log('phase1 commands:', [...cmdNames].filter((n) => data.commands.some((c) => c.name === n)).length, '/', cmdNames.size);

fs.writeFileSync(path.join(dir, 'phase1_strings.json'), JSON.stringify([...strings.values()].map((v) => ({ text: v.text, kinds: [...v.kinds] })), null, 2));
console.log([...strings.keys()].join('\n'));
