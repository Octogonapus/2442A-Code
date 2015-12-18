import java.util.ArrayList;

/**
 * @author Octogonapus
 */

public class Main
{
    public static void main(String[] args)
    {
        ArrayList<TimePair> timePairs = parse("m1002a3004d50061234m2001a4003d60054321");

        for (TimePair timePair : timePairs)
        {
            System.out.print(timePair.getVectors()[0] + " ");
            System.out.print(timePair.getVectors()[1] + " ");
            System.out.print(timePair.getVectors()[2] + ", ");
            System.out.print("Time{" + timePair.getTime() + "}\n");
        }
    }

    public static ArrayList<TimePair> parse(String toParse)
    {
        ArrayList<TimePair> vectors = new ArrayList<>(0);
        char[] pChars = toParse.toCharArray();
        Vector3c[] vectorA = new Vector3c[3];
        String sM, sA, sD;
        String time;

        for (int i = 0; i < pChars.length; i++)
        {
            if (pChars[i] == 'm')
            {
                try
                {
                    sM = "";
                    sA = "";
                    sD = "";

                    sM += pChars[i + 2];
                    sM += pChars[i + 3];
                    sM += pChars[i + 4];

                    sA += pChars[i + 7];
                    sA += pChars[i + 8];
                    sA += pChars[i + 9];

                    sD += pChars[i + 12];
                    sD += pChars[i + 13];
                    sD += pChars[i + 14];

                    vectorA[0] = new Vector3c(pChars[i], pChars[i + 1], sM);
                    vectorA[1] = new Vector3c(pChars[i + 5], pChars[i + 6], sA);
                    vectorA[2] = new Vector3c(pChars[i + 10], pChars[i + 11], sD);

                    time = "";
                    time += pChars[i + 15];
                    time += pChars[i + 16];
                    time += pChars[i + 17];
                    time += pChars[i + 18];

                    vectors.add(new TimePair(vectorA, Integer.parseInt(time)));

                    i += 18;
                    vectorA = new Vector3c[3];
                }
                catch (Exception e)
                {
                    System.out.println("pChars wrong format");
                }
            }
        }

        return vectors;
    }
}
