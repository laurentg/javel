
/** Java test suite for Javel.
    Copyright (c) 2002 Laurent Gregoire - laurent.gregoire@icam.fr
    Test for: invokestatic, invokevirtual, invokespecial, invokeinterface. */

public class FuncCall {

	public FuncCall(int i) {
		mi = i;
	}
	public void f(int i) { }
	public void f1(int i) {	}
	public static void f2(int i, int k) { }
	public int f3(int i) {
		return i + 2;
	}
	public static int f4(int i, int j, int k) {
		return i + j + k;
	}
	public void f5(FuncCall fc) {
		f1(0);
		f2(1, 2);
		int i = f3(2);
		int j = f4(i, 5495875, -45667);
		int k = f7(i);
		fc.f(f3(f4(mi, f3(2), f3(j))));
	}
	public static int f6(Zappable z, int i) {
		z.zap(3);
		return z.zbp(i);
	}
	private int f7(int i) {
		return i * (i + 2);
	}
	private int mi;
	public interface Zappable {
		public abstract void zap(int i);
		public int zbp(int j);
	}
}

