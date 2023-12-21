# Minishell 42 Project

Our first major project carried out as a team during the common core curriculum at [42 Nice](https://42nice.fr/). This project introduces us to the world of shells ([Bash](https://www.gnu.org/software/bash/) in this case) and their functioning. After completing this project, I assure you that you will have learnt a good many ways to manipulate such a powerful interface to your needs. :smiling_imp:

That being said, the Bash shell was not created in 3 months by a 2-person team of amateur developers like us. Ours is a _mini_ respresentation of bash that will certainly have its cons. :unamused:

Think of this C-coded mini shell as **a light-weight command-line interface** that can be used for **basic manipulations in testing environments**.

## Known Shortcomings
As previously stated, this mini shell is not perfect. One of the known issues with the current version (that we recently realised) is its inability to implement heredoc redirections '<<' in more than one node or serie (a list of commands separate by a pipe '|'). This issue will be resolved in the next update. Hence, for the time-being, if you plan on utilising our mini shell, avoid using heredocs in more than one serie.

## Getting Started
To get started with the project, you will need to have had installed Readline, a function commonly used in C programming.
Depending on your operating software, do not hestitate to search on your favourite search engine how to install the above-mentioned function.

Thereafter, git clone the repository and use ```make``` to compile the shell. You can launch the shell with ```./minishell```.
Feel free to use whichever Bash commands you fancy, although, you should know that most _Bash special characters_ like ```;```, ```/```, ```&```, etc. are not supported.
The project subject has its restrictions (thankfully), which involves parsing only double-quoted, single-quoted and dollar-expansion arguments.

## Contact
For any queries or feedback regarding the Minishell 42 project, feel free to contact us. :blush:
