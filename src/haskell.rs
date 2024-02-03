use crate::global::{get_hook, ok, watch};
use crate::zuu::{Zuu, HASKELL_HOOK};
use std::process::{exit, ExitCode};

pub struct Haskell {
    args: Vec<String>,
}

impl Zuu for Haskell {
    fn new(args: Vec<String>) -> Self {
        Self { args }
    }
    fn check(&mut self) -> ExitCode {
        if ok("haskell") {
            exit(0)
        }
        exit(1)
    }

    fn init(&mut self) -> ExitCode {
        get_hook(self.args.clone(), "haskell", HASKELL_HOOK)
    }

    fn each(&mut self) -> ExitCode {
        watch(self.args.clone(), "haskell")
    }
}
