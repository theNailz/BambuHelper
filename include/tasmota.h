#pragma once

void  tasmotaInit();
void  tasmotaLoop(unsigned long now);
float tasmotaGetWatts();          // current watts, -1 if unavailable
bool  tasmotaIsOnline();          // true if data received within last 90s
void  tasmotaMarkPrintStart();    // call when print begins; records Total kWh baseline
float tasmotaGetPrintKwhUsed();   // kWh used since markPrintStart(), -1 if unavailable
bool  tasmotaKwhChanged();        // true (once) when kWh value has updated
