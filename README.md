# LongNumber
<p>This library contains structure LongNumber - a floating point type for long arithmetic.</p>

## Methots and operators of *LongNumber*
- Basic arithmetic operations, such as **+**, **-**, *, **/** are defined for *LongNumber* and have the same syntax as operations for built-in types;
- Comparison operators **>/</>=/<=/==/!=** are also defined for *LongNumber*;
- Method *to_string* converts *LongNumber* to a string;
- Method **abs** returns the absolute value of *LongNumber*;
- Method **print_ln** prints *LongNumber*;
- You can construct LongNumber from long double, std::string, user-defined floating-point literal _ln. Default constructor creates 0.
- The program calculates Pi with the given precision. The biggest correctly calculated precision is 345 digits. 

Class LongNumber was tested using Google tests. Samples are located in subdirectory testdir.
