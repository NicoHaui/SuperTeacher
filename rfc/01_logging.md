- Feature Name: logging

# Summary

```c

#include "log.h"

error("An error append");
// "An error append" appear in the terminal

```

# Motivation

Currently, we use fprintf to print logs message to stderr. Implementing some
higher level function will allow us to have more information like files and date
and to be more flexible.

In the future, we can easily redirect message from the terminal to a GUI without
changing other file than log.c.

# Detailed design

## Log level

### TRACE

Detailed information, used to follow every step of a function.
Should be used in last resort

### DEBUG

Detailed information about some step of a function.
Should be used with parsimony.

### INFO

Interesting runtime events. Visible by default (Short message)

### WARN

Unexpected events by example: "Run of an untested version of windows"

### ERROR

An error that can be recovered

### FATAL

An error that can't be recovered (Program must exit)

## C Interface

## log.h

This library must implement these functions:

```c
void trace( const char * format, ...);
void debug( const char * format, ...);
void info( const char * format, ...);
void warn( const char * format, ...);
void error( const char * format, ...);
void fatal( const char * format, ...);
```


These functions should write a "printf" style message in stderr/stdout, using
this format:

```txt
datetime file line level: message
```

Exemple:

```txt
20160312-104812 main.c WARN: Unsupported OS detected (WIN-VISTA)
```

## Command Line Interface

### Minimal level to print

Use `--log=DEBUG` to select a minimal level to print.
By default: `--log=INFO`

# Unresolved questions

For now, logs are printed in the terminal. 
