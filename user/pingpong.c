#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p_child[2], p_parent[2];
    pipe(p_child);
    pipe(p_parent);
    if(fork() == 0) {
        char buf[512];
        int n = read(p_parent[0], buf, 4);
        close(p_parent[0]);
        if(n == 4) {
            printf("%d: received ping\n", getpid());
        }
        write(p_child[1], "pong", 4);
        close(p_child[1]);
        exit(0);
    } else {
        char buf[512];
        write(p_parent[1], "ping", 4);
        close(p_parent[1]);
        int n = read(p_child[0], buf, 4);
        close(p_child[0]);
        if(n == 4) {
            printf("%d: received pong\n", getpid());
        }
        exit(0);
    }
}