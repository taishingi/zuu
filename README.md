<h1>What it's ?</h1> 

<img alt="logo" src="https://raw.githubusercontent.com/taishingi/zuu/master/img/avatar.png" title="zuu" align="right" width="250"/>

Zuu will perform certain code tests at the time of the commit. 

If the tests fail, you will not be able to validate your modifications until all the checks are successful.

If all controls are successful, a git program will be automatically executed to validate your change, if the controls have failures, ranger is executed in the zuu directory to see all failures.

You can also run the tests yourself to find out if everything is working properly.

Watch mode is available.

You can also generate badges for all checkup in different styles.

[![zuu](https://github.com/taishingi/zuu/actions/workflows/rust.yml/badge.svg)](https://github.com/taishingi/zuu/actions/workflows/rust.yml)
[![continuous](https://github.com/taishingi/zuu/actions/workflows/continuous.yml/badge.svg)](https://github.com/taishingi/zuu/actions/workflows/continuous.yml)

![audit](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/audit.svg)
![check](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/check.svg)
![clippy](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/clippy.svg)
![format](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/fmt.svg)
![test](https://raw.githubusercontent.com/taishingi/zuu/master/badges/social/test.svg)

![Version](https://img.shields.io/crates/v/zuu?style=social)
![Download](https://img.shields.io/crates/d/zuu?style=social)

## Installation

```sh
cargo install zuu rsbadges
```

## Archlinux install

![Aur version](https://img.shields.io/aur/version/zuu?style=social "Aur version")
![Aur last modified](https://img.shields.io/aur/last-modified/zuu?style=social "Aur last modified")
![Aur votes](https://img.shields.io/aur/votes/zuu?style=social "Aur votes")
![Aur maintainer](https://img.shields.io/aur/maintainer/zuu?style=social "Aur maintainer")
![Aur license](https://img.shields.io/aur/license/zuu?style=social "Aur license")

```bash
paru -S zuu
```

## Using docker compose

```yaml
version: '3'
services:
  zuu:
    environment:
      TERM: xterm-color
    image: taishingi/zuu:latest
    volumes:
      - .:/app
```

### Run tests

```bash
docker-compose up
```

### Kill tests container

```bash
docker-compose down
```

## GitHub workflow

```yaml
name: zuu
on:
  push:
    branches: [ "master" , "develop" ]
  pull_request:
    branches: [ "master" , "develop"  ]
env:
  CARGO_TERM_COLOR: always
  TERM: xterm-256color
jobs:
  zuu:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v3
    - name: deps
      run: sudo apt-get install -y wget && wget https://raw.githubusercontent.com/taishingi/zuu/master/pre-commit
    - name: zuu
      run: bash pre-commit
```



## Requirement

- wget
- git
- rsbadges
- cargo-audit
- rustup
- docker-compose
- docker
- ncurses

## Support versioning

- Git
- Mercurial

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
zuu watch
zuu watch 10
```

Time is in seconds

## Upgrade the hook file

```bash
zuu update
```

## Display help

```bash
zuu help
```

## Generate badges

```bash
zuu badges
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