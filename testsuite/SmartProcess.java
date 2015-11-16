
import java.awt.*;
import java.io.*;

public class SmartProcess extends Thread {

   Dialog d;
   protected int result;
   String command;

   public SmartProcess(String command, Dialog d) {
      this.d = d;
      this.command = command;
      result = 0;
   }
   
   public void run() {
      try {
         Process theProcess = Runtime.getRuntime().exec(command);
         if (theProcess != null) {
            result = theProcess.waitFor();
         } else {
            result = -1;
         }
      } catch (Exception e) {
         result = -1;
      }
      d.dispose();
   }
   
   public int getResult() {
      return result;
   }
}
