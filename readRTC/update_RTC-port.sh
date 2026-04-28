#!/bin/bash

C_FILE="$1"

if [ -z "$C_FILE" ]; then
    echo "Usage: ./update_rtc_macros.sh <file.c>"
    exit 1
fi

# ── Get RTC port range from /proc/ioports ─────────────
rtc_range=$(sudo cat /proc/ioports | grep -i rtc | awk '{print $1}')

if [ -z "$rtc_range" ]; then
    echo "❌ RTC ports not found in /proc/ioports"
    exit 1
fi

echo "📍 Found RTC range: $rtc_range"

# ── Parse addr and data port ───────────────────────────
# Format: "0070-0071"
addr_port="0x$(echo "$rtc_range" | cut -d'-' -f1)"
data_port="0x$(echo "$rtc_range" | cut -d'-' -f2)"

echo "📌 addr_port = $addr_port"
echo "📌 data_port = $data_port"

# ── Update macros in C file ────────────────────────────
if [ ! -f "$C_FILE" ]; then
    echo "❌ File not found: $C_FILE"
    exit 1
fi

# Replace macro values using sed
sed -i "s|#define RTC_addr_port.*|#define RTC_addr_port \t$addr_port|" "$C_FILE"
sed -i "s|#define RTC_data_port.*|#define RTC_data_port\t$data_port|" "$C_FILE"

echo "✅ Updated macros in: $C_FILE"