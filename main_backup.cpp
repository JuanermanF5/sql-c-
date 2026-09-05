#include <iostream>
#include <sql.h>
#include <sqlext.h>

int main() {

    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLHSTMT hStmt;
    SQLRETURN ret;

    // Crear entorno ODBC
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);

    SQLSetEnvAttr(
        hEnv,
        SQL_ATTR_ODBC_VERSION,
        (SQLPOINTER)SQL_OV_ODBC3,
        0
    );

    // Crear conexión
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    SQLCHAR connectionString[] =
        "DRIVER={ODBC Driver 18 for SQL Server};"
        "SERVER=JUANERMAN\\SQLEXPRESS;"
        "DATABASE=ExperimentoCPP;"
        "Trusted_Connection=yes;"
        "TrustServerCertificate=yes;";

    SQLCHAR connectionOut[1024];
    SQLSMALLINT connectionOutLength;

    ret = SQLDriverConnect(
        hDbc,
        NULL,
        connectionString,
        SQL_NTS,
        connectionOut,
        sizeof(connectionOut),
        &connectionOutLength,
        SQL_DRIVER_NOPROMPT
    );

    if (SQL_SUCCEEDED(ret)) {
        std::cout << "Conectado a SQL Server correctamente.\n";
    } else {
        std::cout << "Error al conectar a SQL Server.\n";
        return 1;
    }

    // Crear sentencia
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    SQLCHAR sql[] =
        "INSERT INTO Personas (nombre, edad) "
        "VALUES ('Juan', 18)";

    ret = SQLExecDirect(hStmt, sql, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        std::cout << "Registro insertado correctamente.\n";
    } else {
        std::cout << "Error al insertar el registro.\n";
    }

    // Liberar recursos
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}