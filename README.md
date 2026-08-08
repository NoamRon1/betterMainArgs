# BetterMainArgs

BetterMainArgs is a small C++20 command-line argument parser. It lets you describe
short and long options in a configuration vector, parse `argc`/`argv`, generate
usage text, and enforce mandatory options.

## Features

- Short options such as `-h` and long options such as `--help`
- Options with or without a value
- Formatted usage text
- Mandatory option validation
- Unknown-option detection
- Header and source files with no external dependencies

## Requirements

- A C++20-compatible compiler

## Usage

Add `betterMainArgs.h` and `betterMainArgs.cpp` to your project, then define an
argument configuration and create an `ArgumentProcessor`:

```cpp
#include "betterMainArgs.h"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
	using BetterMainArguments::Argument;
	using BetterMainArguments::ArgumentProcessor;

	std::vector<Argument> config = {
		{ {"h", "help"}, "prints this message", false },
		{ {"v", ""},     "prints the version", false },
		{ {"o", "output"}, "sets the output filename", true },
		{ {"", "input"}, "sets the input filename", true }
	};

	ArgumentProcessor parser(argc, argv);

	try {
		std::cout << parser.printUsage(config);

		const auto usedArguments = parser.getUsedArguments(config);
		for (const auto& argument : usedArguments) {
			std::cout << argument.getFlags() << ": "
					  << argument.argument << '\n';
		}
	} catch (const std::runtime_error& error) {
		std::cerr << error.what();
		return 1;
	}

	return 0;
}
```

An option is described by:

```cpp
{ {"short-name", "long-name"}, "help text", mandatory }
```

Use an empty short or long name when an option should have only one form. An
option receives a value when the next command-line token does not begin with
`-`:

```text
./my-program --output result.txt --input data.txt
```

Value-less flags can be used on their own:

```text
./my-program --help
```

## API

### `Argument`

- `argumentNames`: a `{shortName, longName}` pair
- `helpMessage`: text shown by `printUsage`
- `mandatory`: whether the option must be supplied with a value
- `argument`: the parsed value, empty for a flag without a value
- `getFlags()`: returns the formatted option names

### `ArgumentProcessor`

- `printUsage(config)`: returns formatted usage text
- `getUsedArguments(config)`: parses the command line and returns the options
  that were supplied

## Errors

`getUsedArguments` throws `std::runtime_error` when:

- an unknown option is supplied;
- a mandatory option is missing; or
- a mandatory option is supplied without a value.

Catch the exception in the application if you want to print a custom error or
exit with a specific status code.
