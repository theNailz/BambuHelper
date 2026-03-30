# BambuHelper — Development Guide

## Dev cycle

Follow these steps in order — no skipping.

### 1. Create a beads issue

Before writing any code:

```bash
bd create --title="What you're doing" --type=feature|bug|chore --priority=2 --description="Why"
bd update <id> --claim
```

### 2. Create a feature branch

```bash
git fetch origin
git checkout -b feature/my-change origin/main
```

**Always branch from `origin/main`, not local `main`.** Local main contains commits (CLAUDE.md, AGENTS.md, .beads/, .gitignore) that must never appear in PRs to upstream.

### 3. Write code

All frontend (HTML/CSS/JS) is embedded in `src/web_server.cpp` as C++ PROGMEM strings. There are no separate asset files.

### 4. Build

```bash
pio run -e esp32s3
```

Build output lands in `.pio/build/esp32s3/firmware.bin`.

### 5. Flash and test on device — MANDATORY before committing

A test device is available at **http://192.168.178.175/**. Flash via curl:

```bash
curl -F "firmware=@.pio/build/esp32s3/firmware.bin" http://192.168.178.175/ota/upload
```

Wait ~10 seconds for reboot, then verify the device is back online and the change works as expected. For web UI changes, use Chrome MCP to navigate and take screenshots. **Do not use Chrome MCP for file uploads — it cannot upload files.**

**Never commit without first flashing and verifying on the real device.**

### 6. Commit

```bash
git add <files>
git commit -m "Description of change"
```

### 7. Rebase and verify before pushing

Always rebase onto the latest upstream before pushing:

```bash
git fetch origin
git rebase origin/main
```

If there are conflicts, resolve them now — not after the PR is open. After resolving:

```bash
git rebase --continue
pio run -e esp32s3          # rebuild to confirm the rebase didn't break anything
```

### 8. Pre-PR checklist

Before pushing and creating the PR, verify all of the following:

- [ ] `git log --oneline origin/main..HEAD` — only your commit(s), no local-only commits (CLAUDE.md, .beads/, AGENTS.md, gitignore)
- [ ] `git diff origin/main --stat` — only files relevant to the change
- [ ] Build passes after rebase
- [ ] Flashed and tested on device after rebase

### 9. Push

```bash
git push fork feature/my-change
```

### 10. Create a pull request

```bash
gh pr create --repo Keralots/BambuHelper --head theNailz:feature/my-change \
  --title "Short title" --body "Description of the change"
```

Write the PR description as the developer — no AI attribution anywhere (no `🤖`, no "Generated with Claude Code", no "Co-Authored-By" lines — not in the title, body, or comments).

### 11. Close beads issue and push

```bash
bd close <id>
bd dolt push
```

---

## Git remotes

| Remote | URL | Purpose |
|---|---|---|
| `origin` | `Keralots/BambuHelper` | Upstream repo |
| `fork` | `theNailz/BambuHelper` | Our fork, push here |

Always push to `fork`, create PRs against `origin`.

---

## Beads issue tracking

```bash
bd list                   # List all issues
bd ready                  # Find tasks with no blockers
bd show <id>              # View issue details
bd create --title="..." --type=bug --priority=2 --description="..."
bd update <id> --claim    # Claim work
bd close <id>             # Mark done
bd dolt push              # Push beads data
```

Issue types: `bug`, `feature`, `task`, `chore`, `epic`, `decision`
Priorities: P0 (critical) through P4 (backlog)

---

## Testing

There are no automated tests. Verification is manual:

1. **Build check** — `pio run -e esp32s3` must succeed with no errors
2. **OTA flash** — `curl -F "firmware=@.pio/build/esp32s3/firmware.bin" http://192.168.178.175/ota/upload`
3. **Web UI test** — use Chrome MCP to navigate http://192.168.178.175/ and verify changes
4. **Printer test** — verify MQTT connection and live data display on the TFT screen

---

## Merge binaries

```bash
python merge_bins.py              # Build WebFlasher + OTA for esp32s3
python merge_bins.py --board cyd  # Build for CYD
python merge_bins.py --ota        # OTA binary only
python merge_bins.py --full       # WebFlasher binary only
```

Output goes to `firmware/v{VERSION}/`.
