#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char c = argv[1][0];
	pid_t p;
	char* m_argv[] = {
		"echo", "echo", "Hello world", NULL,
	};
	char *envp[] = {
		"/usr/bin",
		"/bin",
		NULL,
	};

	printf("parent pid: %d\n", getpid());


	switch (c){
		case '1':
			if (!fork()) {
				printf("from execl pid: %d\n", getpid());
				execl("/bin/echo", "echo", "Hello world", NULL);
			}
			break;
		case '2':
			if (!fork()) {
				printf("from execle pid: %d\n", getpid());
				execle("/bin/echo", "echo", "Hello world", NULL, envp);
			}
			break;
		case '3':
			if (!fork()) {
				printf("from execlp pid: %d\n", getpid());
				execlp("echo", "echo", "Hello world", NULL);
			}
			break;
		case '4':

			if (!fork()) {
				printf("from execv pid: %d\n", getpid());
				execv("/bin/ls", m_argv);
			}
			break;
		case '5':
			if (!fork()) {
				printf("from execve pid: %d\n", getpid());
				execve("/bin/ls", m_argv, envp);
			}
			break;
		default:
			if (!fork()) {
				printf("from execvp pid: %d\n", getpid());
				execvp("ls", m_argv);
			}
	}
    pause();
	return 0;}