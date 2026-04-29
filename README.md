# 📦 Project Name

> Linux user apps

---

## 📚 Table of Contents

- [📦 Project Name](#-project-name)
  - [📚 Table of Contents](#-table-of-contents)
  - [📝 About](#-about)
  - [✨ Features](#-features)
  - [🚀 Getting Started](#-getting-started)
    - [Prerequisites](#prerequisites)
    - [Source](#source)
    - [Usage](#usage)
    - [Reference](#reference)

---

## 📝 About

> Some apps run in user-space to interact with hardware

---

## ✨ Features

- ✅ read RTC by /dev/port OR I/O ports OR /dev/rtc0
- ✅ read random number from /dev/urandom
- ✅ query MAC address of network interface

---

## 🚀 Getting Started

### Prerequisites

- List software dependencies or system requirements here:
  - Ubuntu
  - Linux C

### Source

- *.c: main app
- *.sh: script

### Usage

[Optional] Setup git hooks
- chmod +x setup-hooks.sh .githooks/prepare-commit-msg
- ./setup-hooks.sh

[Common] Compile source:
- make

[Common] Clean source:
- make clean

[Common] Run test:
- ./out

RTC:
- timedatectl -> check time zone of system
- ./update_RTC-port.sh *.c
- sudo ./out*

network:
- ifconfig -> to check network interface (e.g. *ens33*)
- ./out ens33

### Reference

- https://vimentor.com/vi/lesson/truy-cap-du-lieu-tren-io-module
- https://www.scs.stanford.edu/23wi-cs212/pintos/specs/mc146818a.pdf
- https://man7.org/linux/man-pages/man4/rtc.4.html
- https://man7.org/linux/man-pages/man7/netdevice.7.html