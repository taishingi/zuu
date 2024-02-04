use crate::zuu::{
    Language, Versioning, ALREADY_INIT, GIT_DIR, GIT_HOOK, GIT_HOOK_DIR, GIT_INIT, HG_DIR, HG_HOOK,
    HG_INIT, INIT_FAILED, INIT_SUCCESSFULLY,
};
use std::env::var;
use std::fs::File;
use std::io::Write;
use std::path::Path;
use std::process::{exit, Command, ExitCode};
use std::thread::sleep;
use std::time::Duration;
use std::{fs, io};

pub fn hook(l: &Language) -> String {
    let h = var("HOME").expect("");
    let hook_dir = format!("{h}/.local/bin/hooks");

    match l {
        Language::Rust => {
            format!("{h}/{hook_dir}/rust/pre-commit")
        }
        Language::C => {
            format!("{h}/{hook_dir}/c/pre-commit")
        }
        Language::D => {
            format!("{h}/{hook_dir}/d/pre-commit")
        }
        Language::Python => {
            format!("{h}/{hook_dir}/python/pre-commit")
        }
        Language::Java => {
            format!("{h}/{hook_dir}/java/pre-commit")
        }
        Language::Php => {
            format!("{h}/{hook_dir}/php/pre-commit")
        }
        Language::Ruby => {
            format!("{h}/{hook_dir}/ruby/pre-commit")
        }
        Language::R => {
            format!("{h}/{hook_dir}/r/pre-commit")
        }
        Language::Go => {
            format!("{h}/{hook_dir}/go/pre-commit")
        }
        Language::Js => {
            format!("{h}/{hook_dir}/js/pre-commit")
        }
        Language::Haskell => {
            format!("{h}/{hook_dir}/haskell/pre-commit")
        }
        Language::Unknown => String::new(),
    }
}
pub fn get_hook(args: &[String], language: &Language) -> ExitCode {
    if has(args, 1, "init") && has(args, 2, "git") {
        if !exist(GIT_DIR) {
            println!("{GIT_INIT}");
            exit(1);
        }
        if exist(GIT_HOOK) && exist(hook(language).as_str()) {
            println!("{ALREADY_INIT}");
            exit(1);
        }
        assert!(download_hook(&Versioning::Git, language));
        println!("{INIT_SUCCESSFULLY}");
        exit(0);
    }

    if has(args, 1, "init") && has(args, 2, "hg") {
        if !exist(HG_DIR) {
            println!("{HG_INIT}");
            exit(1);
        }
        if exist(HG_HOOK) && exist(hook(language).as_str()) {
            println!("{ALREADY_INIT}");
            exit(1);
        }
        assert!(download_hook(&Versioning::Hg, language));
        println!("{INIT_SUCCESSFULLY}");
        exit(0);
    }
    println!("{INIT_FAILED}");
    exit(1);
}

pub fn watch(args: &[String], language: &Language) -> ExitCode {
    let mut b;
    loop {
        b = ok(language);
        if should_quit(args) {
            break;
        }
        wait(60);
    }
    quit(b)
}
pub fn shell(program: &str, args: Vec<&str>, d: &str) -> bool {
    Command::new(program)
        .args(args)
        .current_dir(d)
        .spawn()
        .expect(program)
        .wait()
        .expect(program)
        .success()
}
pub fn ok(language: &Language) -> bool {
    let hook = hook(language);
    if hook.is_empty() {
        return false;
    }
    shell("bash", vec![hook.as_str()], ".")
}

pub fn wait(time: i32) {
    println!(
        "\n{}",
        format_args!(
            "{}[ {}OK {}] Waiting {}{}",
            "\x1b[1;37m", "\x1b[1;32m", "\x1b[1;37m", time, "\x1b[0m"
        )
    );

    for _i in 1..time {
        print!(".");
        io::stdout().flush().unwrap();
        sleep(Duration::from_secs(1));
    }
}

pub fn exist(p: &str) -> bool {
    Path::new(p).exists()
}

pub fn touch(f: &str, d: &str, c: &str) -> bool {
    if !exist(d) {
        fs::create_dir(d).expect("failed to create the directory");
    }
    let mut f = File::create(format!("{d}/{f}").as_str()).expect("failed to create the file");
    f.write_all(c.as_bytes()).expect("failed to write data");
    f.sync_data().is_ok()
}

pub fn has(args: &[String], index: usize, argument: &str) -> bool {
    if args.len() < index {
        return args
            .get(index)
            .expect("failed to get argument")
            .eq(argument);
    }
    false
}

pub fn should_quit(args: &[String]) -> bool {
    if args.len() > 1 && has(args, 1, "watch") {
        return false;
    }
    true
}

pub fn quit(status: bool) -> ExitCode {
    if status {
        exit(0);
    }
    exit(1);
}

pub fn get_hooks() -> bool {
    let h = var("HOME").expect("");
    let hook_dir = format!("{h}/.local/bin");
    if exist(hook_dir.as_str()) {
        return shell(
            "git",
            vec!["clone", "--quiet", "https://github.com/taishingi/hooks.git"],
            hook_dir.as_str(),
        );
    }
    assert!(shell("mkdir", vec!["-p", hook_dir.as_str()], h.as_str()));
    return shell(
        "git",
        vec!["clone", "--quiet", "https://github.com/taishingi/hooks.git"],
        hook_dir.as_str(),
    );
}
pub fn download_hook(vcs: &Versioning, language: &Language) -> bool {
    let _ = get_hooks();
    let src = hook(language);
    if src.is_empty() {
        return false;
    }
    match vcs {
        Versioning::Git => {
            assert!(fs::copy(src, GIT_HOOK_DIR).is_ok());
            shell("chmod", vec!["+x", GIT_HOOK], ".")
        }
        Versioning::Hg => touch(
            "hgrc",
            HG_DIR,
            format!("[hooks]\nprecommit = {src}\n").as_str(),
        ),
    }
}
