
Assignment

Sneklang is going to need objects. We'll hand-code those objects, and Sneklang developers will use them to store dynamic variables, kinda like Python. Everything is an object, even simple integers and strings!

Take a look at the SnekObject struct in exercise.h. It has a kind field that stores the type of the object (like INTEGER or STRING) and a data field that stores the actual data.

    Create a snek_object_kind_t enum type in exercise.h. It's the one used as the kind field of the provided SnekObject. It's an enum that can be an INTEGER (0) or a STRING (1).
    Complete the format_object function in exercise.c that uses a switch on the .kind of a snek_object_t and writes a formatted string to the associated buffer.
        For an integer, write the string int:N to the buffer, replacing N with the integer value
        For a string, write the string string:STR to the buffer, replacing STR with the string value

You can use sprintf to write the formatted string to the buffer. For example:

char buffer[100];
sprintf(buffer, "There are %d lights!", 4); // There are 4 lights!

