import java.util.Scanner;
class cold {
  public static void main(String[] args) {
    // Setup scanner and variables
    Scanner scanman = new Scanner(System.in);
    int num = scanman.nextInt();
    int cur = 0;
    int total = 0;
    // Initialize array
    for (int i = 0; i < num; i++) {
      cur = scanman.nextInt();
      if (cur < 0) {
        total++;
      }
    }

  System.out.println(total);

  }
}