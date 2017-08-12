//author: itachigorun
//date: 2017-07-24

红黑树的特性:
(1)每个节点或者是黑色，或者是红色。
(2)根节点是黑色。
(3)每个叶子节点（NIL）是黑色。 [注意：这里叶子节点，是指为空(NIL或NULL)的叶子节点！]
(4)如果一个节点是红色的，则它的子节点必须是黑色的。
(5)从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点。


红黑树左旋转
LEFT-ROTATE(T, x)  
01  y ← right[x]            // 前提：这里假设x的右孩子为y。下面开始正式操作
02  right[x] ← left[y]      // 将 “y的左孩子” 设为 “x的右孩子”，即 将β设为x的右孩子
03  p[left[y]] ← x          // 将 “x” 设为 “y的左孩子的父亲”，即 将β的父亲设为x
04  p[y] ← p[x]             // 将 “x的父亲” 设为 “y的父亲”
05  if p[x] = nil[T]       
06  then root[T] ← y                 // 情况1：如果 “x的父亲” 是空节点，则将y设为根节点
07  else if x = left[p[x]]  
08            then left[p[x]] ← y    // 情况2：如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
09            else right[p[x]] ← y   // 情况3：(x是它父节点的右孩子) 将y设为“x的父节点的右孩子”
10  left[y] ← x             // 将 “x” 设为 “y的左孩子”
11  p[x] ← y                // 将 “x的父节点” 设为 “y”

红黑树右旋转
RIGHT-ROTATE(T, y)  
01  x ← left[y]             // 前提：这里假设y的左孩子为x。下面开始正式操作
02  left[y] ← right[x]      // 将 “x的右孩子” 设为 “y的左孩子”，即 将β设为y的左孩子
03  p[right[x]] ← y         // 将 “y” 设为 “x的右孩子的父亲”，即 将β的父亲设为y
04  p[x] ← p[y]             // 将 “y的父亲” 设为 “x的父亲”
05  if p[y] = nil[T]       
06  then root[T] ← x                 // 情况1：如果 “y的父亲” 是空节点，则将x设为根节点
07  else if y = right[p[y]]  
08            then right[p[y]] ← x   // 情况2：如果 y是它父节点的右孩子，则将x设为“y的父节点的左孩子”
09            else left[p[y]] ← x    // 情况3：(y是它父节点的左孩子) 将x设为“y的父节点的左孩子”
10  right[x] ← y            // 将 “y” 设为 “x的右孩子”
11  p[y] ← x                // 将 “y的父节点” 设为 “x”

红黑树插入
RB-INSERT(T, z)  
01  y ← nil[T]                        // 新建节点“y”，将y设为空节点。
02  x ← root[T]                       // 设“红黑树T”的根节点为“x”
03  while x ≠ nil[T]                  // 找出要插入的节点“z”在二叉树T中的位置“y”
04      do y ← x                      
05         if key[z] < key[x]  
06            then x ← left[x]  
07            else x ← right[x]  
08  p[z] ← y                          // 设置 “z的父亲” 为 “y”
09  if y = nil[T]                     
10     then root[T] ← z               // 情况1：若y是空节点，则将z设为根
11     else if key[z] < key[y]        
12             then left[y] ← z       // 情况2：若“z所包含的值” < “y所包含的值”，则将z设为“y的左孩子”
13             else right[y] ← z      // 情况3：(“z所包含的值” >= “y所包含的值”)将z设为“y的右孩子” 
14  left[z] ← nil[T]                  // z的左孩子设为空
15  right[z] ← nil[T]                 // z的右孩子设为空。至此，已经完成将“节点z插入到二叉树”中了。
16  color[z] ← RED                    // 将z着色为“红色”
17  RB-INSERT-FIXUP(T, z)             // 通过RB-INSERT-FIXUP对红黑树的节点进行颜色修改以及旋转，让树T仍然是一颗红黑树

插入后三种情况需要调整
1. z的叔节点y是红色的
2. z的叔节点y是黑色的且z是一个右孩子
3. z的叔节点y是黑色的且z是一个左孩子
RB-INSERT-FIXUP(T, z)
01 while color[p[z]] = RED                                                  // 若“当前节点(z)的父节点是红色”，则进行以下处理。
02     do if p[z] = left[p[p[z]]]                                           // 若“z的父节点”是“z的祖父节点的左孩子”，则进行以下处理。
03           then y ← right[p[p[z]]]                                        // 将y设置为“z的叔叔节点(z的祖父节点的右孩子)”
04                if color[y] = RED                                         // Case 1条件：叔叔是红色
05                   then color[p[z]] ← BLACK                    ▹ Case 1   //  (01) 将“父节点”设为黑色。
06                        color[y] ← BLACK                       ▹ Case 1   //  (02) 将“叔叔节点”设为黑色。
07                        color[p[p[z]]] ← RED                   ▹ Case 1   //  (03) 将“祖父节点”设为“红色”。
08                        z ← p[p[z]]                            ▹ Case 1   //  (04) 将“祖父节点”设为“当前节点”(红色节点)
09                   else if z = right[p[z]]                                // Case 2条件：叔叔是黑色，且当前节点是右孩子
10                           then z ← p[z]                       ▹ Case 2   //  (01) 将“父节点”作为“新的当前节点”。
11                                LEFT-ROTATE(T, z)              ▹ Case 2   //  (02) 以“新的当前节点”为支点进行左旋。
12                           color[p[z]] ← BLACK                 ▹ Case 3   // Case 3条件：叔叔是黑色，且当前节点是左孩子。(01) 将“父节点”设为“黑色”。
13                           color[p[p[z]]] ← RED                ▹ Case 3   //  (02) 将“祖父节点”设为“红色”。
14                           RIGHT-ROTATE(T, p[p[z]])            ▹ Case 3   //  (03) 以“祖父节点”为支点进行右旋。
15        else (same as then clause with "right" and "left" exchanged)      // 若“z的父节点”是“z的祖父节点的右孩子”，将上面的操作中“right”和“left”交换位置，然后依次执行。
16 color[root[T]] ← BLACK 


