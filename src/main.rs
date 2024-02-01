use std::fs::{read_to_string, File};
use std::io;
use std::io::Write;
use std::path::Path;
use std::process::{exit, Command, ExitCode};
use std::thread::sleep;
use std::time::Duration;

const GIT_HOOK: &str = ".git/hooks/pre-commit";
const HG_HOOK: &str = ".hg/hgrc";
const GIT_DIR: &str = ".git";
const HG_DIR: &str = ".hg";

struct App {
    should_quit: bool,
    init: i32,
    test: (String, i32),
    clippy: (String, i32),
    check: (String, i32),
    format: (String, i32),
    audit: (String, i32),
}
impl App {
    fn new() -> Self {
        Self {
            should_quit: false,
            init: 1,
            test: (String::new(), 0),
            clippy: (String::new(), 0),
            check: (String::new(), 0),
            format: (String::new(), 0),
            audit: (String::new(), 0),
        }
    }
    fn svg(&mut self, _name: &str) -> bool {
        true
    }
    pub fn init(&mut self) -> i32 {
        if Path::new(GIT_DIR).exists() && Path::new(GIT_HOOK).exists() {
            println!("already initialized");
            self.init = 1;
            return self.init;
        }
        if Path::new(GIT_DIR).exists() && !Path::new(GIT_HOOK).exists() {
            let mut f = File::create(GIT_HOOK).expect("failed to create the file");
            f.write_all(b"#!/bin/bash\nunset GIT_DIR\nzuu\nexit $?")
                .expect("failed to write content");
            f.sync_all().expect("failed to write content");
            assert!(Command::new("chmod")
                .arg("+x")
                .arg(GIT_HOOK)
                .current_dir(".")
                .spawn()
                .expect("Failed to run chmod")
                .wait()
                .expect("")
                .success());
            println!("Project initialized successfully");
            self.init = 0;
        }
        if Path::new(HG_DIR).exists() && !Path::new(HG_HOOK).exists() {
            let mut f = File::create(HG_HOOK).expect("failed to create the hook");
            f.write_all(b"[hooks]\nprecommit = zuu").expect("");
            f.sync_data().expect("");
            println!("Project initialized");
            self.init = 0;
        }
        self.init
    }
    pub fn waiting(&mut self, time: i32) -> &mut Self {
        println!();

        for _i in 1..time {
            print!(".");
            io::stdout().flush().unwrap();
            sleep(Duration::from_secs(1));
        }
        self
    }
    pub fn test(&mut self) -> (String, i32) {
        self.test.0.clear();
        let code = Command::new("cargo")
            .arg("--quiet")
            .arg("test")
            .stdout(File::create("zuu/test.txt").expect("failed to create the file"))
            .current_dir(".")
            .output()
            .expect("")
            .status
            .code()
            .unwrap();
        self.test
            .0
            .push_str(read_to_string("zuu/test.txt").expect("failed").as_str());
        self.test.1 = code;
        self.test.clone()
    }

    pub fn check(&mut self) -> (String, i32) {
        self.check.0.clear();
        let code = Command::new("cargo")
            .arg("check")
            .stderr(File::create("zuu/check.txt").expect("failed to create the file"))
            .current_dir(".")
            .output()
            .expect("")
            .status
            .code()
            .unwrap();
        self.check
            .0
            .push_str(read_to_string("zuu/check.txt").expect("failed").as_str());
        self.check.1 = code;
        self.check.clone()
    }
    pub fn audit(&mut self) -> (String, i32) {
        self.audit.0.clear();
        let code = Command::new("cargo")
            .arg("audit")
            .stdout(File::create("zuu/audit.txt").expect("failed to create the file"))
            .current_dir(".")
            .output()
            .expect("")
            .status
            .code()
            .unwrap();
        self.audit
            .0
            .push_str(read_to_string("zuu/audit.txt").expect("failed").as_str());
        self.audit.1 = code;
        self.audit.clone()
    }
    pub fn format(&mut self) -> (String, i32) {
        let code = Command::new("cargo")
            .arg("fmt")
            .arg("--check")
            .stdout(File::create("zuu/fmt.txt").expect("failed to create the file"))
            .current_dir(".")
            .output()
            .expect("")
            .status
            .code()
            .unwrap();
        self.format
            .0
            .push_str(read_to_string("zuu/fmt.txt").expect("failed").as_str());
        self.format.1 = code;
        self.format.clone()
    }

