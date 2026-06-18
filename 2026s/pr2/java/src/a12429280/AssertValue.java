package a12429280;

import java.util.Collection;

final public class AssertValue {
	static private final String createMsg(String msg, int val)     {
		return msg + ", passed: " + val;
	}
	static public final void    isPositive         (int n)         {
        if (n < 0) 
        	throw new IllegalArgumentException(createMsg("amount can't be negative", n));
    }
    static public final void    isAValidPercentage (int p)         {
    	if (p < 0 || p > 100) 
    		throw new IllegalArgumentException(createMsg("percentage must be between 0 and 100", p));
    }
    static public final void    isNotNull     (Object val)         {
    	if (val == null) 
    		throw new IllegalArgumentException("variable must not be null");
    }
    static public final void    isNotEmpty     (String str)        {
    	if (str.isEmpty()) 
    		throw new IllegalArgumentException("string was empty");
    }
    @SuppressWarnings("rawtypes")
	static public final void    isNotEmpty     (Collection c)      {
    	if (c.isEmpty()) 
    		throw new IllegalArgumentException("collection was empty");
    }
    static public final void    areNotTheSame (Object l, Object r) {
    	if (l == r)
    		throw new IllegalArgumentException("both variables refer to the same object");
    }
}
