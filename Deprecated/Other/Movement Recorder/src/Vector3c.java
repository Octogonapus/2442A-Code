/**
 * @author Octogonapus
 */

public class Vector3c
{
    private char port, type;
    private String value;

    public Vector3c(char type, char port, String value)
    {
        this.port = port;
        this.type = type;
        this.value = value;
    }

    public char getPort()
    {
        return port;
    }

    public void setPort(char port)
    {
        this.port = port;
    }

    public char getType()
    {
        return type;
    }

    public void setType(char type)
    {
        this.type = type;
    }

    public String getValue()
    {
        return value;
    }

    public void setValue(String value)
    {
        this.value = value;
    }

    @Override
    public String toString()
    {
        return "Vector3c{" +
               "type=" + type +
               ", port='" + port + '\'' +
               ", value=" + value +
               '}';
    }
}
