package graphusagejava;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.DecimalFormat;
import java.util.ArrayList;

import graph.Graph;
import graph.Edge;
import graph.MstKruscal;
import graph.GraphException;
import graph.MstKruscalException;
import unionfindset.UnionFindSetException;

/**
 * The main usage class of the Graph and MstKruscal class.
 * Starting from a csv file with 2 city names and their
 * distance, it will create the related graph and mst thanks
 * to the Kruscal algorithm
 * @author lucamodica, lorenzopallanza
 */
public class GraphKruscalUsageJava {

  /* Encoding variable used in the file reading operations */ 
  private static final Charset ENCODING = StandardCharsets.UTF_8;

  /* Encoding string for colors in terminal */ 
  public static final String ANSI_RESET = "\u001B[0m";
  public static final String ANSI_RED = "\u001B[31m";
  public static final String ANSI_GREEN = "\u001B[32m";
  public static final String ANSI_YELLOW = "\u001B[33m";

  /* Generates the mst and prints the related informations */ 
  private static void makeMstKruscal(Graph<String,Double> graph) 
    throws MstKruscalException, GraphException, UnionFindSetException{
    DecimalFormat decimalFormat = new DecimalFormat("###,###.###");

    System.out.println(ANSI_YELLOW + "Creating the MST from the parameter graph..." + ANSI_RESET);
    MstKruscal<String> mst = new MstKruscal<String>(graph);

    System.out.println(ANSI_GREEN + "***Generated MST result***" + ANSI_RESET);
    System.out.println("Number of vertices: " + ANSI_RED + mst.getVerticesCount() + ANSI_RESET);
    System.out.println("Number of edges: " + ANSI_RED + mst.getEdgesCount() + ANSI_RESET);
    System.out.println("Total weight: " + ANSI_RED + decimalFormat.format(mst.getWeight()/1000) + " Km" + ANSI_RESET);
  }
  
  /* Generates a graph, based on the data read from the parameter csv file */ 
  private static Graph<String,Double> makeGraph(String filepath) 
	  throws IOException, GraphException{
    System.out.println(ANSI_YELLOW + "Loading data from " + filepath + " file..." + ANSI_RESET);
    
    ArrayList<Edge<String,Double>> records = new ArrayList<Edge<String,Double>>();
    Path inputFilePath = Paths.get(filepath);
    try(BufferedReader fileInputReader = Files.newBufferedReader(inputFilePath, ENCODING)){
      String line = null;
      while((line = fileInputReader.readLine()) != null){      
        String[] lineElements = line.split(",");       
        Double label = Double.parseDouble(lineElements[2]);
        records.add(new Edge<String,Double>(lineElements[0], lineElements[1], label, false));
      }
    }

    Graph<String,Double> g = new Graph<String,Double>(false,records);

    System.out.println(ANSI_GREEN + "Graph data loaded!" + ANSI_RESET);
    System.out.println("Is directed: " + g.isDirected());
    System.out.println("Number of vertices: " + g.getVerticesCount());
    System.out.println("Number of edges: " + g.getEdgesCount() + '\n');

    return g;
  }
  
  /* Wrapper to the main program */ 
  private static void testGraphKruscal(String filepath)
	  throws IOException, MstKruscalException, GraphException, UnionFindSetException{
    Graph<String,Double> gCities = makeGraph(filepath);
    makeMstKruscal(gCities);
  }
  
  /**
   * The main method
   * @param args the command line arguments. It should contain only one argument
   * specifying the filepath of the data file
   */
  public static void main(String[] args) throws IOException, GraphException, Exception {
    if(args.length < 1){
      throw new Exception("Usage: java -jar GraphUsageJava.java <file_name>");
    }
      
    testGraphKruscal(args[0]);
  }      
}