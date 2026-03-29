# BambuHelper v2.5 BETA Release Notes

## Power Monitoring via Tasmota (NEW)

- **Live watt display** - shows current power consumption from a Tasmota-flashed smart plug in the bottom status bar, alongside the layer counter
- **Two display modes**: alternate between layer count and watts every 4 seconds, or always show watts
- **Configurable poll interval** - HTTP API polling every 10, 15, 20, or 30 seconds (Tasmota HTTP, no MQTT broker required)
- **Print energy summary** - on the "Print Complete" screen, total kWh consumed during the print job is shown between the filename and the status bar (e.g. `⚡ 0.234 kWh`)
- Graceful fallback: if the plug is offline or not yet polled, layer count is shown instead - no crashes
- Configured in a new "Power Monitoring" section in the web UI; disabled by default, zero impact when not configured

## Screensaver brightness (NEW)
*contributed by [@theNailz](https://github.com/theNailz) in [#16](https://github.com/Keralots/BambuHelper/pull/16)*

- **Separate brightness for clock/screensaver screen** - display can automatically dim when idle without affecting brightness during active printing
- Slider appears in the Display section under "Show clock after print" (hidden when clock is disabled)
- Respects night mode: during night hours, whichever brightness is lower wins
- Included in settings export/import, backwards-compatible with existing configs

## ESP32-C3 Super Mini support (NEW)
*contributed by [@noliran](https://github.com/noliran) in [#13](https://github.com/Keralots/BambuHelper/pull/13)*

- **New build target** for ESP32-C3 Super Mini with ST7789 1.69" 240x280 display
- Separate PlatformIO environment (`pio run -e esp32c3`), does not affect existing S3 or CYD builds
- Includes pre-build patch script for a TFT_eSPI bug on C3: `SPI2_HOST` (host enum = 1) was used where the bus number (2) is required, causing a Store access fault on the first SPI write. Patched automatically before compilation until upstream fix is merged

## Web UI security fixes
*contributed by [@theNailz](https://github.com/theNailz) in [#18](https://github.com/Keralots/BambuHelper/pull/18)*

- **XSS hardening** - dynamic content from API responses (printer names, MQTT error text, state values) is now HTML-escaped before injection via `innerHTML`
- Status messages (import, OTA, cloud logout) switched from `innerHTML` to `textContent` where no markup is needed - cleaner and safer
- Exploitation would require a malicious printer name or compromised API response, but this is now properly handled regardless

## Web UI error handling improvements
*contributed by [@theNailz](https://github.com/theNailz) in [#19](https://github.com/Keralots/BambuHelper/pull/19)*

- **Meaningful error messages** - generic "Error" toast replaced with descriptive messages ("Save failed", "Network error", "Buzzer test failed", etc.) across all settings actions
- Empty `catch` blocks now log to `console.warn` with function name, making browser-side debugging possible when troubleshooting network or API failures

## Web UI polling optimization
*contributed by [@theNailz](https://github.com/theNailz) in [#20](https://github.com/Keralots/BambuHelper/pull/20)*

- **Timers stop when sections are collapsed** - live stats (3s) and diagnostics (5s) polling now only runs when the relevant section is actually open
- Previously both `setInterval` timers ran continuously from page load regardless of what was visible, wasting bandwidth and ESP32 CPU cycles on long-lived browser sessions
