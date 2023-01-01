import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Part2 {
  private static void bubble_sort(int maxes[]) {
    return;
  }
  
  public static void main(String args[]) {
    try {

      if (args.length < 1) {
        System.err.println("Usage: part1 <filename>");
        System.exit(1);
      }

      String filename = args[0];
      File f = new File(filename);
      Scanner fileReader = new Scanner(f);
      int lineTotal = 0;
      int max[] = new int[4];

      while(fileReader.hasNext()) {
        try {
          // If parsing was correct then add to line total;
          int line = Integer.parseInt(fileReader.nextLine());
          lineTotal += line;
        } catch (NumberFormatException nfe) {
          max[3] = lineTotal;
          bubble_sort(max);
          lineTotal = 0;
        }
      }

      fileReader.close();

      System.out.printf("Max Total: %d\n", (max[0] + max[1] + max[2]));
      if (filename.equals("test_input.txt")) {
        assert (max[0] + max[1] + max[2]) == 45000 : "Incorrect Answer";
        System.out.println("Test Passed!");
      }
    } catch (FileNotFoundException fnfe) {
      System.out.printf("Error: %s\n", fnfe.getMessage());
    } catch (Exception e) {
      System.out.printf("There was a problem: %s\n", e.getMessage());
    }
  }
}
