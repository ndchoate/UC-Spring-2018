import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Connection;
import java.sql.Statement;

//package database_connection;

public class DBConnect
{
    public DBConnect(String host, String username, String password)
    {
        m_host = host;
        m_username = username;
        m_password = password;
    }

    // Input:
    //      String table - Name of table to insert into
    //      String columns - Name of all columns to insert into. Has the form of
    //                      "( column0, column1, ..., columnn)"
    //      String values - Values to enter into each columns, same form as columns string
    public void InsertIntoTable(String table, String columns, String values)
    {
        try
        {
            Statement stmt = m_connection.createStatement();
            String insertStatement = "INSERT INTO " + table + columns + " VALUES " + values;
            stmt.executeQuery(insertStatement);
        }
        catch (SQLException err)
        {
            System.out.println(err.getMessage());
        }
    }

    // Connect to the database using the attributes that have been instantiated using the
    // constructor
    public void Connect()
    {
        try
        {
            m_connection = DriverManager.getConnection(m_host, m_username, m_password);
        }
        catch (SQLException err)
        {
            System.out.println(err.getMessage());
        }
    }

    public Connection m_connection;
    public String m_host;
    public String m_username;
    public String m_password;
}