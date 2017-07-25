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

RIGHT-ROTATE(T, y)  
 x ← left[y]             // 前提：这里假设y的左孩子为x。下面开始正式操作
 left[y] ← right[x]      // 将 “x的右孩子” 设为 “y的左孩子”，即 将β设为y的左孩子
 p[right[x]] ← y         // 将 “y” 设为 “x的右孩子的父亲”，即 将β的父亲设为y
 p[x] ← p[y]             // 将 “y的父亲” 设为 “x的父亲”
 if p[y] = nil[T]       
 then root[T] ← x                 // 情况1：如果 “y的父亲” 是空节点，则将x设为根节点
 else if y = right[p[y]]  
           then right[p[y]] ← x   // 情况2：如果 y是它父节点的右孩子，则将x设为“y的父节点的左孩子”
           else left[p[y]] ← x    // 情况3：(y是它父节点的左孩子) 将x设为“y的父节点的左孩子”
 right[x] ← y            // 将 “y” 设为 “x的右孩子”
 p[y] ← x                // 将 “y的父节点” 设为 “x”