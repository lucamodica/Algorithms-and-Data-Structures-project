
public class Test {

    public static void main(String[] args) {
        
        UnionFindSet<Integer> s = new UnionFindSet<Integer>();

        for(int i = 0; i < 100; i++){
            s.makeSet(i);
        }

        System.out.println("\nBefore unions:");
        for(int i = 0; i < 100; i++){
            System.out.print(s.findSet(i) + "  ");
        }

        for(int i = 0; i < 100; i = i + 2){
            s.union(i + 1, i);
        }

        System.out.println("\n\nAfter unions:");
        for(int i = 0; i < 100; i++){
            System.out.print(s.findSet(i) + "  ");
        }
        System.out.println("\n");

    }
}