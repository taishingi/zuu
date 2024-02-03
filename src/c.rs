use crate::global::{get_hook, ok, watch};
use crate::zuu::{Zuu, C_HOOK};
use std::process::{exit, ExitCode};

pub struct C {
    args: Vec<String>,
}

impl Zuu for C {
    fn new(args: Vec<String>) -> Self {
        Self { args }
    }
    fn check(&mut self) -> ExitCode {
        if ok("c") {
            exit(0)
        }
        exit(1)
    }

    fn init(&mut self) -> ExitCode {
        get_hook(self.args.clone(), "c", C_HOOK)
    }

    fn each(&mut self) -> ExitCode {
        watch(self.args.clone(), "c")
    }
}
