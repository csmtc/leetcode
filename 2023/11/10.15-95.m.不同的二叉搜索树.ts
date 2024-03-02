/**
 * Definition for a binary tree node.
 * class TreeNode {
 *     val: number
 *     left: TreeNode | null
 *     right: TreeNode | null
 *     constructor(val?: number, left?: TreeNode | null, right?: TreeNode | null) {
 *         this.val = (val===undefined ? 0 : val)
 *         this.left = (left===undefined ? null : left)
 *         this.right = (right===undefined ? null : right)
 *     }
 * }
 */
class TreeNode {
    val: number
    left: TreeNode | null
    right: TreeNode | null
    constructor(val?: number, left?: TreeNode | null, right?: TreeNode | null) {
        this.val = (val === undefined ? 0 : val)
        this.left = (left === undefined ? null : left)
        this.right = (right === undefined ? null : right)
    }
}
function _gen(tree_arr: Array<TreeNode | null>, tree: TreeNode, cur: TreeNode | null, unused: Array<number>) {
    if (cur === null) return;
    for (const x of unused) {
        if (x < cur.val) cur.left = x;
    }
};
function generateTrees(n: number): Array<TreeNode | null> {
    for (let i = 0; i < n; ++i) {

    }
};
