Assignment

Sneklang has support for networking!

Complete the PacketHeader union. It should have two potential fields:

    tcp_header: A struct:
        The first 2 bytes are the src_port.
        The next 2 bytes are the dest_port.
        The last 4 bytes are the seq_num.
    raw: An array of 8 integers that are each 1 byte in size.

Use uint8_t, uint16_t, and uint32_t for the types of the fields, based on the number of bytes needed. Remember, 8 bits = 1 byte.
