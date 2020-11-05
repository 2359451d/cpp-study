# AVL

自平衡二分查找树（排序，搜索）

平衡因子

![](/static/2020-11-04-13-54-44.png)

* 左右子树高度差
  * `node.balance = height(node.right) - height(node.left)`
* 如果左右子树高度差<`|1|`
  * 平衡

## Rebalance

平衡某节点

* 一旦某节点更新，需要检查整个树(或从某个节点开始检查)是否平衡

```java
private void rebalance(Node n)
{
    setBalance(n);// 计算节点n的当前balance

    //检查是否平衡
    // 左子树过高
    if (n.balance==-2){
        if(height(n.left.left)>=height(n.left.right)){
            //右旋
            n = rotateRight(n);
        }else{
            //左旋再右旋？
            n=rotateLeftThenRight(n);
        }
    }else if (n.balance==2){
        //右子树过高
        if(height(n.right.right)>=height(n.right.left)){
            n=rotateLeft(n);
        }else{
            n=rotateRightThenLeft(n);
        }
    }

    //调整当前结点后，向上继续调整
    if (n.parent!=null) rebalance(n.parent);
    else {root=n};
}
```

### Rotate Left

左旋

```java
private Node rotateLeft(Node x)
{
    Node z = x.right;//右子树
    z.parent = x.parent;
    x.right =z.left;
    
    if (x.right != null) { x.right.parent = x; }

    z.left = x;
    x.parent = z;

    if (z.parent != null) {
        if (z.parent.right == x) { z.parent.right = z; }
        else { z.parent.left = z; }
    }

    setBalance(x);
    setBalance(z);
    return z;
}

```

### Combined Rotations

![](/static/2020-11-04-14-30-12.png)

## Insert

插入节点，root为空时直接建树

* 每次确保平衡（左右子树高度差）
* 重复节点直接返回`false`

```java
public boolean insert(int key)
{
    // 树(root)为空，直接建树，返回true
    if (root=null){
        root = new Node(key,null);
        return true;
    }

    Node n = root;
    while(true)
    {
        if(n.key==key) return false;

        Node parent = n;//当前父结点，用于关联新孩子
        boolean goLeft = n.key > key;// true- goleft, false-goright
        n = goLeft ? n.left: n.right //traversing & updating parent node, till reached the leaf 不停遍历左/右子树更新给当前节点变量n，直到叶结点，在对应位置插入新节点

        // if(n!=null) continue;
        if (n==null)
        {
            if(goLeft){
                //左边插入新节点
                parent.left =new Node(key,parent);
            }else{
                // 右边插入新节点
                parent.right=new Node(key,parent);
            }
            // 为更新后的父节点，进行平衡
            rebalance(parent);
            break;
        }
    }
    return true;//插入成功
}

```