import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class klockan2 {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int angle = Integer.parseInt(reader.readLine().trim());
        reader.close();
        
        String result = doCase(angle);
        System.out.println(result);
    }

    public static String doCase(int angle) {
        int[] mods = {0, 30, 5, 35, 10, 40, 15, 45, 20, 50, 25, 35};
        int index = -1;

        for (int i = 0; i < mods.length; i++) {
            if (mods[i] == angle % 55) {
                index = i;
                break;
            }
        }

        angle += 3600 * index;
        int totalMinutes = angle / 55;
        int hours = totalMinutes / 60;
        int minutes = totalMinutes % 60;

        return String.format("%02d:%02d", hours, minutes);
    }
}