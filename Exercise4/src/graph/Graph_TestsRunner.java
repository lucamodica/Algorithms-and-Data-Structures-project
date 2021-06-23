package graph;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

/**
 * Main class for the Unit Tests
 * @author lucamodica, lorenzopallanza
 */
public class Graph_TestsRunner {

  /**
   * @param args the command line arguments
   */
  public static void main(String[] args) {
    Result result = JUnitCore.runClasses(GraphTests.class);
    for (Failure failure : result.getFailures()) {
      System.out.println(failure.toString());
    }
  
    if(result.wasSuccessful()){
      System.out.println("All Graph tests passed!");
    }
  }
  
}
