test: test_parsely

test_parsely: test_parsely.cpp
	g++ $< -o $@

clean:
	rm test_parsely

.PHONY: test clean
