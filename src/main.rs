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
const HOOK: &str = ".git/hooks/pre-commit";
const HOOK_DIR: &str = ".git/hooks/";

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

fn waiting(time: i32) {
    println!(
        "{}",
        format_args!(
            "{}[ {}OK {}] Waiting {}s{}\n",
            "\x1b[1;37m", "\x1b[1;32m", "\x1b[1;37m", time, "\x1b[0m"
        )
    );
    for _i in 1..time {
        print!(".");
        io::stdout().flush().unwrap();
        sleep(Duration::from_secs(1));
    }
}
fn git_tools(time: i32) {
    waiting(time);
    assert!(Command::new("lazygit")
        .current_dir(".")
        .spawn()
        .expect("msg")
        .wait()
        .expect("msg")
        .success());
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

fn gen_badges() -> i32 {
    if Path::new(HOOK).exists()
        && Command::new("bash")
            .arg(HOOK)
            .arg("--gen-badges")
            .spawn()
            .expect("msg")
            .wait()
            .expect("msg")
            .success()
    {
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
                git_tools(converted_time);
            } else {
                println!(
                    "\n{}",
                    format_args!(
                        "{}[ {}OK {}] Waiting {}s{}\n",
                        "\x1b[1;37m", "\x1b[1;32m", "\x1b[1;37m", time, "\x1b[0m"
                    )
                );
                waiting(converted_time);
            }
        }
    } else {
        loop {
            let code = run();

            if code {
                git_tools(60);
            } else {
                println!(
                    "\n{}",
                    format_args!(
                        "{}[ {}OK {}] Waiting {}s{}",
                        "\x1b[1;37m", "\x1b[1;32m", "\x1b[1;37m", "60", "\x1b[0m"
                    )
                );
                waiting(60);
            }
        }
    }
}

fn main() -> ExitCode {
    let args: Vec<String> = args().collect();
    if args.len() == 1 && Path::new(HOOK).exists() {
        if run() {
            git_tools(10);
            exit(0);
        }
        exit(1);
    }

    if args.len() == 2 && args.get(1).expect("Fail to get the argument").eq(&"init") {
        exit(init());
    }

    if args.len() == 2
        && args
            .get(1)
            .expect("Fail to get the argument")
            .eq(&"--gen-badges")
    {
        if gen_badges().eq(&0) {
            git_tools(10);
            exit(0);
        }
        exit(1);
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
