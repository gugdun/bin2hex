# bin2hex
Command line tool to convert binary file to Verilog HEX format

## Usage
```bash
bin2hex INPUT OUTPUT [BYTES_PER_LINE]
```
 * `INPUT` must be existing file name
 * `OUTPUT` file will be overwritten
 * `BYTES_PER_LINE` is optional, must be unsigned integer
 
 ## Build
 1. Create build directory:
 ```bash
 mkdir build
 ```
 2. Generate files for your favourite build system:
 ```bash
 cmake -B build -G Ninja
 ```
 3. Then go to build directory:
 ```bash
 cd build
 ```
 4. And build the project!
 ```bash
 ninja
 ```
 
