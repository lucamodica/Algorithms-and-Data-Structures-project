package graph;

import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Set;
import java.util.Map;
import java.util.HashSet;
import java.util.Iterator;

/**
 * The core class library to handle a graph data structure,
 * both directed and not directed
 * @author lucamodica lorenzopallanza
 */
public class Graph<V, E> {

  /**
   * The adjacent lists for each vertex. 
   * The is the vertex itself, while the value
   * is a linked list of Node Objects, which
   * contains an adjacent vertex and the 
   * associated edge label 
   */ 
  private HashMap<V, LinkedList<Node<V, E>>> graph;
  /**
   * An HashSet of all edges of the graph, formatted
   * to prevent duplicate edges in non-directed graph
   * and to be used by the Kruscal algorithm
   */
  private HashSet<Edge<V, E>> edges;
  /* Mark the graph as directed (true) or not (false) */ 
  private boolean directed;

  /**
   * Create an empty graph
   * @param directed mark the graph as directed or not
   * @throws GraphException if directed parameter is null
   */
  public Graph(Boolean directed) throws GraphException{
    if (directed == null) {
      throw new GraphException("Graph constructor: directed parameter cannot be null");
    }
    
    graph = new HashMap<V, LinkedList<Node<V, E>>>();
    edges = new HashSet<Edge<V, E>>();
    this.directed = directed;
  }

  /**
   * Create a graph based on an initial collection
   * of edges
   * @param directed mark the graph as directed or not
   * @param c The initial collection of element
   * @throws GraphException if one of the parameters are null, or an
   * edge in the collection ha a different direction creteria
   * of the graph (for example the graph is directed but an
   * edge in the collection is non-directed)
   */
  public Graph(Boolean directed, Collection<Edge<V,E>> c) throws GraphException{
    if (directed == null || c == null) {
      throw new GraphException("Graph constructor: directed and c parameters cannot be null");
    }
    
    graph = new HashMap<V, LinkedList<Node<V, E>>>();
    edges = new HashSet<Edge<V, E>>();
    this.directed = directed;

    HashSet<Edge<V,E>> e = new HashSet<Edge<V,E>>(c);
    for (Edge<V,E> elem : e) {
      if(elem.isDirected() != this.isDirected()){
        throw new GraphException("Graph constructor: an edge in the collection has a different direction criteria");
      }
      addEdge(elem.getSrc(), elem.getDest(), elem.getLabel());
    }
  }

  /**
   * Adds a vertex to the graph
   * @param elem the new vertex
   * @throws GraphException the elem parameter is null
   */
  public void addVertex(V elem) throws GraphException{
    if (elem == null){
      throw new GraphException("Graph addVertex: elem parameter cannot be null");
    }

    graph.put(elem, new LinkedList<Node<V, E>>());
  }

  /**
   * Adds an edge to the graph
   * @param src the source vertex
   * @param dest the destination vertex
   * @param label the edge label
   * @throws GraphException if one of the paremeters are null, the src and dest are
   * the same but the graph is not directed, or the edge already exists
   */
  public void addEdge(V src, V dest, E label)  throws GraphException{
    if (src == null || dest == null || label == null){
      throw new GraphException("Graph addEdge: src, dest and label parameters cannot be null");
    }
    if(src.equals(dest) && !directed){
      System.out.println("Graph addEdge: cannot add an adge with the same src and dest, in a non-directed graph");
      return;
    }
    if(hasEdge(src, dest) || (!directed && hasEdge(dest, src))){
      System.out.println("Graph addEdge: the edge already exists");
      return;
    }

    if (!hasVertex(src)) {
      addVertex(src);
    }
    if (!hasVertex(dest)) {
      addVertex(dest);
    }

    graph.get(src).add(new Node<V, E>(dest, label));
    if (!directed) {
      graph.get(dest).add(new Node<V, E>(src, label));
    }

    edges.add(new Edge<V, E>(src, dest, label, this.directed));
  }

  /**
   * Checks if a graph is directed
   */
  public boolean isDirected() {
    return directed;
  }

  /**
   * Checks if the graph has the vertex containing elem
   * @param elem vertex to look for
   * @return true if the vertex is in the graph, false otherwise
   * @throws GraphException if elem parameter is null
   */
  public boolean hasVertex(V elem) throws GraphException{
    if (elem == null){
      throw new GraphException("Graph hasVertex: elem parameter cannot be null");
    }

    return graph.containsKey(elem);
  }

