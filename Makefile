CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -I.

SOURCES = config_validator.c test_config_validator.c unity/src/unity.c
HEADERS = config_validator.h unity/src/unity.h unity/src/unity_internals.h

.PHONY: all test coverage analyze clean

# Default build
all: test_runner.exe

# Compile and link
test_runner.exe: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

# Run unit tests
test: test_runner.exe
	./test_runner.exe

# Run tests with coverage measurement
coverage:
	rm -f *.gcda *.gcno *.gcov
	$(CC) $(CFLAGS) --coverage $(SOURCES) -o test_runner_coverage.exe
	./test_runner_coverage.exe
	gcov -b -o test_runner_coverage-config_validator config_validator.c

# Static analysis
analyze:
	$(CC) $(CFLAGS) -fanalyzer -c config_validator.c -o config_validator_analyzer.o

# Remove generated files
clean:
	rm -f *.o *.exe *.gcda *.gcno *.gcov