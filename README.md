# InertLogger
A simple logging library with support for log levels and debug mode for C.

## Features
- 5 log levels: DEBUG, INFO, WARN, ERROR, FATAL_ERROR
- Automatic timestamp in `HH:MM:SS` format
- Disable DEBUG messages via parameter
- Support for formatted output (like `printf`)

## Usage
### Print a standard greeting message
```c
char *username = "Alex";
ilog(INFO, 0, "Welcome back %s!", username);
```
**Output:**
```
[14:23:05] [INFO] Welcome back Alex!
```

### Conditional DEBUG message output
The second argument accepts a boolean value (0 or 1). When set to `1`, the message is displayed; when set to `0`, the message is not displayed.
**Enable output:**
```c
int width = 800;
int allowdebug = 1;
ilog(DEBUG, allowdebug, "Current width: %d", width);
```
**Output:**
```
[14:23:05] [DEBUG] Current width: 800
```
**Disable output:**
```c
int width = 800;
int allowdebug = 0;
ilog(DEBUG, allowdebug, "Current width: %d", width);
```
**Output:** (empty, message is not shown)
## Compilation
### Debian / Ubuntu / Linux Mint
```bash
sudo apt update && sudo apt install -y gcc
```
```bash
gcc -o innertlogger main.c -Wall
```

### Arch Linux / Manjaro
```bash
sudo pacman -S --noconfirm gcc
```
```bash
gcc -o innertlogger main.c -Wall
```

### Fedora / RHEL / CentOS
```bash
sudo dnf install -y gcc
```
```bash
gcc -o innertlogger main.c -Wall
```

### openSUSE
```bash
sudo zypper install -y gcc
```
```bash
gcc -o innertlogger main.c -Wall
```

### macOS
```bash
xcode-select --install
```
```bash
gcc -o innertlogger main.c -Wall
```

### Windows (MinGW)
```powershell
winget install -e --id GnuWin32.Make
```
```powershell
gcc -o innertlogger.exe main.c -Wall
```

### Alpine Linux
```bash
sudo apk add gcc musl-dev
```
```bash
gcc -o innertlogger main.c -Wall
```

### FreeBSD
```bash
sudo pkg install -y gcc
```
```bash
gcc -o innertlogger main.c -Wall
```
