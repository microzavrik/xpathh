# Console file manager xpathh

This is a command-line file manager that allows you to perform various file operations using different flags.
Usage

To use the file manager, run the following command:
[flag] [parameters]

Replace [flag] with one of the following flags:
-p: print directory
-d: delete file
-c: copy file
-a: create file
-r: rename file
-fp: file properties
Replace [file/directory name] with the name of the file or directory you want to perform the operation on.
Examples

Print the contents of a directory:
file_manager -p /path/to/directory

Delete a file:
`-d /path/to/file`

Copy a file:
-c /path/to/source/file /path/to/destination/file

Create a file:
-a /path/to/new/file

Rename a file:
-r /path/to/old/file /path/to/new/file

Get file properties:
-fp /path/to/file
