# hello-world
Well-written C code to greet the world!

## Example Use

```console
:~$./hello_world
Hello, world!
```

## Build (Ubuntu)

```console
:~$sudo apt-get install automake gnulib
:~$git clone https://github.com/hannah-leitheiser/hello-world
:~$cd hello-world
:~$gnulib-tool --import progname vasprintf
:~$autoreconf --install
:~$./configure
:~$make
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
