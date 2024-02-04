use crate::global::{get_hook, ok, watch};
use crate::zuu::{Language, Zuu};
use std::process::{exit, ExitCode};

pub struct Java {
    args: Vec<String>,
}

impl Zuu for Java {
    fn new(args: Vec<String>) -> Self {
        Self { args }
    }
    fn check(&mut self) -> ExitCode {
        if ok(&Language::Java) {
            exit(0)
        }
        exit(1)
    }

    fn init(&mut self) -> ExitCode {
        get_hook(&self.args, &Language::Java)
    }

    fn each(&mut self) -> ExitCode {
        watch(&self.args, &Language::Java)
    }
}
