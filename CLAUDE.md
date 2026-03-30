# BambuHelper

ESP32 firmware for monitoring Bambu Lab 3D printers via MQTT. Displays real-time status (temperatures, progress, fan speeds) on a small TFT screen. Supports LAN direct and Bambu Cloud connections, dual printers, OTA updates, and a web-based configuration portal.

## Build targets

| Environment | Board | Display | Build command |
|---|---|---|---|
| `esp32s3` | ESP32-S3 Super Mini | ST7789 240x240 | `pio run -e esp32s3` |
| `cyd` | ESP32-2432S028 (CYD) | ILI9341 320x240 | `pio run -e cyd` |

Firmware version is defined in `include/config.h` as `FW_VERSION`.

## Project structure

```
src/
  main.cpp              # Setup/loop orchestrator
  web_server.cpp/h      # Config portal (embedded HTML/CSS/JS), OTA, JSON API
  bambu_mqtt.cpp/h      # MQTT over TLS, dual connections, backoff
  bambu_cloud.cpp/h     # Cloud region URLs, JWT extraction
  settings.cpp/h        # NVS persistence (all settings)
  wifi_manager.cpp/h    # WiFi STA/AP, static IP, reconnection
  display_ui.cpp/h      # Screen state machine (10 states)
  display_gauges.cpp/h  # Arc gauges, progress bar, color rendering
  display_anim.cpp/h    # Loading spinner, pulse, celebration animations
  clock_mode.cpp/h      # Digital clock display
  clock_pong.cpp/h      # Breakout game clock screensaver
  button.cpp/h          # Push button / TTP223 touch input
  buzzer.cpp/h          # Passive buzzer notifications
  icons.h               # 16x16 pixel-art icons
  timezones.cpp/h       # Timezone database

include/
  config.h              # Pin defs, constants, FW_VERSION, RGB565 colors
  bambu_state.h         # Data structures (BambuState, PrinterConfig)
  layout.h              # Layout dispatcher
  layout_default.h      # 240x240 layout
  layout_cyd.h          # 320x240 layout

tools/
  get_token.py          # Extract Bambu Cloud token
  mqtt_test.py          # Diagnostic MQTT tester
```

## Development workflow

See **[DEVELOPMENT.md](DEVELOPMENT.md)** for the full step-by-step dev cycle including branching, building, flashing, rebasing, and PR creation.

## Commit and PR rules

- Author: **Niels Timmer <niels@nielstimmer.nl>**
- Never add a `Co-Authored-By` line for Claude or any AI
- Never expose AI involvement in commits, PRs, code comments, or PR descriptions
- Write commit messages and PR descriptions as if you are the developer
- No `🤖`, no "Generated with Claude Code" — not in title, body, or comments

## Tooling

- Use the **PlatformIO skill** (`o2scale/electronics-agent-kit@platformio`) for all ESP32/embedded/build-related work
- Use **Chrome MCP** for web UI navigation and screenshots — not for file uploads (use curl for OTA)
- Use **beads** (`bd`) for all issue tracking — never TodoWrite or markdown task lists

## Key dependencies

- `bodmer/TFT_eSPI` — display driver
- `bodmer/TFT_eWidget` — UI widgets
- `knolleary/PubSubClient` — MQTT client
- `bblanchon/ArduinoJson` — JSON parsing
- `XPT2046_Touchscreen` — touch screen (CYD only)
