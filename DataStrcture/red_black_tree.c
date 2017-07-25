//author: itachigorun
//date: 2017-07-24

LEFT_ROTATE(T, x)
    y = x.right		// set y
    x.right = y.left	// turn y's left subtree into x's right subtree
    if y.left != T.nil
    	y.left.p = x
    y.p = x.p		// link x's parent to y
    if x.p == T.nil
    	T.root = y
    elseif x == x.p.left
    	x.p.left = y
    else x.p.right = y
    y.left = x		// put x on y's left
    x.p = y

