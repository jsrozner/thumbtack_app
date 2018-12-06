This program is a response to thumbtack.com/challenges (number 3)
Acceptable Commands:
SET [name] [value]: Set a variable [name] to the value [value]. Neither variable names or values will ever contain spaces.
GET [name]: Print out the value stored under the variable [name]. Print NULL if that variable name hasn't been set.
UNSET [name]: Unset the variable [name]
END: Exit the program

BEGIN: Open a transactional block
ROLLBACK: Rollback all of the commands from the most recent transaction block. If no transactional block is open, print out INVALID ROLLBACK
COMMIT: Permanently store all of the operations from any presently open transactional blocks

tack.c is the primary database program ("tack" taken from the name Thumbtack)

hash.c and stack.c are implementations of a hash table and stack respectively

data.c provides an interface that makes hash.c and stack.c scaleable

Makefile:
- "make" compiles everything
- "make run" compiles and starts the database, which takes commands until "END"

Note:
MAX_LEN defined in tack.c defines the maximum length (in characters) of a variable name (and also the maximum number of characters to be interpreted as part of the value). Longer inputs will be truncated. Choosing a number greater than 9 means that the value might not be storeable in an int. Appropriate changes should be made (atol, store to long).

When using for a large database, it would probably be best to choose an INIT_SIZE in hash.h that is prime and approximately double the expected number of elements. 

Using a table of successive primes (each approximately double the previous) for growing the table would also be useful for scaling, since the present implementation just doubles the hash_table size, which means that the size is no longer prime.