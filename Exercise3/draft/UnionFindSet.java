import java.util.HashMap;

public class UnionFindSet<T> {

  HashMap<T, Node<T>> sets;

  public UnionFindSet(){
    sets = new HashMap<T, Node<T>>();
  }

  public void makeSet(T x){
    sets.put(x, new Node<T>(x));
  }

  public T findSet(T x){
    if(! x.equals(sets.get(x).getElem())){
      T parent = sets.get(x).getElem();
      sets.replace(x, new Node<T>(findSet(parent)));
    }
    return sets.get(x).getElem();
  }

  private void link(Node<T> x, Node<T> y){
    if(x.getRank() > y.getRank()){
      sets.replace(y.getElem(), x);
    }
    else{
      if(x.getRank() == y.getRank()){
        y.setRank(y.getRank() + 1);
      }
      sets.replace(x.getElem(), y);
    }
  }

  public void union(T x, T y){
    link(sets.get(findSet(x)), sets.get(findSet(y)));
  }

}
