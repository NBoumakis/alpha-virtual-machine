Work by Konstantina Papafragaki, Katerina Lionta, Nikos Boumakis.

To compile, run `make` in the project folder. The executable is stored in $project_folder/bin
and is named 'avm'.

# Usage:

`avm OPTIONS`

where OPTIONS is:

-   `--in input_file` The executable file, in text or binary format
-   `--text` Assume that the executable is in text format (this takes precedence)
-   `--binary` Assume that the executable is in binary format (this is the default)

# Example:

To run the executable stored in file `test.atc` using the text format run the command:

```
avm --in test.atc --text
```

To run the executable stored in file `test.abc` using the binary format run the command:

```
avm --in test.atc
```

# Notes

-   Run and tested in papaya.csd.uoc.gr
-   Use `hexdump` to examine the executable
-   The preferred method of loading is using the binary format. The text loader is not fully functional
-   Bonus implemented: Every described library function, table keys can be functions, booleans, strings and numbers.
-   All Warnings and Errors are printed in stderr.

# Limitations

-   Functors where not implemented
-   Tables that contain themselves (both implicitly and explicitly) are not supported, they cause segmentation faults.
