use crate::global::{get_hook, ok, watch};
use crate::zuu::{Zuu, JS_HOOK};
use std::process::{exit, ExitCode};

pub struct Js {
    args: Vec<String>,
}

impl Zuu for Js {
    fn new(args: Vec<String>) -> Self {
        Self { args }
    }
    fn check(&mut self) -> ExitCode {
        if ok("js") {
            exit(0)
        }
        exit(1)
    }

    fn init(&mut self) -> ExitCode {
        get_hook(self.args.clone(), "js", JS_HOOK)
    }

    fn each(&mut self) -> ExitCode {
        watch(self.args.clone(), "js")
    }
}
