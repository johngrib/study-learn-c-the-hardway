#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

/**
 * 여러 개의 Address를 갖는 데이터베이스.
 */
struct Database {
    struct Address rows[MAX_ROWS];
};

struct Connection {
    FILE *file;
    struct Database *db;
};

struct Connection *conn;

void Database_close();

void die(const char *message)
{
    Database_close(conn);
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load()
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) {
        die("Failed to load database.");
    }
}

struct Connection *Database_open(const char *filename, char mode)
{
    conn = malloc(sizeof(struct Connection));
    if (!conn) {
        die("Memory error");
    }

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db) {
        die("Memory error");
    }

    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");
        if (conn->file) {
            Database_load();
        }
    }

    if (!conn->file) {
        die("Failed to open the file");
    }
    return conn;
}

void Database_close()
{
    if (conn) {
        if (conn->file) {
            fclose(conn->file);
        }
        if (conn->db) {
            free(conn->db);
        }
        free(conn);
    }
}

void Database_write()
{
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) {
        die("Failed to write database.");
    }
    rc = fflush(conn->file);
    if (rc == -1) {
        die("Cannot flush database.");
    }
}

void Database_create()
{
    int i = 0;
    for (i = 0; i < MAX_ROWS; i++) {
        // 초기화 용도로 사용할 프로토타입을 만든다.
        struct Address addr = { .id = i, .set = 0 };
        // 이제 지정만 하면 된다.
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) {
        die("Already set, delete it first");
    }
    addr->set = 1;
    char *res = strncpy(addr->name, name, MAX_DATA);
    addr->name[MAX_DATA - 1] = '\0';

    // strncpy 버그를 보여줌
    if (!res) {
        die("Name copy failed");
    }
    res = strncpy(addr->email, email, MAX_DATA);
    addr->email[MAX_DATA - 1] = '\0';
    if (!res) {
        die("Email copy failed");
    }
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_delete(int id)
{
    // 현대의 C는 간단히 하나의 구조체에 다른 구조체 값을 지정하는 것만으로도 구조체를 복사해 준다.
    struct Address addr = { .id = id, .set = 0 };
    conn->db->rows[id] = addr;
}

void Database_list()
{
    int i = 0;
    struct Database *db = conn->db;

    for (i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];

        if (cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        die("USAGE: ex17 <dbfile> <action> [action params]");
    }
    char *filename = argv[1];
    char action = argv[2][0];
    conn = Database_open(filename, action);
    int id = 0;

    if (argc > 3) {
        id = atoi(argv[3]);
    }
    if (id >= MAX_ROWS) {
        die("There's not that many records.");
    }

    switch (action) {
        case 'c':
            Database_create();
            Database_write();
            break;
        case 'g':
            if (argc != 4) {
                die("Need an id to get");
            }
            Database_get(conn, id);
            break;
        case 's':
            if (argc != 6) {
                die("Need id, name, email to set");
            }
            Database_set(conn, id, argv[4], argv[5]);
            Database_write();
            break;
        case 'd':
            if (argc != 4) {
                die("Need id to delete");
            }
            Database_delete(id);
            Database_write();
            break;
        case 'l':
            Database_list();
            break;
        default:
            die("Invalid action: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close();
    return 0;
}

/*
$ make ex17
make: `ex17' is up to date.

$ ./ex17 db.dat c

$ ./ex17 db.dat s 1 zed zed@zedshaw.com
$ ./ex17 db.dat s 2 frank frank@zedshaw.com
$ ./ex17 db.dat s 3 joe joe@zedshaw.com

$ ./ex17 db.dat l
1 zed zed@zedshaw.com
2 frank frank@zedshaw.com
3 joe joe@zedshaw.com

$ ./ex17 db.dat d 3

$ ./ex17 db.dat l
1 zed zed@zedshaw.com
2 frank frank@zedshaw.com

$ ./ex17 db.dat g 2
2 frank frank@zedshaw.com
*/

