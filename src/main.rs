use std::{
    env::args,
    path::Path,
    process::{exit, Command, ExitCode},
};

const HOOK: &str = ".git/hooks/pre-commit";
const HOOK_DIR: &str = ".git/hooks/";

fn main() -> ExitCode {
    if args().count() == 1 && !Path::new(HOOK).exists() {
        println!("Run -> zuu init");
        exit(1);
    } else if args().count() == 2 {
        if Path::new(HOOK).exists() {
            println!("Project already initialized");
            exit(0);
        }
        let args: Vec<String> = args().collect();
        let init = args.get(1).expect("msg");
        if init.eq(&"init") {
            assert!(Command::new("wget")
                .arg("-q")
                .arg("https://raw.githubusercontent.com/taishingi/zuu/develop/pre-commit")
                .current_dir(HOOK_DIR)
                .spawn()
                .expect("Failed to get hook file")
                .wait()
                .expect("msg")
                .success());

            assert!(Command::new("chmod")
                .arg("+x")
                .arg(HOOK)
                .current_dir(".")
                .spawn()
                .expect("Failed to run chmod")
                .wait()
                .expect("")
                .success());
            println!("Project initialized successfully");
            exit(0);
        } else {
            println!("nad");
        }
    }
    println!("git commit   : Run tests");
    println!("zuu init     : Init a repository");

    exit(1);
}
