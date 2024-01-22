// tree.java
// demonstrates binary tree
// to run this program: C>java TreeApp
package binarytree;
// tree.java
// demonstrates binary tree
// to run this program: C>java TreeApp
import java.io.*;
import java.util.*;               // for Stack class
////////////////////////////////////////////////////////////////
class Node
   {
   public int iData;              // data item (key)
   public int generation;         // how many levels deep
   public Node parent;            // this node's parent
   public Node grandparent;       // this node's grandparent
   public Node leftChild;         // this node's left child
   public Node rightChild;        // this node's right child

   public void displayNode()      // display ourself
      {
      System.out.print('{');
      System.out.print(iData);
      System.out.print("} ");
      }
   }  // end class Node
////////////////////////////////////////////////////////////////
class Tree
   {
   private Node root, parent, grandparent;             // first node of tree
// -------------------------------------------------------------
   
   public Tree(int usergen)
     {
	   root = new Node();
	   parent = new Node();
	   grandparent = new Node();
	   root.parent = parent;
	   root.grandparent = grandparent;
	   parent.parent = parent;
       int generation = usergen;
       root.grandparent.iData = 1;
       root.parent.iData = 2;
       root.iData = root.grandparent.iData + root.parent.iData;
       makeTree(root, parent, grandparent, generation);
     }
//--------------------------------------------------------------
   public void makeTree(Node root, Node parent, Node grandparent, int generation)
     {
       Node leftchild = new Node();
       Node rightchild = new Node();
       leftchild.iData = grandparent.iData + root.iData;
       rightchild.iData =  parent.iData + root.iData;
       leftchild.parent = root;
       rightchild.parent = root;
       generation--;
       if (generation == 0)
       {
         return;
       }
       else {
    	 grandparent = parent;
    	 parent = root;
    	 
    	 parent.leftChild = leftchild;
    	 parent.rightChild = rightchild;
         makeTree(leftchild, parent, grandparent, generation);
         makeTree(rightchild, parent, grandparent, generation);
       }
       
     }
//--------------------------------------------------------------
   public Node find(int key)      // find node with given key
      {                           // (assumes non-empty tree)
      Node current = root;               // start at root
      while(current.iData != key)        // while no match,
         {
         if(key < current.iData)         // go left?
            current = current.leftChild;
         else                            // or go right?
            current = current.rightChild;
         if(current == null)             // if no child,
            return null;                 // didn't find it
         }
      return current;                    // found it
      }  // end find()
   public int findmax(Tree theTree)
   {
	   Node current;
	   current = root;
	   parent = root;
	   while(current != null)
	   {
		   parent = current;
		   current = current.rightChild;
	   }
	  return parent.iData; 
   }
   public void count(Tree theTree)
   {
      int max = findmax(theTree);
      ArrayList<Integer> counts = new ArrayList<Integer>(Collections.nCopies(max+2, 0));      CountinOrder(root, counts);
      System.out.print("Missing: ");
      for (int i = 1; i < max+1; i++) {
            if(counts.get(i) == 0)
               System.out.print(i + " ");
      }
      System.out.print("\nCounts:\n");
      for (int j = 1; j< max+1; j++) {
         System.out.print(j + ": " + counts.get(j)+"\n");
      }
   }
   private void CountinOrder(Node localRoot, ArrayList<Integer> counts)
   {
   if(localRoot != null)
      {
      CountinOrder(localRoot.leftChild, counts);
      counts.set(localRoot.iData, counts.get(localRoot.iData) + 1);
      CountinOrder(localRoot.rightChild, counts);
      }
   }

   public void traverse(int traverseType)
      {
      switch(traverseType)
         {
         case 1: System.out.print("\nPreorder traversal: ");
                 preOrder(root);
                 break;
         case 2: System.out.print("\nInorder traversal:  ");
                 inOrder(root);
                 break;
         case 3: System.out.print("\nPostorder traversal: ");
                 postOrder(root);
                 break;
         }
      System.out.println();
      }
// -------------------------------------------------------------
   private void preOrder(Node localRoot)
      {
      if(localRoot != null)
         {
         System.out.print(localRoot.iData + " ");
         preOrder(localRoot.leftChild);
         preOrder(localRoot.rightChild);
         }
      }
// -------------------------------------------------------------
   private void inOrder(Node localRoot)
      {
      if(localRoot != null)
         {
         inOrder(localRoot.leftChild);
         System.out.print(localRoot.iData + " ");
         inOrder(localRoot.rightChild);
         }
      }
// -------------------------------------------------------------
   private void postOrder(Node localRoot)
      {
      if(localRoot != null)
         {
         postOrder(localRoot.leftChild);
         postOrder(localRoot.rightChild);
         System.out.print(localRoot.iData + " ");
         }
      }
// -------------------------------------------------------------
   public void displayTree()
      {
      Stack globalStack = new Stack();
      globalStack.push(root);
      int nBlanks = 32;
      boolean isRowEmpty = false;
      System.out.println(
      "......................................................");
      while(isRowEmpty==false)
         {
         Stack localStack = new Stack();
         isRowEmpty = true;

         for(int j=0; j<nBlanks; j++)
            System.out.print(' ');

         while(globalStack.isEmpty()==false)
            {
            Node temp = (Node)globalStack.pop();
            if(temp != null)
               {
               System.out.print(temp.iData);
               localStack.push(temp.leftChild);
               localStack.push(temp.rightChild);

               if(temp.leftChild != null ||
                                   temp.rightChild != null)
                  isRowEmpty = false;
               }
            else
               {
               System.out.print("--");
               localStack.push(null);
               localStack.push(null);
               }
            for(int j=0; j<nBlanks*2-2; j++)
               System.out.print(' ');
            }  // end while globalStack not empty
         System.out.println();
         nBlanks /= 2;
         while(localStack.isEmpty()==false)
            globalStack.push( localStack.pop() );
         }  // end while isRowEmpty is false
      System.out.println(
      "......................................................");
      }  // end displayTree()
// -------------------------------------------------------------
   }  // end class Tree
