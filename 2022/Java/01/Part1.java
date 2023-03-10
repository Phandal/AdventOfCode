import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Part1 {
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
      int max = 0;

      while(fileReader.hasNext()) {
        try {
          // If parsing was correct then add to line total;
          int line = Integer.parseInt(fileReader.nextLine());
          lineTotal += line;
        } catch (NumberFormatException nfe) {
          if (lineTotal > max) {
            max = lineTotal;
          }
          lineTotal = 0;
        }
      }

      fileReader.close();

      System.out.printf("Max: %d\n", max);
      if (filename.equals("test_input.txt")) {
        assert max == 24000 : "Incorrect Answer";
        System.out.println("Test Passed!");
      }
    } catch (FileNotFoundException fnfe) {
      System.out.printf("Error: %s\n", fnfe.getMessage());
    } catch (Exception e) {
      System.out.printf("There was a problem: %s\n", e.getMessage());
    }
  }
}
