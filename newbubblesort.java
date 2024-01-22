package bubbleSort.java;

public class newbubblesort {
	static class ArrayBub
	   {
	   private int[] a;              
	   private int nElems;              
	   public ArrayBub(int max)       
	      {
	      a = new int[max];                 
	      nElems = 0;                        
	      }
	 
	   public void insert(int value)    
	      {
	      a[nElems] = value;             
	      nElems++;                      
	      }
	   public void display()            
	      {
	      for(int j=0; j<nElems; j++)       
	         System.out.print(a[j] + " ");  
	      System.out.println("");
	      }
	public static void recursiveBubbleSort(int[] arr, int left, int right) {
	    if (left < right) {
	        if (right - left + 1 <= 4) {
	            bubbleSort(arr, left, right);
	        } else {
	            int mid = left + (right - left) / 2;
	            recursiveBubbleSort(arr, left, mid);
	            recursiveBubbleSort(arr, mid + 1, right);
	            merge(arr, left, mid, right);
	        }
	    }
	}
	     
	  private static void bubbleSort(int[] arr, int left, int right) {
	    boolean swapped = true;
	    int j = 0;
	    int numexchanges = 0;
	    while (swapped) {
	        swapped = false;
	        j++;
	        for (int i = left; i < right - j + 1; i++) {
	            if (arr[i] > arr[i + 1]) {
	            	numexchanges++;
	                int temp = arr[i];
	                arr[i] = arr[i + 1];
	                arr[i + 1] = temp;
	                swapped = true;
	            }
	        }
	        if (numexchanges < 1) {
	        	return;
	        }
	    }
	}
	    private static void merge(int[] arr, int left, int mid, int right) {
	  
	    int[] temp = new int[right - left + 1];
	    
	    
	    int i = left, j = mid + 1, k = 0;
	    
	    
	    while (i <= mid && j <= right) {
	        if (arr[i] <= arr[j]) {
	            temp[k++] = arr[i++];
	        } else {
	            temp[k++] = arr[j++];
	        }
	    }
	    
	    
	    while (i <= mid) {
	        temp[k++] = arr[i++];
	    }
	    
	    
	    while (j <= right) {
	        temp[k++] = arr[j++];
	    }
	    
	    
	    for (int m = 0; m < temp.length; m++) {
	        arr[left + m] = temp[m];
	    }
	}
	    public static void main(String[] args)
	      {
	      int min = 1;
	      int maxSize = 5000;
	      int left = 0;
	      ArrayBub arr;           
	      arr = new ArrayBub(maxSize);  
	      for(int i = 0; i < maxSize; i++)
	        {
	          int random_int = (int)Math.floor(Math.random() * (maxSize - min + 1) + min);
	          arr.insert(random_int);
	        }
	      int right = arr.nElems - 1;

	      arr.display();                

	      recursiveBubbleSort(arr.a, left, right);             

	      arr.display();                
	      } 
	   
}
}
