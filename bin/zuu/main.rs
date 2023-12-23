use rsbadges::{Badge, Style};
use std::env::current_dir;
use std::fs::{self, File};
use std::io::Write;
use std::path::Path;
use std::process::{exit, Command};

fn badge(name: &str, success: bool) {
    if !Path::new("badges").is_dir() {
        fs::create_dir("badges").expect("failed to create badges directory");
    }
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
        assert!(std::path::Path::new(format!("{}/{}.svg", "badges", name).as_str()).is_file());
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
        assert!(std::path::Path::new(format!("{}/{}.svg", "badges", name).as_str()).is_file());
    }
}

fn done(program: &str, arg: &str) -> bool {
    let b = Command::new(program)
        .arg(arg)
        .current_dir(".")
        .spawn()
        .expect("")
        .wait()
        .expect("")
        .success();
    if b {
        return true;
    }
    exit(1);
}

fn main() {
    let args: Vec<String> = std::env::args().collect();

    if args.len() == 1 {
        badge("verify", done("cargo", "verify-project"));
        badge("build", done("cargo", "build"));
        badge("clippy", done("cargo", "clippy"));
        badge("check", done("cargo", "check"));
        badge("benchmark", done("cargo", "bench"));
        badge("format", done("cargo", "fmt"));
        badge("documentation", done("cargo", "doc"));
        badge("tests", done("cargo", "test"));
        badge("tree", done("cargo", "tree"));
        exit(0);
    } else {
        let arg: &String = args.get(1).expect("failed to get argument");
        if arg.eq("init") {
            let name = ".git/hooks/pre-commit";

            if !Path::new(".git").is_dir() {
                assert!(Command::new("git")
                    .arg("init")
                    .current_dir(".")
                    .spawn()
                    .expect("Failed to find git")
                    .wait()
                    .expect("msg")
                    .success());
            }
            
            if Path::new(name).is_file() {
                println!(
                    "Project already initialised at {:?}",
                    current_dir().expect("failed to get current dir")
                );
                exit(0);
            } else {
                let mut x = File::create(name)
                    .unwrap_or_else(|_| panic!("Failed to create the {} file", name));
                x.write_all("#!/bin/bash\n\nzuu\n\nexit $?\n".as_bytes())
                    .unwrap_or_else(|_| panic!("Failed to create the {} file", name));
            }
            assert!(Command::new("chmod")
                .arg("+x")
                .arg(".git/hooks/pre-commit")
                .spawn()
                .expect("failed to init git hook")
                .wait()
                .expect("")
                .success());
            println!(
                "Project initialised at {:?}",
                current_dir().expect("failed to get current dir")
            );
            exit(0);
        } else {
            help();
        }
    }
}

fn help() {
    println!("zuu init : Initialize a new repository");
    println!("zuu      : Run test in a initialized repository");
    exit(0);
}
