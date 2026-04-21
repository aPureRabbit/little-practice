#include <stdio.h>
#include <stdlib.h>

// 1. 定义线索二叉树的节点结构
typedef struct ThreadNode {
    char data;                      // 数据域 (存 A, B, C...)
    struct ThreadNode *lchild;      // 左指针
    struct ThreadNode *rchild;      // 右指针
    int ltag;                       // 左线索标志：0代表孩子，1代表前驱
    int rtag;                       // 右线索标志：0代表孩子，1代表后继
} ThreadNode, *ThreadTree;

// 全局变量 pre，指向刚刚访问过的节点
ThreadNode *pre = NULL;

// 2. 核心逻辑：中序遍历并线索化 (左 -> 根 -> 右)
void InThread(ThreadTree curr) {
    if (curr != NULL) {
        // 第一步：递归线索化左子树
        InThread(curr->lchild);
        
        // ------------------ 中序遍历的"访问"逻辑开始 ------------------
        
        // 1. 如果当前节点的左指针为空，说明它没有左孩子，让它指向前驱(pre)
        if (curr->lchild == NULL) {
            curr->lchild = pre;
            curr->ltag = 1;      // 1代表这是线索
        }
        
        // 2. 如果上一个节点(pre)不为空，且它的右指针为空，让它指向后继(即当前节点 curr)
        if (pre != NULL && pre->rchild == NULL) {
            pre->rchild = curr;
            pre->rtag = 1;       // 1代表这是线索
        }
        
        // 3. 两人同步往前走一步：把当前节点变成"过去的节点"
        pre = curr;
        
        // ------------------ 中序遍历的"访问"逻辑结束 ------------------

        // 第三步：递归线索化右子树
        InThread(curr->rchild);
    }
}

// 包装函数：处理最后一个节点的右线索
void CreateInThread(ThreadTree T) {
    pre = NULL; // 初始化 pre 为空
    if (T != NULL) {
        InThread(T); // 执行核心线索化
        
        // 遍历结束后，pre 指向中序序列的最后一个节点(此例中是 C)。
        // 它的右指针肯定为空，我们需要把它置为线索，并指向 NULL。
        if (pre->rchild == NULL) {
            pre->rtag = 1;
        }
    }
}

// -----------------------------------------------------------------
// 下面是线索化后的威力展示：不需要递归，也不需要栈，直接像遍历链表一样遍历树！

// 辅助函数：找到以某节点为根的子树中，"中序遍历的第一个节点" (即一直往左下角找)
ThreadNode* FirstNode(ThreadNode *p) {
    while (p->ltag == 0) {
        p = p->lchild;
    }
    return p;
}

// 辅助函数：找到某节点在中序遍历下的"后继节点"
ThreadNode* NextNode(ThreadNode *p) {
    if (p->rtag == 1) {
        // 如果 rtag 为 1，说明 rchild 直接指向的就是后继，太爽了，直接返回
        return p->rchild;
    } else {
        // 如果 rtag 为 0，说明它有右孩子。那么它的后继，就是它右子树里最左下的那个节点
        return FirstNode(p->rchild);
    }
}

// 利用线索进行中序遍历 (像遍历单链表一样一个 for 循环搞定！)
void InorderTraverse_Thread(ThreadTree T) {
    // 找到最开始的节点，然后不断找 NextNode
    for (ThreadNode *p = FirstNode(T); p != NULL; p = NextNode(p)) {
        printf("%c ", p->data);
    }
    printf("\n");
}
// -----------------------------------------------------------------

// 辅助函数：创建一个新节点并初始化
ThreadNode* CreateNode(char data) {
    ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->data = data;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    newNode->ltag = 0; // 默认都是真实孩子
    newNode->rtag = 0;
    return newNode;
}

int main() {
    // 手动构造一棵二叉树
    //       A
    //      / \
    //     B   C
    //    / \
    //   D   E
    ThreadNode* root = CreateNode('A');
    ThreadNode* nodeB = CreateNode('B');
    ThreadNode* nodeC = CreateNode('C');
    ThreadNode* nodeD = CreateNode('D');
    ThreadNode* nodeE = CreateNode('E');

    root->lchild = nodeB; root->rchild = nodeC;
    nodeB->lchild = nodeD; nodeB->rchild = nodeE;

    printf("树已搭建完毕，准备进行线索化...\n");
    CreateInThread(root);
    printf("线索化完成！\n");

    printf("利用线索进行中序遍历的结果是：\n");
    // 期望输出应该是：D B E A C
    InorderTraverse_Thread(root);

    // (省略释放内存操作，以保持代码简短)
    return 0;
}