  /**
   * Checks if the graph has the edge (in case
   * of a non-directed graph, the parameter order does not
   * count)
   * @param src edge to look for
   * @param dest destination of the edge
   * @return true if it founds the edge, false otherwise.
   * @throws GraphException if one of the parameters are null
   */
  public boolean hasEdge(V src, V dest) throws GraphException{
    if (src == null || dest == null){
      throw new GraphException("Graph hasEdge: src and dest parameters cannot be null");
    }

    if (!hasVertex(src) || !hasVertex(dest)) {
      return false;
    }

    return edges.contains(new Edge<V,E>(src, dest, this.directed));
  }

  /**
   * Deletes the vertex containing elem
   * @param elem  vertex to be deleted
   * @throws GraphException if elem parameter is null, or if the vertex already
   * does not exists
   */
  public void deleteVertex(V elem) throws GraphException{
    if (elem == null){
      throw new GraphException("Graph deleteVertex: elem parameter cannot be null");
    }
    if (!hasVertex(elem)) {
      System.out.println("Graph deleteVertex: elem does not exists in the graph");
      return;
    } 

    graph.remove(elem);
    for(Map.Entry<V, LinkedList<Node<V, E>>> entry : graph.entrySet()){
      entry.getValue().remove(new Node<V,E>(elem));
    }

    for (Iterator<Edge<V,E>> i = edges.iterator(); i.hasNext();) {
      Edge<V,E> e = i.next();
      if (e.getSrc().equals(elem) || e.getDest().equals(elem)) {
        i.remove();
      }
    }
  }

  /**
   * Deletes the edge with specified src and dest (in case
   * of a non-directed graph, the parameter order does not
   * count)
   * @param src  edge source
   * @param dest edge destination
   * @throws GraphException if one of the parameters are null, or
   * one of the vertex does not exists
   */
  public void deleteEdge(V src, V dest) throws GraphException{
    if (src == null || dest == null){
      throw new GraphException("Graph deleteEdge: src and dest parameters cannot be null");
    }
    if (!hasVertex(src) || !hasVertex(dest)) {
      System.out.println("Graph deleteEdge: one or both the vertices node does not exist");
      return;
    }

    graph.get(src).remove(new Node<V,E>(dest));

    if(!directed){
      graph.get(dest).remove(new Node<V,E>(src));
    }

    edges.remove(new Edge<V,E>(src, dest, this.directed));
  }

  /**
   * Gets the number of vertices
   */
  public int getVerticesCount() {
    return graph.size();
  }

  /**
   * Gets the number of edges
   */
  public int getEdgesCount() {
    return edges.size();
  }

  /**
   * Gets the vertices set in the graph
   */
  public Set<V> getVertices() {
    return graph.keySet();
  }

  /**
   * Gets the edges set in the graph, formatted
   * with the Edge class
   */
  public Set<Edge<V, E>> getEdges() {
    return edges;
  }

  /**
   * Gets the linked list of all adjacent vertices
   * of a specified vertex 
   * @param elem the specified vertex
   * @return the associated linked list to the vertex,
   * that is the values of the key vertex in the HashMap
   * @throws GraphException if elem parameter is null, or the specified
   * vertex does not exists in the graph
   */
  public LinkedList<Node<V, E>> getAdjacentVerteces(V elem) throws GraphException{
    if (elem == null) {
      throw new GraphException("Graph getAdjacentVerteces: elem parameter cannot be null");
    }
    if (!hasVertex(elem)) {
      System.out.println("Graph getAdjacentVerteces: elem vertex does not exists in the graph");
    }

    return graph.get(elem);
  }

  /**
   * Gets the label of a specified edge with src and dest (in case
   * of a non-directed graph, the parameter order does not count)
   * @param src  edge source
   * @param dest edge destination
   * @return the edge label
   * @throws GraphException if one of the parameters are null, or if the edge does
   * not exists
   */
  public E getEdgeLabel(V src, V dest) throws GraphException{
    if (src == null || dest == null){
      throw new GraphException("Graph getEdgeLabel: src and dest parameters cannot be null");
    }
    if (!hasEdge(src, dest)) {
      System.out.println("Graph getEdgeLabel: the edge does not exists");
      return null;
    }
    
    E label = null;
    for (Node<V, E> e : graph.get(src)) {
      if (e.getElem().equals(dest)) {
        label = e.getLabel();
      }
    }

    return label;
  }

}