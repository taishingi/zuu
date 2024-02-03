use crate::global::{get_hook, ok, watch};
use crate::zuu::{Zuu, PHP_HOOK};
use std::process::{exit, ExitCode};

pub struct Php {
    args: Vec<String>,
}

impl Zuu for Php {
    fn new(args: Vec<String>) -> Self {
        Self { args }
    }
    fn check(&mut self) -> ExitCode {
        if ok("php") {
            exit(0)
        }
        exit(1)
    }

    fn init(&mut self) -> ExitCode {
        get_hook(self.args.clone(), "php", PHP_HOOK)
    }

    fn each(&mut self) -> ExitCode {
        watch(self.args.clone(), "php")
    }
}
