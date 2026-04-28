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

- ✅ read RTC using system call ioperm / iopl OR through /dev/port

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
- gcc *.c -o out

[Common] Run test:
- ./out

readRTC:
- ./update_RTC-port.sh readRTC_by_dev-port.c
- make
- sudo .out/


### Reference

- https://vimentor.com/vi/lesson/truy-cap-du-lieu-tren-io-module 