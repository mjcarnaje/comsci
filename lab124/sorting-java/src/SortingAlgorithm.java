public abstract class SortingAlgorithm {

	protected int[] orig;
	protected int[] arr;
	protected int n;

	public SortingAlgorithm( int[] arrInput, int n)
	{
		// keep local copy of the input values
		this.n = n;
		this.orig = new int[n];
		this.arr = new int[n];
		
		for (int i = 0; i < n; ++i)
		{	
			this.orig[i] = arrInput[i];
		}
	}

	public double getAverageRunTime(int numIterations)
	{
		double sum = 0.0;
		for (int i = 0; i < numIterations; ++i)
		{
			sum += this.getRunTime();
		}
		return (sum / numIterations);		
		
	}

	public void initArray()
	{
		for (int i = 0; i < n; ++i)
			arr[i] = orig[i];
	}
	
	private double getRunTime()
	{
		this.initArray();
		long timeStart = System.nanoTime();
		this.sort();
		long timeEnd = System.nanoTime();

		if (!this.isSorted())
			System.out.println("----- BUG in Sorting! -----");
		

		return (timeEnd - timeStart); 
	}

	public abstract void sort();


	private boolean isSorted()
	{
		for (int i = 1; i < this.n; ++i)
		{
			if (this.arr[i] < this.arr[i-1])
				return false;
		}
		return true;
	}

}