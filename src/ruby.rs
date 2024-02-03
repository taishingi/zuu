use crate::global::{get_hook, ok, watch};
use crate::zuu::{Zuu, RUBY_HOOK};
use std::process::{exit, ExitCode};

pub struct Ruby {
    args: Vec<String>,
}

impl Zuu for Ruby {
    fn new(args: Vec<String>) -> Self {
        Self { args }
    }
    fn check(&mut self) -> ExitCode {
        if ok("ruby") {
            exit(0)
        }
        exit(1)
    }

    fn init(&mut self) -> ExitCode {
        get_hook(self.args.clone(), "ruby", RUBY_HOOK)
    }

    fn each(&mut self) -> ExitCode {
        watch(self.args.clone(), "ruby")
    }
}
