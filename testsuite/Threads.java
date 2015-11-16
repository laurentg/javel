
/** Java test suite for Javel.
    Test synchronization related functions
*/

public class Threads {

	public void f1(String s) {

		synchronized(s) {
			s += "x";
		}
	}
}

