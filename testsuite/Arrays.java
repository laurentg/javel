
/** Java test suite for Javel.
    Copyright (c) 2002 Laurent Gregoire - laurent.gregoire@icam.fr
    Test for: Array operations. */

public class Arrays {

	/** Load from an array */
	public void f1(int[] x1, long[][] x2) {
		int j = 0;
		int i = x1[j];
		long k = x2[x1[j]][j];
	}

	/** Test array length */
	public void f2(int[] x1, int[][][] x2) {
		int x;
		for (int i = 0; i < x2.length; i++) {
			for (int j = 0; j < x2[i].length; j++) {
				for (int k = 0; k < x2[i][j].length; k++) {
					x = x2[i][j][k] + x1[i + j + k];
		}	}	}
	}

	/** Test new arrays */
	public void f3(int i, int j) {
		int[] x1 = new int[10];
		int[][] x2 = new int[i][i + j];
		String[] s1 = new String[i + j];
		String[][][][] s2 = new String[1][3][i][j];
	}
}

