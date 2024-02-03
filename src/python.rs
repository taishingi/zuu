use crate::global::{get_hook, ok, watch};
use crate::zuu::{Zuu, PYTHON_HOOK};
use std::process::{exit, ExitCode};

pub struct Python {
    args: Vec<String>,
}

impl Zuu for Python {
    fn new(args: Vec<String>) -> Self {
        Self { args }
    }
    fn check(&mut self) -> ExitCode {
        if ok("python") {
            exit(0)
        }
        exit(1)
    }

    fn init(&mut self) -> ExitCode {
        get_hook(self.args.clone(), "python", PYTHON_HOOK)
    }

    fn each(&mut self) -> ExitCode {
        watch(self.args.clone(), "python")
    }
}
