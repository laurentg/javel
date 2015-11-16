
/** Java test suite for Javel.
    Test exceptions related functions (athrow, try/catch...)
*/

public class Exceptions {

	public class ScrewedUp extends Exception {
		public ScrewedUp() { }
		public ScrewedUp(String s) { super(s); }
	}
	
	public void f1(int i, ScrewedUp exc) throws ScrewedUp {

		if (i == -1) throw null;
		if (i < 0) throw exc;
		if (i == 0) throw new ScrewedUp("i is null");
	}

	public int f2() {

		int i;
		try {
			i = 0;
		} finally {
			i = 1;
		}
		return i;
	}
}

