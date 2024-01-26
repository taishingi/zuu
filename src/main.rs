use std::io;
use std::io::Write;
use std::{
    env::args,
    fs,
    path::Path,
    process::{exit, Command, ExitCode},
    thread::sleep,
    time::Duration,
};

const GIT_HOOK: &str = ".git/hooks/pre-commit";
const HG_HOOK: &str = ".hg/hgrc";
const GIT_DIR: &str = ".git";
const GIT_HOOK_DIR: &str = ".git/hooks/";
const HG_DIR: &str = ".hg";

fn help() -> i32 {
    println!("zuu                   : Run test cases");
    println!("zuu upgrade           : Upgrade the hook script");
    println!("zuu init              : Init the repository");
    println!("zuu --gen-badges      : Run test cases and generate badges");
    println!("zuu --help            : Display help");
    println!("zuu --watch           : Run hook script in watch mode");
    println!("zuu --watch <time>    : Run hook script in watch mode with the expected time");
    0
}

fn upgrade() -> i32 {
    if Path::new(GIT_DIR).exists() {
        fs::remove_file(GIT_HOOK).expect("Failed to remove hook");
        return init();
    }
    if Path::new(HG_DIR).exists() {
        fs::remove_file(HG_HOOK).expect("failed to remove the hook");
        return init();
    }
    println!("run -> zuu init");
    1
}
fn init() -> i32 {
    if Path::new(GIT_DIR).exists() {
        assert!(
            Command::new("wget")
                .arg("-q")
                .arg("https://raw.githubusercontent.com/taishingi/zuu/master/pre-commit")
                .current_dir(GIT_HOOK_DIR)
                .spawn()
                .expect("Failed to get hook file")
                .wait()
                .expect("msg")
                .success(),
            "The git directory has been not founded"
        );

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
        return 0;
    }
    if Path::new(HG_DIR).exists() {
        assert!(
            Command::new("wget")
                .arg("-q")
                .arg("https://raw.githubusercontent.com/taishingi/zuu/master/hgrc")
                .current_dir(HG_DIR)
                .spawn()
                .expect("Failed to get hook file")
                .wait()
                .expect("msg")
                .success(),
            "The hg directory has been not founded"
        );
        println!("Project initialized successfully");
        return 0;
    }
    0
}

fn waiting(time: i32) {
    for _i in 1..time {
        print!(".");
        io::stdout().flush().unwrap();
        sleep(Duration::from_secs(1));
    }
    println!();
}
fn run() -> bool {
    if Path::new(GIT_HOOK).exists() {
        return Command::new("bash")
            .arg(GIT_HOOK)
            .current_dir(".")
            .spawn()
            .expect("Failed to run the hook")
            .wait()
            .expect("msg")
            .success();
    }
    if Path::new(HG_HOOK).exists() {
        return Command::new("pre-commit")
            .current_dir(".")
            .spawn()
            .expect("Failed to run the hook")
            .wait()
            .expect("msg")
            .success();
    }
    println!("run -> zuu init");
    false
}

fn gen_badges() -> i32 {
    if Path::new(GIT_HOOK).exists()
        && Command::new("bash")
            .arg(GIT_HOOK)
            .arg("--gen-badges")
            .spawn()
            .expect("msg")
            .wait()
            .expect("msg")
            .success()
    {
        return 0;
    }
    if Path::new(HG_HOOK).exists() {
        assert!(Command::new("pre-commit")
            .arg("--gen-badges")
            .current_dir(".")
            .spawn()
            .expect("failed")
            .wait()
            .expect("")
            .success());
        return 0;
    }
    1
}

fn watch(args: &[String]) {
    if args.len() == 3 {
        let time = args
            .get(2)
            .expect("Fail to get the sleep time argument")
            .to_string();
        let converted_time: i32 = time.parse().expect("Fail to parse");
        loop {
            let code = run();

            if code {
                println!(
                    "\n{}",
                    format_args!(
                        "{}[ {}OK {}] Waiting {}s{}\n",
                        "\x1b[1;37m", "\x1b[1;32m", "\x1b[1;37m", time, "\x1b[0m"
                    )
                );
            } else {
                println!(
                    "\n{}",
                    format_args!(
                        "{}[ {}KO {}] Waiting {}s{}\n",
                        "\x1b[1;37m", "\x1b[1;31m", "\x1b[1;37m", time, "\x1b[0m"
                    )
                );
            }
            waiting(converted_time);
        }
    } else {
        loop {
            let code = run();

            if code {
                println!(
                    "\n{}",
                    format_args!(
                        "{}[ {}OK {}] Waiting {}s{}",
                        "\x1b[1;37m", "\x1b[1;32m", "\x1b[1;37m", "60", "\x1b[0m"
                    )
                );
            } else {
                println!(
                    "\n{}",
                    format_args!(
                        "{}[ {}KO {}] Waiting {}s{}",
                        "\x1b[1;37m", "\x1b[1;31m", "\x1b[1;37m", "60", "\x1b[0m"
                    )
                );
            }
            waiting(60);
        }
    }
}

fn main() -> ExitCode {
    let args: Vec<String> = args().collect();
    if args.len() == 1 {
        if run() {
            exit(0);
        }
        exit(1);
    }

    if args.len() == 2 && args.get(1).expect("Fail to get the argument").eq("init") {
        exit(init());
    }

    if Path::new(GIT_DIR).exists() && !Path::new(GIT_HOOK).exists() {
        println!("run -> zuu init");
        exit(1);
    }
    if Path::new(HG_DIR).exists() && !Path::new(HG_HOOK).exists() {
        println!("run -> zuu init");
        exit(1);
    }

    if args.len() == 2
        && args
            .get(1)
            .expect("Fail to get the argument")
            .eq("--gen-badges")
    {
        if gen_badges().eq(&0) {
            exit(0);
        }
        exit(1);
    }

    if args.get(1).expect("failed to get argument").eq("upgrade") {
        exit(upgrade());
    }
    if args.get(1).expect("failed to get argument").eq("--help") {
        exit(help());
    }
    if args.get(1).expect("Fail to get the argument").eq("--watch") {
        watch(&args);
    }
    exit(help());
}
