use crate::global::{get_hook, ok, watch};
use crate::zuu::{Zuu, GO_HOOK};
use std::process::{exit, ExitCode};

pub struct Go {
    args: Vec<String>,
}

impl Zuu for Go {
    fn new(args: Vec<String>) -> Self {
        Self { args }
    }
    fn check(&mut self) -> ExitCode {
        if ok("go") {
            exit(0)
        }
        exit(1)
    }

    fn init(&mut self) -> ExitCode {
        get_hook(self.args.clone(), "go", GO_HOOK)
    }

    fn each(&mut self) -> ExitCode {
        watch(self.args.clone(), "go")
    }
}