////////////////////////////////////////////////////////////////
class TreeApp
   {
   public static void main(String[] args) throws IOException
      {
      int value, generation, maxvalue;
      System.out.print("Enter the number of generations you would like?: ");
      generation = getInt();
      Tree theTree = new Tree(generation);
      maxvalue = theTree.findmax(theTree);


      while(true)
         {
         System.out.print("Enter first letter of show, find, count, or traverse: ");
         int choice = getChar();
         switch(choice)
            {
            case 's':
               theTree.displayTree();
               break;
            case 'f':
               System.out.print("Enter value to find: ");
               value = getInt();
               Node found = theTree.find(value);
               if(found != null)
                  {
                  System.out.print("Found: ");
                  found.displayNode();
                  System.out.print("\n");
                  }
               else
                  System.out.print("Could not find ");
                  System.out.print(value + '\n');
               break;
            case 'c':
                theTree.count(theTree);
                break;
            case 't':
               System.out.print("Enter type 1, 2 or 3: ");
               value = getInt();
               theTree.traverse(value);
               break;
            default:
               System.out.print("Invalid entry\n");
            }  // end switch
         }  // end while
      }  // end main()
// -------------------------------------------------------------
   public static String getString() throws IOException
      {
      InputStreamReader isr = new InputStreamReader(System.in);
      BufferedReader br = new BufferedReader(isr);
      String s = br.readLine();
      return s;
      }
// -------------------------------------------------------------
   public static char getChar() throws IOException
      {
      String s = getString();
      return s.charAt(0);
      }
//-------------------------------------------------------------
   public static int getInt() throws IOException
      {
      String s = getString();
      return Integer.parseInt(s);
      }
// -------------------------------------------------------------
   }  // end class TreeApp
////////////////////////////////////////////////////////////////