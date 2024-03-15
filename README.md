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

After the parsing stage, the commands should be well-structured and ready for execution. Here's an example structure:

typedef enum s_type
{
	REDIR_INPUT = 10,
	REDIR_OUTPUT = 20,
	HERE_DOC = 100,
	RED_END_OUPUT = 200
}						t_type;

typedef struct s_redir
{
	int					index;
	t_type				type;
	char				*file_name;
	char				content[3];
	char				*stopper;
	struct s_heredoc	*heredoc;
	struct s_redir		*prev;
	struct s_redir		*next;
}						t_redir;

typedef struct s_cmd
{
	char				*cmd_str;
	char				clean_cmd[4096];
	char				**clean_split;
	int					nbr_redir;
	char				*cmd_path;
	struct s_cmd		*prev;
	struct s_cmd		*next;
	t_redir				*redir;

}						t_cmd;


This project, while not flawless, is a testament to our perseverance and commitment to learning. We welcome any feedback, contributions, or insights, as we believe in the power of collaborative growth and continuous improvement.


