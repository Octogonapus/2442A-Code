/**
 * @author Octogonapus
 */

public class TimePair
{
    private Vector3c[] vectors;
    private int time;

    public TimePair(Vector3c[] vectors)
    {
        this.vectors = vectors;
        this.time = -1;
    }

    public TimePair(int time)
    {
        this.vectors = null;
        this.time = time;
    }

    public TimePair(Vector3c[] vectors, int time)
    {
        this.vectors = vectors;
        this.time = time;
    }

    public Vector3c[] getVectors()
    {
        return vectors;
    }

    public void setVectors(Vector3c []vectors)
    {
        this.vectors = vectors;
    }

    public int getTime()
    {
        return time;
    }

    public void setTime(int time)
    {
        this.time = time;
    }

    @Override
    public String toString()
    {
        return "TimePair{" +
               "vectors=" + vectors +
               ", time=" + time +
               '}';
    }
}
