# Zuu

A git hook test runner for rust programer.

![audit](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/audit.svg)
![check](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/check.svg)
![clippy](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/clippy.svg)
![format](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/fmt.svg)
![test](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/test.svg)

## Output

![zuu output](https://raw.githubusercontent.com/taishingi/zuu/master/zuu-6.gif)

## Installation

```sh
cargo install zuu git-graph rsbadges
```

## Archlinux install

![AUR Version](https://img.shields.io/aur/version/zuu?style=social)
![AUR Last Modified](https://img.shields.io/aur/last-modified/zuu?style=social)
![AUR Votes](https://img.shields.io/aur/votes/zuu?style=social)
![AUR Maintainer](https://img.shields.io/aur/maintainer/zuu?style=social)
![AUR License](https://img.shields.io/aur/license/zuu?style=social)

```bash
paru -S zuu
```

## Requirement

- wget
- ranger
- git
- git-graph
- lazygit
- rsbadges
- cargo-audit
- rustup

## Track repository

```bash
git init
zuu init
```

## Usage

```sh
git add .
git commit -m "commit msg"
```

## Manual usage

```bash
zuu
zuu --watch
zuu --watch 10
```

Time is in seconds

## Upgrade the hook file

```bash
zuu upgrade
```

## Display help

```bash
zuu --help
```

## Generate badges

```bash
zuu --gen-badges
```

## Structure of the project

```bash
.
├── badges
│  ├── flat
│  │  ├── audit.svg
│  │  ├── check.svg
│  │  ├── clippy.svg
│  │  ├── fmt.svg
│  │  ├── test.svg
│  │  └── verify-project.svg
│  ├── flatsquare
│  │  ├── audit.svg
│  │  ├── check.svg
│  │  ├── clippy.svg
│  │  ├── fmt.svg
│  │  ├── test.svg
│  │  └── verify-project.svg
│  ├── forthebadge
│  │  ├── audit.svg
│  │  ├── check.svg
│  │  ├── clippy.svg
│  │  ├── fmt.svg
│  │  ├── test.svg
│  │  └── verify-project.svg
│  ├── plastic
│  │  ├── audit.svg
│  │  ├── check.svg
│  │  ├── clippy.svg
│  │  ├── fmt.svg
│  │  ├── test.svg
│  │  └── verify-project.svg
│  └── social
│     ├── audit.svg
│     ├── check.svg
│     ├── clippy.svg
│     ├── fmt.svg
│     ├── test.svg
│     └── verify-project.svg
├── src
│  └── main.rs
├── zuu
│  └── git
│     └── patch
├── Cargo.toml
├── LICENSE
└── README.md
```

## Social links

[Email](mailto:micieli@vivaldi.net)

[Donate](https://www.paypal.com/donate/?hosted_button_id=D43VUM85PM724)

[Github](https://github.com/taishingi)
