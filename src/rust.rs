use crate::global::{get_hook, ok, watch};
use crate::zuu::{Zuu, RUST_HOOK};
use std::process::{exit, ExitCode};

pub struct Rust {
    args: Vec<String>,
}

impl Zuu for Rust {
    fn new(args: Vec<String>) -> Self {
        Self { args }
    }
    fn check(&mut self) -> ExitCode {
        if ok("rust") {
            exit(0)
        }
        exit(1)
    }

    fn init(&mut self) -> ExitCode {
        get_hook(&self.args.clone(), "rust", RUST_HOOK)
    }

    fn each(&mut self) -> ExitCode {
        watch(&self.args, "rust")
    }
}
