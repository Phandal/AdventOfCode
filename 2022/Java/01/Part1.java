import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Part1 {
  public static void main(String args[]) {
    try {

      if (args.length < 2) {
        System.err.println("Usage: part1 <filename>");
        System.exit(1);
      }

      File f = new File("test.txt");
      Scanner fileReader = new Scanner(f);

      while(fileReader.hasNext()) {
        System.out.printf("%i\n", Integer.parseInt(fileReader.nextLine()));
      }

      fileReader.close();
    } catch (FileNotFoundException e) {
      System.out.printf("Error: %s\n", e.getMessage());
    }
  }
}
