# InertLogger

A powerful, cross-platform logging library for C with color support, runtime configuration, and multiple log levels.

## Features

- 6 output modes: DEBUG, INFO, WARN, ERROR, FATAL_ERROR, STDOUT
- ANSI color support with RGB configuration (Linux/macOS)
- Windows console color support (automatic fallback)
- Runtime configuration via iconfig() function
- Automatic timestamp in [HH:MM:SS] format (toggleable)
- Customizable prefixes for each log level (toggleable)
- Formatted output (like printf)
- Cross-platform: Linux, macOS, Windows (MinGW), FreeBSD

## Quick Start

```c
#include "inertlogger.h"

int main() {
    // Basic logging
    ilog(INFO, "Application started");
    ilog(DEBUG, "Debug value: %d", 42);
    ilog(WARN, "Something suspicious happened");
    ilog(ERROR, "Operation failed with code: %d", -1);
    ilog(FATAL_ERROR, "Critical failure, exiting...");
    ilog(STDOUT, "Normal output without formatting");
    
    return 0;
}
```

**Output Example**

```
[22:56:48] [INFO] Application started
[22:56:48] [DEBUG] Debug value: 42
[22:56:48] [WARN] Something suspicious happened
[22:56:48] [ERROR] Operation failed with code: -1
[22:56:48] [FATAL ERROR] Critical failure, exiting...
Normal output without formatting
```

## Configuration
Use `iconfig()` to change logging behavior at runtime:

```c
// Disable DEBUG messages
iconfig(ENABLE_DEBUG, "0");

// Disable timestamps
iconfig(ENABLE_TIME, "0");

// Disable prefixes (DEBUG/INFO/WARN, etc.)
iconfig(ENABLE_PREFIX, "0");

// Disable all colors
iconfig(ENABLE_COLORS, "0");

// Change colors (RGB format)
iconfig(SET_COLOR_DEBUG, "255, 100, 100");   // light red
iconfig(SET_COLOR_INFO,  "0, 255, 0");       // green
iconfig(SET_COLOR_WARN,  "255, 255, 0");     // yellow
iconfig(SET_COLOR_ERROR, "255, 0, 0");       // red
iconfig(SET_COLOR_FATAL_ERROR, "255, 0, 255"); // magenta
```

**Default Colors**

| Level | RGB Value | Color |
|-------|-----------|-------|
| DEBUG | 255, 0, 240 | Magenta |
| INFO | 0, 230, 0 | Bright Green |
| WARN | 240, 190, 0 | Yellow-Orange |
| ERROR | 210, 0, 0 | Dark Red |
| FATAL_ERROR | 255, 0, 0 | Bright Red |
| STDOUT | no color | Default |

## API Reference
`ilog(Level level, const char* format, ...)`
Main logging function.

Parameters:
- level - Log level (DEBUG, INFO, WARN, ERROR, FATAL_ERROR, STDOUT)
- format - Printf-style format string
- ... - Variable arguments


`iconfig(PropertiesKey key, const char* value)`
Configure logger behavior at runtime.

Available keys:
- **ENABLE_DEBUG** - Enable/disable DEBUG messages (0/1)
- **ENABLE_COLORS** - Enable/disable colored output (0/1)
- **ENABLE_TIME** - Enable/disable timestamp (0/1)
- **ENABLE_PREFIX** - Enable/disable level prefix (0/1)
- **SET_COLOR_DEBUG** - Set color for DEBUG level (RGB string)
- **SET_COLOR_INFO** - Set color for INFO level
- **SET_COLOR_WARN** - Set color for WARN level
- **SET_COLOR_ERROR** - Set color for ERROR level
- **SET_COLOR_FATAL_ERROR** - Set color for FATAL_ERROR level

## Compilation
Linux (Debian/Ubuntu/Mint)

```bash
sudo apt install gcc
gcc -o program main.c inertlogger.c -Wall
```

Linux (Arch/Manjaro)

```bash
sudo pacman -S gcc
gcc -o program main.c inertlogger.c -Wall
```

Linux (Fedora/RHEL/CentOS)

```bash
sudo dnf install gcc
gcc -o program main.c inertlogger.c -Wall
```

macOS

```bash
xcode-select --install
gcc -o program main.c inertlogger.c -Wall
```

Windows (MinGW)

```powershell
winget install -e --id GnuWin32.Make
gcc -o program.exe main.c inertlogger.c -Wall
```

FreeBSD

```bash
sudo pkg install gcc
gcc -o program main.c inertlogger.c -Wall
```

Alpine Linux

```bash
sudo apk add gcc musl-dev
gcc -o program main.c inertlogger.c -Wall
```

---

Note: Colors work on Linux/macOS by default. On Windows 10+, colors work automatically. On older Windows versions, colors will be disabled automatically. It has not been tested on Windows, macOS, FreeBSD and some Linux distributions.
