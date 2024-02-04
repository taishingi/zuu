use crate::zuu::{
    Versioning, ALREADY_INIT, GIT_DIR, GIT_HOOK, GIT_HOOK_DIR, GIT_INIT, HG_DIR, HG_HOOK, HG_INIT,
    INIT_SUCCESSFULLY,
};
use std::env::var;
use std::fs::File;
use std::io::Write;
use std::path::Path;
use std::process::{exit, Command, ExitCode};
use std::thread::sleep;
use std::time::Duration;
use std::{fs, io};

pub fn get_hook(args: &[String], language: &str, url: &str) -> ExitCode {
    let h = var("HOME").expect("");
    let hook_dir = format!(".local/bin/{language}/");
    let hook = format!("{h}/{hook_dir}/pre-commit");

    if has(args, 1, "init") && has(args, 2, "git") {
        if !exist(GIT_DIR) {
            println!("{GIT_INIT}");
            exit(1);
        }
        if exist(GIT_HOOK) && exist(hook.as_str()) {
            println!("{ALREADY_INIT}");
            exit(1);
        }
        assert!(download_hook(&Versioning::Git, language, url));
        println!("{INIT_SUCCESSFULLY}");
        exit(0);
    }

    if has(args, 1, "init") && has(args, 2, "hg") {
        if !exist(HG_DIR) {
            println!("{HG_INIT}");
            exit(1);
        }
        if exist(HG_HOOK) && exist(hook.as_str()) {
            println!("{ALREADY_INIT}");
            exit(1);
        }
        assert!(download_hook(&Versioning::Hg, language, url));
        println!("{INIT_SUCCESSFULLY}");
        exit(0);
    }
    println!("run -> zuu init hg || zuu init git");
    exit(1);
}

pub fn watch(args: &[String], language: &str) -> ExitCode {
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
pub fn ok(language: &str) -> bool {
    let h = var("HOME").expect("");
    let hook_dir = format!(".local/bin/zuu/{language}");
    let hook = format!("{h}/{hook_dir}/pre-commit");
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
    return Path::new(p).exists();
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
    if args.len() > index {
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

pub fn download_hook(vcs: &Versioning, language: &str, url: &str) -> bool {
    let h = var("HOME").expect("");
    let hook_dir = format!("{h}/.local/bin/zuu/{language}");
    let hook = format!("{hook_dir}/pre-commit");
    if !exist(hook.as_str()) {
        assert!(shell("mkdir", vec!["-p", hook_dir.as_str()], h.as_str()));
        assert!(shell("wget", vec!["-q", url], hook_dir.as_str()));
    }
    match vcs {
        Versioning::Git => {
            assert!(touch(
                "pre-commit",
                GIT_HOOK_DIR,
                format!("#!/bin/bash\n source {hook}\nexit $?\n").as_str()
            ));
            shell("chmod", vec!["+x", GIT_HOOK], ".")
        }
        Versioning::Hg => touch(
            "hgrc",
            HG_DIR,
            format!("[hooks]\nprecommit = {hook}\n").as_str(),
        ),
    }
}
