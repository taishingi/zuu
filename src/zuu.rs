use std::process::ExitCode;

///
/// # All supported vcs
///
pub enum Versioning {
    Git,
    Hg,
}
pub enum Language {
    Rust,
    C,
    D,
    Python,
    Java,
    Php,
    Ruby,
    R,
    Go,
    Js,
    Haskell,
    Unknown,
}

pub const RUST_HOOK: &str =
    "https://raw.githubusercontent.com/taishingi/zuu/develop/hooks/rust/pre-commit";
pub const C_HOOK: &str =
    "https://raw.githubusercontent.com/taishingi/zuu/develop/hooks/c/pre-commit";
pub const D_HOOK: &str =
    "https://raw.githubusercontent.com/taishingi/zuu/develop/hooks/d/pre-commit";
pub const PYTHON_HOOK: &str =
    "https://raw.githubusercontent.com/taishingi/zuu/develop/hooks/python/pre-commit";
pub const JAVA_HOOK: &str =
    "https://raw.githubusercontent.com/taishingi/zuu/develop/hooks/java/pre-commit";
pub const PHP_HOOK: &str =
    "https://raw.githubusercontent.com/taishingi/zuu/develop/hooks/php/pre-commit";
pub const RUBY_HOOK: &str =
    "https://raw.githubusercontent.com/taishingi/zuu/develop/hooks/ruby/pre-commit";
pub const R_HOOK: &str =
    "https://raw.githubusercontent.com/taishingi/zuu/develop/hooks/r/pre-commit";
pub const GO_HOOK: &str =
    "https://raw.githubusercontent.com/taishingi/zuu/develop/hooks/go/pre-commit";
pub const JS_HOOK: &str =
    "https://raw.githubusercontent.com/taishingi/zuu/develop/hooks/js/pre-commit";
pub const HASKELL_HOOK: &str =
    "https://raw.githubusercontent.com/taishingi/zuu/develop/hooks/haskell/pre-commit";

pub const ALREADY_INIT: &str =
    "\x1b[1;37m[ \x1b[1;31mKO \x1b[1;37m] Project already tracked by zuu \x1b[0m";
pub const INIT_SUCCESSFULLY: &str =
    "\x1b[1;37m[ \x1b[1;32mOK \x1b[1;37m] Your project is now tracked by zuu\x1b[0m";

pub const HG_INIT: &str = "\x1b[1;37m[ \x1b[1;31mKO \x1b[1;37m] Run hg init first\x1b[0m";
pub const GIT_INIT: &str = "\x1b[1;37m[ \x1b[1;31mKO \x1b[1;37m] Run git init first\x1b[0m";

pub const RUST_PROJECT: &str = "Cargo.toml";
pub const HASKELL_PROJECT: &str = "stack.yaml";
pub const JS_PROJECT: &str = "package.json";
pub const PYTHON_PROJECT: &str = "pyproject.toml";
pub const GO_PROJECT: &str = "go.mod";
pub const C_PROJECT: &str = "CMakeLists.txt";
pub const D_PROJECT: &str = "dub";
pub const R_PROJECT: &str = "R";
pub const RUBY_PROJECT: &str = "Gemfile";
pub const PHP_PROJECT: &str = "composer.json";
pub const JAVA_PROJECT: &str = "settings.gradle";
pub const GIT_HOOK: &str = ".git/hooks/pre-commit";
pub const GIT_HOOK_DIR: &str = ".git/hooks";

pub const HG_HOOK: &str = ".hg/hgrc";
pub const GIT_DIR: &str = ".git";
pub const HG_DIR: &str = ".hg";

pub trait Application {
    ///
    /// # Constructor
    ///
    /// - `args`            The main args
    /// - `language`        The main language
    ///
    #[must_use]
    fn new(args: &[String]) -> Self;

    ///
    /// # Detect current language
    ///
    ///
    fn detect(&mut self) -> Language;

    fn exist(&mut self, p: &str) -> bool;

    ///
    /// # Check if args contains the argument
    ///
    /// `index`       The argument index
    /// `argument`    The argument to check
    ///
    fn has(&mut self, index: usize, argument: &str) -> bool;
}
///
///
/// # Generic methods to check code
///
pub trait Zuu {
    ///
    /// # Constructor
    ///
    /// - `args`            The main args
    /// - `language`        The main language
    ///
    #[must_use]
    fn new(args: Vec<String>) -> Self;

    fn check(&mut self) -> ExitCode;

    fn init(&mut self) -> ExitCode;

    fn each(&mut self) -> ExitCode;
}
