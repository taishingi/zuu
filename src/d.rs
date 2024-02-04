use crate::global::{get_hook, ok, watch};
use crate::zuu::{Zuu, D_HOOK};
use std::process::{exit, ExitCode};

pub struct D {
    args: Vec<String>,
}

impl Zuu for D {
    fn new(args: Vec<String>) -> Self {
        Self { args }
    }
    fn check(&mut self) -> ExitCode {
        if ok("d") {
            exit(0)
        }
        exit(1)
    }

    fn init(&mut self) -> ExitCode {
        get_hook(&self.args, "d", D_HOOK)
    }

    fn each(&mut self) -> ExitCode {
        watch(&self.args, "d")
    }
}
