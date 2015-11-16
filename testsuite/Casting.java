
/** Java test suite for Javel.
    Test casting (instanceof...)
*/

public class Casting {

	public class A { };
	public class B extends A { };
	public class C extends B { };
	public class D extends A { };

	public int f1(A a) {
		if (a instanceof B)
			return 1;
		B b = (B)a;
		C c = (C)new A();
		return 0;
	}
}

