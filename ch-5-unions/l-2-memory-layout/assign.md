
Assignment

Take a look at the val_or_err_t union. It represents either an integer value or an unsigned (non-negative) integer error code.

    Run the code in its current state.

    Notice that the .value field is set to -420, then the data in each field is printed. The .value field works as you'd expect, printing -420. However, the .err field prints 4294966876! It's trying to interpret the bytes of -420 as an unsigned integer, which results in a very large number.

    Uncomment the next block of code, and run it without submitting.

    Notice that now we set the .err field (an unsigned integer) to UINT_MAX, which is a constant representing the largest possible unsigned integer (4294967295 in my case). As expected, the .err field prints 4294967295. However, the .value field prints -1! It's reading the bytes for 4294967295 as a signed integer instead of an unsigned one, which turns it into -1.

Submit the fully uncommented code.
