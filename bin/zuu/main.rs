use rsbadges::{Badge, Style};
use std::env::current_dir;
use std::fs::{self, File};
use std::io::Write;
use std::path::Path;
use std::process::{exit, Command, ExitCode};

const HOOK: &str = "./.git/hooks/pre-commit";

fn create_badges() -> bool {
    if !Path::new("badges").is_dir() {
        fs::create_dir("badges").expect("failed to create badges directory");
        return true;
    }
    true
}

fn hook_exists() -> bool {
    Path::new(HOOK).is_file()
}

fn create_hook() -> bool {
    if hook_exists() {
        println!(
            "Project already initialised at {:?}",
            current_dir().expect("failed to get current dir")
        );
        return true;
    }
    let mut x = File::create(HOOK).unwrap_or_else(|_| panic!("Failed to create the {} file", HOOK));
    x.write_all("#!/bin/bash\n\nzuu\n\nexit $?\n".as_bytes())
        .unwrap_or_else(|_| panic!("Failed to create the {} file", HOOK));
    Command::new("chmod")
        .arg("+x")
        .arg(HOOK)
        .spawn()
        .expect("failed to init git hook")
        .wait()
        .expect("")
        .success()
}

fn cargo() -> bool {
    Path::new("./Cargo.toml").is_file()
}
fn check() -> bool {
    create_badges();
    if cargo() {
        assert!(badge("verify", done("cargo", "verify-project")));
        assert!(badge("build", done("cargo", "build")));
        assert!(badge("clippy", done("cargo", "clippy")));
        assert!(badge("check", done("cargo", "check")));
        assert!(badge("benchmark", done("cargo", "bench")));
        assert!(badge("format", done("cargo", "fmt")));
        assert!(badge("documentation", done("cargo", "doc")));
        assert!(badge("tests", done("cargo", "test")));
        assert!(badge("tree", done("cargo", "tree")));
        return true;
    }
    println!("use zuu init [ bin | lib ] first");
    exit(1);
}

fn create(bin: bool, name: &str) -> bool {
    if bin {
        Command::new("cargo")
            .arg("init")
            .arg("--bin")
            .arg("--vcs")
            .arg("git")
            .arg(name)
            .current_dir(".")
            .spawn()
            .expect("failed to init the binary")
            .wait()
            .expect("msg")
            .success()
    } else {
        Command::new("cargo")
            .arg("init")
            .arg("--lib")
            .arg("--vcs")
            .arg("git")
            .arg(name)
            .current_dir(".")
            .spawn()
            .expect("failed to init the library")
            .wait()
            .expect("msg")
            .success()
    }
}

fn badge(name: &str, success: bool) -> bool {
    if success {
        let badge = Badge {
            label_text: name.to_string(),
            msg_link: "".to_string(),
            logo: "https://simpleicons.org/icons/rust.svg".to_string(),
            embed_logo: true,
            badge_link: "".to_string(),
            badge_title: format!("{} status", name).to_string(),
            label_title: "status".to_string(),
            label_link: "".to_string(),
            msg_text: "success".to_string(),
            msg_title: "build status".to_string(),
            label_color: "grey".to_string(),
            msg_color: "green".to_string(),
        };
        let badge_style = Style::FlatSquare(badge);
        let badge_svg = badge_style.generate_svg().unwrap();
        rsbadges::save_svg(format!("{}/{}.svg", "badges", name).as_str(), &badge_svg).expect("");
        Path::new(format!("{}/{}.svg", "badges", name).as_str()).is_file()
    } else {
        let badge = Badge {
            label_text: name.to_string(),
            msg_link: "".to_string(),
            logo: "https://simpleicons.org/icons/rust.svg".to_string(),
            embed_logo: true,
            badge_link: "".to_string(),
            badge_title: format!("{} status", name).to_string(),
            label_title: "status".to_string(),
            label_link: "".to_string(),
            msg_text: "failure".to_string(),
            msg_title: format!("{} status", name).to_string(),
            label_color: "grey".to_string(),
            msg_color: "red".to_string(),
        };
        let badge_style = Style::FlatSquare(badge);
        let badge_svg = badge_style.generate_svg().unwrap();
        rsbadges::save_svg(format!("{}/{}.svg", "badges", name).as_str(), &badge_svg).expect("");
        Path::new(format!("{}/{}.svg", "badges", name).as_str()).is_file()
    }
}

fn done(program: &str, arg: &str) -> bool {
    Command::new(program)
        .arg(arg)
        .current_dir(".")
        .spawn()
        .expect("")
        .wait()
        .expect("")
        .success()
}

fn main() -> ExitCode {
    let args: Vec<String> = std::env::args().collect();

    let want_run: bool = args.len() == 1;

    let want_help: bool =
        args.len() == 2 && args.get(1).expect("Failed to get argument").eq("help");
    let want_init: bool = args.len() == 3 && args.get(1).expect("failed to get init").eq("init");

    let want_hook: bool = args.len() == 2 && args.get(1).expect("Failed to get index").eq("init");

    if want_run {
        assert!(check());
        exit(0);
    }

    if want_help {
        exit(help(true));
    }

    if want_hook {
        assert!(create_hook());
        exit(0);
    }

    if want_init {
        let arg: &String = args.get(1).expect("Failed to get argument");
        let t: &String = args.get(2).expect("Failed to get the type argument");
        let init: bool = cargo();

        match init {
            true => exit(0),
            false => {
                if t.eq("bin") && arg.eq("init") && !init || t.eq("lib") && arg.eq("init") && !init
                {
                    assert!(create_badges());
                    assert!(create(t.eq("bin"), "."));
                    assert!(create_hook());
                }
                exit(0);
            }
        }
    }

    exit(help(false));
}

fn help(h: bool) -> i32 {
    println!("zuu init [ bin | lib ]        : Initialize a new repository");
    println!("zuu help                      : Display this help");
    println!("zuu                           : Run test in a initialized repository");
    match h {
        true => 0,
        false => 1,
    }
}
