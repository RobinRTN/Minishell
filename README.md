# Minishell
Our very own minishell - replica of bash

## Overview

The Minishell project at [42 School](https://www.42.fr/) is an intricate and rewarding challenge. Completed shortly after training at Le Wagon, this project required thorough collaboration and a deep understanding of shell programming. While our project isn't perfect, it encapsulates the significant growth in our skills and is a substantial part of our learning journey.

## Global Approach

We chose to focus on the mandatory features, setting aside the bonus parts for a dedicated effort on quality. Our strategy was built around:
- Utilizing chained lists for efficient memory management.
- Adhering strictly to `norminette` standards for maintainable code.
- Dividing the project into two primary sections: parsing and execution, to optimize teamwork.

## Parsing Breakdown

### 1. Initialization and Error Handling
- Setting up the core data structures.
- Extracting `PATH` from the environment.
- Handling user input through `readline`.
- Implementing initial checks for empty lines or unclosed quotes.

### 2. Expansion
- Processing elements with `$` based on their context (quotes, heredocs, variable names).
- Expanding elements correctly according to their specific conditions.

### 3. Command Separation
- Splitting input at `|` to indicate separate commands, while respecting quotes.
  
### 4. Redirection Identification
- Detecting redirections within each command.
- Creating sublists for each redirection type and filename.
- Removing redirection elements from the command string.

### 5. Validation and Error Reporting
- Ensuring commands are executable and reporting errors as needed.

### 6. Command Processing
- Breaking down the command string by spaces.
- Appending `PATH` to commands.
- Repeating this process for all commands.

## Expected Outcome
After the parsing stage, the commands should be well-structured and ready for execution. You can check the minishell.h file to check how the lists are made and connected
  
## Execution Breakdown


## Builtins Breakdown

### 1. `exit`
- **Single Argument Check**: Errors out if more than one argument is provided.
- **Range Checking**: Validates if the exit status is within the `int` range. Prints an error for invalid ranges.
- **Exit Behavior**: Exits the program with the specified status (up to 255). Higher values overflow, and negatives are considered positive.

### 2. `cd`
- **Special Cases**: Supports `cd -`, `cd --`, and `cd ~`.
- **Argument Validation**: Errors out if multiple arguments are passed.

### 3. `export`
- **Environment Variables**: Lists all environment variables from the initial chained list.
- **Argument Formatting**: Ensures arguments start with `_` and handles numerical values. Checks for `=` presence.
- **Output Format**: Quotes variables with `=` in expansion but not in the `env` command display.

### 4. `env`
- **Display Environment**: Shows all environment variables, reflecting current session changes.

### 5. `unset`
- **Variable Removal**: Deletes specified variables from the environment.
- **Argument Handling**: Manages multiple arguments and addresses error scenarios.

### 6. `echo`
- **Flag Processing**: Handles `-n` and consecutive `-n` flags effectively.

### 7. `pwd`
- **Functionality**: Implements the print working directory command straightforwardly.


This project, while not flawless, is a testament to our perseverance and commitment to learning. We welcome any feedback, contributions, or insights, as we believe in the power of collaborative growth and continuous improvement.


