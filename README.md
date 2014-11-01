parsely
=======

![](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGQAAABMBAMAAABpMw88AAAABGdBTUEAALGPC/xhBQAAAAFzUkdCAK7OHOkAAAAYUExURQAAAJDTSarXcsTrgZrRYIfHTHHCIkujECKgEewAAAAGdFJOUwD+QvaHxh8zH3AAAARSSURBVEjH1ZdNc9pIEIbFLDhXNzLjq0yAXAPj3CUMyhVcWL56WNRzdmoz8/f3bQkSE1sCTls7VaZsPI/66+2eURT9pytLzt+r8DOMenQB8tcsitbJ3SVIJ04i/pZRegFCsyXT9BKkG8fEtkbUOd5lT3OiNVuiVM2TrP94Rr4IPsVMse3fkdW6f4aZiQXD1pIu2BPfnCYWYyYaaDjG7II9A8mICNvzA6IHpxKg1gAQew6SnQt8GomiMTNbHZPWlRW6OUdiObOGjVtnXSDqR1l7TZUaLUaaLZN1MOeJVhNetVceMWjtYMaKf17HQ+brUxnjalXIwNL91UlELbUQ8AzY2NIMv5/Sp9IWBhif+qZj4yUzJNOe6E7tmIViVnc2Lpg3abRoRda2RkpLSU7T6o+kaEWGWIth7kuKFfRZPWDn0/HJvlYc06xjJeOaHftHsi2b6/xcUfw1m4pGkT30td61GKh12NXxKIZfWjJx61lvG4FRmpV1c04fTExG1MDOc4tq7ijn6oE0NcZMpxWFJuCkpZJc/zuOjVnDBmHe6ODbQpkgXJhRsblPopGW4QHXfNpclERJIYAYI7Z6GDUG/Vk2DvWe5s0YZlZRz3ytviksfUMwnhrljEh2kNUu+mz2DeRoUIlm2xyJ5idJwN5IFGHW8KAIzYhEUqL5d+bguwrkkLGyOcldUSEqfv/rm+dX5x2XzTleIhJeM5v7BdJXzRvU0Tu/apti1frb1EtGIAffHH7vQPDr/cOemfJtCMFTy9jbNzKmpBo+oIybZFTI3GyMBYz38MOi6gaHBuvwM1GFD2HexmAYy/ki6hJ9hZAouBYeG+N3VbgbjuvgofzwOu8K87E0P1eDzwsCEaMtMZslX+UzkJ8fEQ8GSDkB9cRzntJshF5BXaB+MbP6iDDYnU6cePciJ1kajRyC8XI8fWRGKlEukioD0OEEhybNe9o7YSj48Z+NpkDM1D5p2LO7ksOf1jIupJbunV9oQzPbC/FJ5kP5CY9GDtY1gvXjPXEo1qDAFLL8xTtbnVCbPbJ9F8cvRwvW3r7yMvCrIOElr5HN8R3MmN89lDEOSq8HuCiIkMO2J0D/Kv3DreRYz5q189ZBNS7806niP741PZg3T1CFdBWQYB2khu2Ze6eX7iFXe7+gSpyUUMozPquqCPJyHMlbXld+VeL6LjUFA8QdJ0y9NRIVFbK26JRPPsjU9xDaj+Gwefbr6tBHpkUisKARGYy0XHu0XGGYc2yFgKGDCRC3CM2n/1rbjQVTSDwcBmEnSEi/t1wYRo8dYioLuKfJL3n1JXAe0l7rHSPDMbwTJGdf3ETPgcchVa0I6UxvC0j/US4wXed3vdB+6ndvkkyvcL3S/e7TIurN79JRceI2nsBOggzo/SVxUb9tnLhe66hAe+3P1HMu8V3aAsnt9oIXBUyW3I745YL3pAF0Y5Px9QVWruUt5rwgDlawt9uPLl0qif536181V4SUTy71qAAAAABJRU5ErkJggg==)

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
