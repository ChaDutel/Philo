gcc -Wall -Wextra main.c parsing.c init.c exec.c state.c && leaks -atExit -- ./a.out 5 30 30 30 5
gcc -Wall -Wextra -g3 -fsanitize=address main.c parsing.c init.c exec.c state.c && ./a.out 5 30 30 30 5
gcc -Wall -Wextra -g3 -fsanitize=thread main.c parsing.c init.c exec.c state.c && ./a.out 5 30 30 30 5 