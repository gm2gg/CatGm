# CatGm
download - https://github.com/gm2gg/CatGm/releases/download/CatGm/catgm.exe

Minimalist programming language interpreter written in C. Executes commands from .catgm files.

## Requirements
- Windows
- GCC (MinGW / MSYS2)

## Build
gcc src/main.c -o catgm.exe

## Run
catgm.exe <file.catgm>

## CatGm Language Cheatsheet (New Features)

### Variables

- Two types:  
  - `int(...)` → integer values (like Python int)  
  - `it(...)` → string values (like Python str)

- Assignment syntax:  

variable_name = int(123)
variable_name = it(text)


- Rules for variable names:  
- Can contain English letters (`a-z`, `A-Z`)  
- Can contain underscores `_`, but **not at the start or end**  
- Can contain digits (`0-9`), but **not at the start**

---

### Strings in it(...)

- Same rules as `o(...)` regarding special characters:  
- Normal mode: `it(...)` → cannot use `()` or `{}` inside  
- Extended mode: `it-(...)-` → allows `()` and `{}` inside  
- Inside extended mode, cannot use `-()-` or `-{ }-` markers

---

### Output with o(...)

- Already supported:  
- `o(...)` → simple output  
- `o-(...)-` → extended output, allows `()` and `{}` inside
