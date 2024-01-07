use std::{
    env::args,
    fs,
    path::Path,
    process::{exit, Command, ExitCode},
    thread::sleep,
    time::Duration,
};

const HOOK: &str = ".git/hooks/pre-commit";
const HOOK_DIR: &str = ".git/hooks/";

fn help() -> i32 {
    println!("zuu                   : Run test cases");
    println!("zuu upgrade           : Upgrade the hook script");
    println!("zuu init              : Init the repository");
    println!("zuu --help            : Display help");
    println!("zuu --watch           : Run hook script in watch mode");
    println!("zuu --watch <time>    : Run hook script in watch mode with the expected time");
    0
}

fn upgrade() -> i32 {
    if Path::new(HOOK).exists() {
        fs::remove_file(HOOK).expect("Failed to remove hook");
        return init();
    }
    1
}
fn init() -> i32 {
    if Path::new(HOOK).exists() {
        println!("The project is already initialized");
        return 0;
    }
    assert!(Command::new("wget")
        .arg("-q")
        .arg("https://raw.githubusercontent.com/taishingi/zuu/master/pre-commit")
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
    0
}
fn run() -> bool {
    if Path::new(HOOK).exists() {
        return Command::new("bash")
            .arg(HOOK)
            .spawn()
            .expect("msg")
            .wait()
            .expect("msg")
            .success();
    }
    false
}
fn watch(args: &[String]) {
    if args.len() == 3 {
        let time = args
            .get(2)
            .expect("Fail to get the sleep time argument")
            .to_string();
        let converted_time: u64 = time.parse().expect("Fail to parse");
        loop {
            println!(
                "{}",
                format_args!(
                    "{}[ {}OK {}] Starting {}{}\n",
                    "\x1b[1;37m", "\x1b[1;32m", "\x1b[1;37m", HOOK, "\x1b[0m"
                )
            );
            sleep(Duration::from_secs(1));
            let _ = run();
            println!(
                "{}",
                format_args!(
                    "{}[ {}OK {}] Waiting {}s{}\n",
                    "\x1b[1;37m", "\x1b[1;32m", "\x1b[1;37m", time, "\x1b[0m"
                )
            );
            sleep(Duration::from_secs(converted_time));
        }
    } else {
        loop {
            println!(
                "{}",
                format_args!(
                    "{}[ {}OK {}] Starting {}{}\n",
                    "\x1b[1;37m", "\x1b[1;32m", "\x1b[1;37m", HOOK, "\x1b[0m"
                )
            );
            sleep(Duration::from_secs(1));
            let _ = run();
            println!(
                "{}",
                format_args!(
                    "{}[ {}OK {}] Waiting {}s{}\n",
                    "\x1b[1;37m", "\x1b[1;32m", "\x1b[1;37m", "60", "\x1b[0m"
                )
            );
            sleep(Duration::from_secs(60));
        }
    }
}

fn main() -> ExitCode {
    let args: Vec<String> = args().collect();
    if args.len() == 1 && Path::new(HOOK).exists() {
        if run() {
            exit(0);
        }
        exit(1);
    }

    if args.len() == 2 && args.get(1).expect("Fail to get the argument").eq(&"init") {
        exit(init());
    }

    if !Path::new(HOOK).exists() {
        println!("run -> zuu init");
        exit(1);
    }

    if args.get(1).expect("failed to get argument").eq(&"upgrade") {
        exit(upgrade());
    }
    if args.get(1).expect("failed to get argument").eq(&"--help") {
        exit(help());
    }
    if args
        .get(1)
        .expect("Fail to get the argument")
        .eq(&"--watch")
    {
        watch(&args);
    }
    exit(help());
}
