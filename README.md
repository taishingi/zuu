# What it's ?

<img src="https://raw.githubusercontent.com/taishingi/zuu/master/img/logo.png" alt="logo" align="right" width="250"/>

Zuu will perform certain code tests at the time of the commit. if the tests fail, you will not be able to validate your modifications until all the checks are successful.

If all controls are successful, a git program will be automatically executed to validate your change, if the controls have failures, ranger is executed in the zuu directory to see all failures.

You can also run the tests yourself to find out if everything is working properly.

Watch mode is available.

You can also generate badges for all checkup in different styles.

![audit](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/audit.svg)
![check](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/check.svg)
![clippy](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/clippy.svg)
![format](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/fmt.svg)
![test](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/test.svg)

![Version](https://img.shields.io/crates/v/zuu?style=social)
![Download](https://img.shields.io/crates/d/zuu?style=social)

## Output

<img src="https://raw.githubusercontent.com/taishingi/zuu/master/zuu-6.gif" width="100%" alt="demo">

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
