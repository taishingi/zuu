use crate::global::{get_hook, ok, watch};
use crate::zuu::{Zuu, R_HOOK};
use std::process::{exit, ExitCode};

pub struct R {
    args: Vec<String>,
}

impl Zuu for R {
    fn new(args: Vec<String>) -> Self {
        Self { args }
    }
    fn check(&mut self) -> ExitCode {
        if ok("r") {
            exit(0)
        }
        exit(1)
    }

    fn init(&mut self) -> ExitCode {
        get_hook(&self.args, "r", R_HOOK)
    }

    fn each(&mut self) -> ExitCode {
        watch(&self.args, "r")
    }
}
