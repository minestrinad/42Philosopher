# 42Philosopher

## Overview

The "Philosophers of Ecole 42" project is an implementation of the dining philosophers problem. The project simulates philosophers sitting at a round table, alternating between eating, thinking, and sleeping, with the challenge of avoiding deadlock and resource contention.

## Table of Contents

- [Common Instructions](#common-instructions)
- [Overview](#overview)
- [Global Rules](#global-rules)
- [Mandatory Part](#mandatory-part)
- [How to Run](#how-to-run)
- [Output Format](#output-format)
- [Contributing](#contributing)
- [License](#license)

## Common Instructions

- The project must be written in C.
- Code must comply with the Norm, and bonus files/functions are included in the norm check.(no bonus)
- Functions should not quit unexpectedly, and all heap-allocated memory must be properly freed to avoid leaks.
- A Makefile must be submitted, and it should compile the source files with the flags -Wall, -Wextra, and -Werror.
- Global variables are forbidden.

## Global Rules

- Philosophers are threads, and there is one fork between each pair of philosophers.
- To prevent philosophers from duplicating forks, fork states should be protected with mutexes.

## Mandatory Part

### Program Name: philo

- Makefile rules: `NAME`, `all`, `clean`, `fclean`, `re`
- Arguments: `number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`
- External functions: `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`
- Description: Philosophers with threads and mutexes

## How to Run

To run the program, follow these steps:

1. Clone the repository to your local machine.
2. Navigate to the `42Philosophers/` directory.
3. Run the Makefile: `make`
4. Execute the program with the required arguments.

Example:

```bash
./philo 5 800 200 200
```

## Output Format

- State changes of a philosopher must be formatted with a timestamp.
- The log should include messages for taking a fork, eating, sleeping, thinking, and dying.
- Displayed state messages should not be mixed up with other messages.
- A message announcing a philosopher's death should be displayed no more than 10 ms after the actual death.

## Contributing

Contributions to this project are welcome. Feel free to submit bug reports, feature requests, or code contributions.

## License

This project is open-source