红黑树的删除
RB-DELETE(T, z)
01 if left[z] = nil[T] or right[z] = nil[T]         
02    then y ← z                                  // 若“z的左孩子” 或 “z的右孩子”为空，则将“z”赋值给 “y”；
03    else y ← TREE-SUCCESSOR(z)                  // 否则，将“z的后继节点”赋值给 “y”。
04 if left[y] ≠ nil[T]
05    then x ← left[y]                            // 若“y的左孩子” 不为空，则将“y的左孩子” 赋值给 “x”；
06    else x ← right[y]                           // 否则，“y的右孩子” 赋值给 “x”。
07 p[x] ← p[y]                                    // 将“y的父节点” 设置为 “x的父节点”
08 if p[y] = nil[T]                               
09    then root[T] ← x                            // 情况1：若“y的父节点” 为空，则设置“x” 为 “根节点”。
10    else if y = left[p[y]]                    
11            then left[p[y]] ← x                 // 情况2：若“y是它父节点的左孩子”，则设置“x” 为 “y的父节点的左孩子”
12            else right[p[y]] ← x                // 情况3：若“y是它父节点的右孩子”，则设置“x” 为 “y的父节点的右孩子”
13 if y ≠ z                                    
14    then key[z] ← key[y]                        // 若“y的值” 赋值给 “z”。注意：这里只拷贝z的值给y，而没有拷贝z的颜色！！！
15         copy y's satellite data into z         
16 if color[y] = BLACK                            
17    then RB-DELETE-FIXUP(T, x)                  // 若“y为黑节点”，则调用
18 return y 

删除后四种情况需要调整
1. x的兄弟节点w是红色的
2. x的兄弟节点w是黑色的，而且w的两个子节点都是黑色的
3. x的兄弟节点w是黑色的，w的左孩子是红色的，w的右孩子是黑色的
4. x的兄弟节点w是黑色的，且w的右孩子是红色的
RB-DELETE-FIXUP(T, x)
01 while x ≠ root[T] and color[x] = BLACK  
02     do if x = left[p[x]]      
03           then w ← right[p[x]]                                             // 若 “x”是“它父节点的左孩子”，则设置 “w”为“x的叔叔”(即x为它父节点的右孩子)                                          
04                if color[w] = RED                                           // Case 1: x是“黑+黑”节点，x的兄弟节点是红色。(此时x的父节点和x的兄弟节点的子节点都是黑节点)。
05                   then color[w] ← BLACK                        ▹  Case 1   //   (01) 将x的兄弟节点设为“黑色”。
06                        color[p[x]] ← RED                       ▹  Case 1   //   (02) 将x的父节点设为“红色”。
07                        LEFT-ROTATE(T, p[x])                    ▹  Case 1   //   (03) 对x的父节点进行左旋。
08                        w ← right[p[x]]                         ▹  Case 1   //   (04) 左旋后，重新设置x的兄弟节点。
09                if color[left[w]] = BLACK and color[right[w]] = BLACK       // Case 2: x是“黑+黑”节点，x的兄弟节点是黑色，x的兄弟节点的两个孩子都是黑色。
10                   then color[w] ← RED                          ▹  Case 2   //   (01) 将x的兄弟节点设为“红色”。
11                        x ←  p[x]                               ▹  Case 2   //   (02) 设置“x的父节点”为“新的x节点”。
12                   else if color[right[w]] = BLACK                          // Case 3: x是“黑+黑”节点，x的兄弟节点是黑色；x的兄弟节点的左孩子是红色，右孩子是黑色的。
13                           then color[left[w]] ← BLACK          ▹  Case 3   //   (01) 将x兄弟节点的左孩子设为“黑色”。
14                                color[w] ← RED                  ▹  Case 3   //   (02) 将x兄弟节点设为“红色”。
15                                RIGHT-ROTATE(T, w)              ▹  Case 3   //   (03) 对x的兄弟节点进行右旋。
16                                w ← right[p[x]]                 ▹  Case 3   //   (04) 右旋后，重新设置x的兄弟节点。
17                         color[w] ← color[p[x]]                 ▹  Case 4   // Case 4: x是“黑+黑”节点，x的兄弟节点是黑色；x的兄弟节点的右孩子是红色的。(01) 将x父节点颜色 赋值给 x的兄弟节点。
18                         color[p[x]] ← BLACK                    ▹  Case 4   //   (02) 将x父节点设为“黑色”。
19                         color[right[w]] ← BLACK                ▹  Case 4   //   (03) 将x兄弟节点的右子节设为“黑色”。
20                         LEFT-ROTATE(T, p[x])                   ▹  Case 4   //   (04) 对x的父节点进行左旋。
21                         x ← root[T]                            ▹  Case 4   //   (05) 设置“x”为“根节点”。
22        else (same as then clause with "right" and "left" exchanged)        // 若 “x”是“它父节点的右孩子”，将上面的操作中“right”和“left”交换位置，然后依次执行。
23 color[x] ← BLACK   