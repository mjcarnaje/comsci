import java.util.*;
import java.io.File;

public class SortingBenchmarker {
	static final String DELIMITER = "\t";
	static final int NUM_EXPERIMENTS = 30;
	
	public static void main ( String[] args ) throws Exception
	{
		Scanner sc = new Scanner(new File("SortingInput.txt"));

		int numCases = sc.nextInt();
		
		for (int i = 0; i < numCases; ++i)
			benchmark(sc);
		
		sc.close();
	}
	
	
	public static void benchmark (Scanner sc)
	{
		int numItems = sc.nextInt();
		int[] arrOrig = new int[numItems];
		
		// store contents to an array
		for (int i = 0; i < numItems; ++i)
		{
			arrOrig[i] = sc.nextInt();
		}

		SortingAlgorithm sSort = new SelectionSort( arrOrig, numItems );
		// SortingAlgorithm iSort = new InsertionSort( arrOrig, numItems );
		
		System.out.printf("%d %s %.2e \n", numItems, DELIMITER, sSort.getAverageRunTime(NUM_EXPERIMENTS));
		// System.out.printf("%d %s %.2e %s %.2e \n", numItems, DELIMITER, sSort.getAverageRunTime(NUM_EXPERIMENTS), DELIMITER, iSort.getAverageRunTime(NUM_EXPERIMENTS));
		//System.out.println();
		
	}
	
}

