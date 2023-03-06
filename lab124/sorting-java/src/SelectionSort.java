import java.util.*;
import java.io.File;

public class SelectionSort extends SortingAlgorithm {

	public SelectionSort( int[] arr, int n)
	{
		super( arr, n ); 
	}

	public void sort()
	{
		int last = n-1;
		for (int i = 0; i < last; ++i)
		{
			int minValue = arr[i];
			int minIndex = i;
			for (int j = i+1; j < n; ++j)
			{
				if (arr[j] < minValue)
				{
					minValue = arr[j];
					minIndex = j;
				}
			}
			// swap
			arr[minIndex] = arr[i];
			arr[i] = minValue;
		}
	}
	
}