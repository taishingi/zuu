use std::{env::args, fs, process::Command};

const HOOK: &str = ".git/hooks/pre-commit";

fn main() {
    if args().count() == 1 {
        Command::new("bash")
            .arg(HOOK)
            .spawn()
            .expect("failed to run hook");
    } else if args().count() == 2 {
        let args: Vec<String> = args().collect();
        let init = args.get(1).expect("msg");
        if init.eq(&"init") {
            Command::new("wget")
                .arg("https://raw.githubusercontent.com/taishingi/zuu/develop/pre-commit")
                .current_dir("/tmp")
                .spawn()
                .expect("failed to get hook file");
            fs::copy("/tmp/pre-commit", HOOK).expect("Fail to copy the hook file");
            fs::remove_file("/tmp/pre-commit").expect("fail to remove hook file");
            Command::new("chmod")
                .arg("+x")
                .arg(HOOK)
                .current_dir(".")
                .spawn()
                .expect("failed to run chmod");
        } else {
            println!("nad");
        }
    }
}

#[cfg(test)]
mod test {
    use std::process::Command;
    #[test]
    fn init() {
        assert!(Command::new("cargo")
            .arg("run")
            .arg("--bin")
            .arg("zuu")
            .arg("init")
            .current_dir(".")
            .spawn()
            .expect("msg")
            .wait()
            .expect("msg")
            .success());
    }
    #[test]
    fn all() {
        assert!(Command::new("cargo")
            .arg("run")
            .current_dir(".")
            .spawn()
            .expect("msg")
            .wait()
            .expect("msg")
            .success());
    }
}
