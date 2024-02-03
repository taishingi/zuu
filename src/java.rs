use crate::global::{get_hook, ok, watch};
use crate::zuu::{Zuu, JAVA_HOOK};
use std::process::{exit, ExitCode};

pub struct Java {
    args: Vec<String>,
}

impl Zuu for Java {
    fn new(args: Vec<String>) -> Self {
        Self { args }
    }
    fn check(&mut self) -> ExitCode {
        if ok("java") {
            exit(0)
        }
        exit(1)
    }

    fn init(&mut self) -> ExitCode {
        get_hook(self.args.clone(), "java", JAVA_HOOK)
    }

    fn each(&mut self) -> ExitCode {
        watch(self.args.clone(), "lava")
    }
}