    pub fn clippy(&mut self) -> (String, i32) {
        let code = Command::new("cargo")
            .arg("clippy")
            .arg("--")
            .arg("-F")
            .arg("keyword_idents")
            .arg("-F")
            .arg("warnings")
            .arg("-F")
            .arg("let-underscore")
            .arg("-F")
            .arg("rust-2018-compatibility")
            .arg("-F")
            .arg("rust-2018-idioms")
            .arg("-F")
            .arg("rust-2021-compatibility")
            .arg("-F")
            .arg("future-incompatible")
            .arg("-F")
            .arg("unused")
            .arg("-F")
            .arg("unused_crate_dependencies")
            .arg("-F")
            .arg("unused_extern_crates")
            .arg("-F")
            .arg("unused_macro_rules")
            .arg("-F")
            .arg("unused_results")
            .arg("-F")
            .arg("unused_qualifications")
            .arg("-F")
            .arg("nonstandard-style")
            .arg("-F")
            .arg("macro_use_extern_crate")
            .arg("-F")
            .arg("absolute_paths_not_starting_with_crate")
            .arg("-F")
            .arg("ambiguous_glob_imports")
            .arg("-F")
            .arg("clippy::all")
            .arg("-F")
            .arg("clippy::perf")
            .arg("-F")
            .arg("clippy::pedantic")
            .arg("-F")
            .arg("clippy::style")
            .arg("-F")
            .arg("clippy::suspicious")
            .arg("-F")
            .arg("clippy::correctness")
            .arg("-F")
            .arg("clippy::nursery")
            .arg("-F")
            .arg("clippy::complexity")
            .arg("-F")
            .arg("clippy::cargo")
            .stderr(File::create("zuu/clippy.txt").expect("failed to create the file"))
            .current_dir(".")
            .output()
            .unwrap()
            .status
            .code()
            .unwrap();
        self.clippy
            .0
            .push_str(read_to_string("zuu/clippy.txt").expect("failed").as_str());
        self.clippy.1 = code;
        self.clippy.clone()
    }
    pub fn quit(&mut self, quit: bool) -> &mut Self {
        self.should_quit = quit;
        self
    }

    pub fn out(&mut self, x: i32, s: &str, e: &str) -> &mut Self {
        if x.eq(&0) {
            println!(
                "\n{}",
                format_args!(
                    "{}[ {}OK {}] {}{}",
                    "\x1b[1;37m", "\x1b[1;32m", "\x1b[1;37m", s, "\x1b[0m"
                )
            );
        } else {
            println!(
                "\n{}",
                format_args!(
                    "{}[ {}KO {}] {}{}",
                    "\x1b[1;37m", "\x1b[1;31m", "\x1b[1;37m", e, "\x1b[0m"
                )
            );
        }
        self
    }
    pub fn success(&mut self) -> bool {
        self.check.1.eq(&0)
            && self.audit.1.eq(&0)
            && self.format.1.eq(&0)
            && self.clippy.1.eq(&0)
            && self.test.1.eq(&0)
    }

    pub fn all(&mut self, q: bool, wait: i32) -> bool {
        let tests = self.test();
        let clippy = self.clippy();
        let format = self.format();
        let audit = self.audit();
        let check = self.check();
        self.out(tests.1, "test", tests.0.as_str())
            .out(clippy.1, "clippy", clippy.0.as_str())
            .out(format.1, "format", format.0.as_str())
            .out(audit.1, "audit", audit.0.as_str())
            .out(check.1, "check", check.0.as_str())
            .quit(q)
            .waiting(wait)
            .success()
    }

    pub fn generate_svg(&mut self) -> bool {
        let tests = self.test();
        if tests.1.eq(&0) {
            return true;
        }
        false
    }

    fn done(&mut self, q: bool, wait: i32) -> i32 {
        let mut s;
        loop {
            s = self.all(q, wait);
            if self.should_quit {
                break;
            }
        }
        i32::from(!s)
    }
}

fn main() -> ExitCode {
    let args: Vec<String> = std::env::args().collect();
    let mut app = App::new();
    app.generate_svg();
    if args.len() == 2 && args.get(1).unwrap().eq("init") {
        exit(app.init());
    }
    if args.len() == 2 && args.get(1).unwrap().eq("watch") {
        exit(app.done(false, 60));
    }
    if args.len() == 3 {
        let time: i32 = args.get(2).unwrap().parse().unwrap();
        let q = args.get(1).unwrap().eq("watch");
        exit(app.done(q, time));
    }
    exit(app.done(true, 0));
}

#[cfg(test)]
mod test {
    use crate::App;

    #[test]
    pub fn all() {
        let mut app = App::new();
        assert_eq!(app.clippy().1, 0);
        assert_eq!(app.check().1, 0);
        assert_eq!(app.audit().1, 0);
        assert_eq!(app.format().1, 0);
    }
}
