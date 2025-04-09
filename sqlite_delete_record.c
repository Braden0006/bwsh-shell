#include <stdio.h>
#include <sqlite3.h>

void sqlite_delete_record(char *command) {
	sqlite3 *db;
	sqlite3_stmt *stmt;

	int rc = sqlite3_open("/Users/bradenwhitcher/workspace/github.com/Braden0006/bwsh-shell/build/test.db", &db);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQLite Error: %s", sqlite3_errmsg(db));
	}

	const char *sql_command = "DELETE FROM Aliases WHERE value = ?;";

	// Prepares the sqlite statement
	rc = sqlite3_prepare_v2(db, sql_command, -1, &stmt, 0);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error in delete_command 1: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}

	sqlite3_bind_text(stmt, 1, command, -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "sqlite error in delete_command 2: %s", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
	} else {
		printf("alias deleted successfully!\n");
	}

	// Cleanup
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}
