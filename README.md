# hello-world
C code to greet the world!

## Example Use

```console
$./hello_world
Hello, world!
```

## Build (Ubuntu)

```console
$sudo apt-get install automake gnulib
$git clone https://github.com/hannah-leitheiser/hello-world
$cd hello-world
/hello-world$gnulib-tool --import progname vasprintf
/hello-world$touch config.rpath
/hello-world$autoreconf --install
/hello-world$./configure
/hello-world$make
/hello-world$cd src
/hello-world/src$./hello_world
```

## Command Line Options

* -w, --width
   * Terminal Width in Columns for Word Wrap
   *  0 for autodetect

* -n, --nowrap
  -   Disable Word Wrap

* -l, --lang
    - Language

* -v, --version
    - Version Information

* -o, --debugoutput
    - Debug output:
    - 0 for standard output
    - otherwise a filename

* -d, --debuglevel
    - Debug Level:
    - 0 Error
    - 1 Warning
    - 2 Verbose

* -h -?, --help
   -  Get Help Message
