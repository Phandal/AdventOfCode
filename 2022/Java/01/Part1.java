import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Part1 {
  public static void main(String args[]) {
    try {
      File f = new File("test.txt");
      Scanner fileReader = new Scanner(f);
      System.out.println(fileReader.nextLine());
      fileReader.close();
    } catch (FileNotFoundException e) {
      System.out.printf("Error: %s\n", e.getMessage());
    }
  }
}
