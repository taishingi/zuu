mod c;
mod d;
mod global;
mod go;
mod haskell;
mod java;
mod js;
mod php;
mod python;
mod r;
mod ruby;
mod rust;
mod zuu;

use crate::c::C;
use crate::d::D;
use crate::go::Go;
use crate::haskell::Haskell;
use crate::java::Java;
use crate::js::Js;
use crate::php::Php;
use crate::python::Python;
use crate::r::R;
use crate::ruby::Ruby;
use crate::rust::Rust;
use crate::zuu::{
    Application, Language, Zuu, C_PROJECT, D_PROJECT, GO_PROJECT, HASKELL_PROJECT, JAVA_PROJECT,
    JS_PROJECT, PHP_PROJECT, PYTHON_PROJECT, RUBY_PROJECT, RUST_PROJECT, R_PROJECT,
};
use std::path::Path;
use std::process::{exit, ExitCode};

struct App {
    args: Vec<String>,
}
impl Application for App {
    fn new(args: &[String]) -> Self {
        Self {
            args: Vec::from(args),
        }
    }

    fn detect(&mut self) -> Language {
        if self.exist(RUST_PROJECT) {
            return Language::Rust;
        } else if self.exist(GO_PROJECT) {
            return Language::Go;
        } else if self.exist(JS_PROJECT) {
            return Language::Js;
        } else if self.exist(D_PROJECT) {
            return Language::D;
        } else if self.exist(PYTHON_PROJECT) {
            return Language::Python;
        } else if self.exist(C_PROJECT) {
            return Language::C;
        } else if self.exist(HASKELL_PROJECT) {
            return Language::Haskell;
        } else if self.exist(R_PROJECT) {
            return Language::R;
        } else if self.exist(RUBY_PROJECT) {
            return Language::Ruby;
        } else if self.exist(PHP_PROJECT) {
            return Language::Php;
        } else if self.exist(JAVA_PROJECT) {
            return Language::Java;
        }
        Language::Unknown
    }

    fn exist(&mut self, file: &str) -> bool {
        Path::new(file).exists()
    }

    fn has(&mut self, index: usize, argument: &str) -> bool {
        if self.args.len() > index {
            return self.args.get(index).unwrap().eq(argument);
        }
        false
    }
}

fn check(args: Vec<String>, l: Language) -> ExitCode {
    match l {
        Language::Rust => Rust::new(args).check(),
        Language::C => C::new(args).check(),
        Language::D => D::new(args).check(),
        Language::Python => Python::new(args).check(),
        Language::Java => Java::new(args).check(),
        Language::Php => Php::new(args).check(),
        Language::Ruby => Ruby::new(args).check(),
        Language::R => R::new(args).check(),
        Language::Go => Go::new(args).check(),
        Language::Js => Js::new(args).check(),
        Language::Haskell => Haskell::new(args).check(),
        Language::Unknown => {
            exit(1);
        }
    }
}

fn hook(args: Vec<String>, l: Language) -> ExitCode {
    match l {
        Language::Rust => Rust::new(args).init(),
        Language::C => C::new(args).init(),
        Language::D => D::new(args).init(),
        Language::Python => Python::new(args).init(),
        Language::Java => Java::new(args).init(),
        Language::Php => Php::new(args).init(),
        Language::Ruby => Ruby::new(args).init(),
        Language::R => R::new(args).init(),
        Language::Go => Go::new(args).init(),
        Language::Js => Js::new(args).init(),
        Language::Haskell => Haskell::new(args).init(),
        Language::Unknown => {
            exit(1);
        }
    }
}

fn watching(args: Vec<String>, l: Language) -> ExitCode {
    match l {
        Language::Rust => Rust::new(args).each(),
        Language::C => C::new(args).each(),
        Language::D => D::new(args).each(),
        Language::Python => Python::new(args).each(),
        Language::Java => Java::new(args).each(),
        Language::Php => Php::new(args).each(),
        Language::Ruby => Ruby::new(args).each(),
        Language::R => R::new(args).each(),
        Language::Go => Go::new(args).each(),
        Language::Js => Js::new(args).each(),
        Language::Haskell => Haskell::new(args).each(),
        Language::Unknown => {
            exit(1);
        }
    }
}

fn main() -> ExitCode {
    let args: Vec<String> = std::env::args().collect();
    let mut app = App::new(&args);
    if app.has(1, "check") {
        return check(args, app.detect());
    } else if app.has(1, "init") {
        return hook(args, app.detect());
    } else if app.has(1, "watch") {
        return watching(args, app.detect());
    }
    exit(1);
}

#[cfg(test)]
mod test {}
