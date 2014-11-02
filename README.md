parsely
=======

![](https://cloud.githubusercontent.com/assets/1570168/4874405/d33421a4-6253-11e4-9cad-288253249949.png)

Parsely helps you tokenize and parse simple space-delimited files. For example, Parsely can print this tokenized version of a simple Makefile.

```
1: test:
1:       test_parsely
3: test_parsely:
3:               test_parsely.cpp
4:  g++
4:      $<
4:         -o
4:            $@
6: clean:
7:  rm
7:     test_parsely
9: .PHONY:
9:         test
9:              clean
```

Here's the minimal amount of code you need to start using Parsely:

```c++
#import "parsely.cpp"

parsely::FileParser parser(filename);
while (parser.advance_line()) {
  while (parser.next_token()) {
    do_something_with(parser.token);
  }
}
```

Parsely also helps you inform the user of incorrectly formatted files. Use `parser.here()` to print out the current token in context:

```
Oh no! An error occurred at parsely.cpp:103:38: (additional info can go here)
  oss << line_string << std::endl << zfill_to_colno() << '^' << underline_token() << std::endl;
                                     ^~~~~~~~~~~~~~~~
```

Use `require_next_token` methods to try to parse as the given data type and exit with an error if the next token doesn't match. Here's an example using `parser.require_next_token_positive(float)`:

```
error: expected a positive number at in/scene1.txt:4:25
                ltp 200 200 200 0.6 0.6 -0.6
                                        ^~~~
```

There's not much documentation right now, but there's a test program
that might help explain things. To run it, `make` and then `./test_parsely some_file`.
