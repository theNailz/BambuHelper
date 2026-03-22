# BambuHelper v2.4 Release Notes

## OTA firmware update (NEW)

- **Web-based OTA updates** - upload new firmware directly from the web UI, no USB cable needed
- Upload a .bin file in the "WiFi & System" section, progress bar shows upload status
- All settings preserved after update (WiFi, printers, cloud tokens, display config)
- Client-side validation (file type, size) + server-side ESP32 magic byte check
- MQTT disconnects during upload to free memory, device restarts automatically after success
- Current firmware version shown in web UI

## Date format fix

- **Locale-aware date format** - clock screens (standard and Pong) now use DD.MM.YYYY in 24h mode and MM/DD/YYYY in 12h mode (previously always DD.MM.YYYY regardless of setting)
- **ETA date format** - print ETA on the dashboard now uses MM/DD format in 12h mode (was DD.MM)

## Screen wakeup fix

- **Wake from screen off on print end** - when display auto-off was active and printer left FINISH state, the screen now properly wakes up to IDLE instead of staying off until button press
- SCREEN_CLOCK remains sticky (only button or new print exits it)

## Build stats

- Flash: 89.9% (1178KB / 1310KB)
- RAM: 15.7% (51KB / 328KB)
- Board: lolin_s3_mini (ESP32-S3)
