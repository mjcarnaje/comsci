var TreeNode = /** @class */ (function () {
    function TreeNode(value) {
        this.value = value;
        this.left = null;
        this.right = null;
    }
    return TreeNode;
}());
//** HELPER FUNCTIONS **/
function visit(node) {
    console.log(node.value);
}
function levelOrderTraversal(root) {
    if (!root) {
        return;
    }
    var queue = [];
    queue.push(root);
    while (queue.length) {
        var node = queue.shift();
        if (!node) {
            continue;
        }
        visit(node);
        if (node.left) {
            queue.push(node.left);
        }
        if (node.right) {
            queue.push(node.right);
        }
    }
}
function preOrderTraversal(root) {
    if (!root) {
        return;
    }
    visit(root);
    preOrderTraversal(root.left);
    preOrderTraversal(root.right);
}
function postOrderTraversal(root) {
    if (!root) {
        return;
    }
    postOrderTraversal(root.left);
    postOrderTraversal(root.right);
    visit(root);
}
function inOrderTraversal(root) {
    if (!root) {
        return;
    }
    inOrderTraversal(root.left);
    visit(root);
    inOrderTraversal(root.right);
}
//** ================= **/
var BinarySearchTree = /** @class */ (function () {
    function BinarySearchTree() {
        this.root = null;
        this.nodeCount = 0;
    }
    BinarySearchTree.prototype.visit = function (node) {
        console.log(node.value);
    };
    BinarySearchTree.prototype.insert = function (value) {
        var newNode = new TreeNode(value);
        if (!this.root) {
            this.root = newNode;
        }
        else {
            var parentNode = null;
            var currentNode = this.root;
            // Find the parent node
            while (currentNode) {
                parentNode = currentNode;
                if (value < currentNode.value) {
                    currentNode = currentNode.left;
                }
                else {
                    currentNode = currentNode.right;
                }
            }
            if (!parentNode) {
                console.error("Parent node is null");
                return;
            }
            if (value < parentNode.value) {
                parentNode.left = newNode;
            }
            else {
                parentNode.right = newNode;
            }
        }
        this.nodeCount++;
    };
    BinarySearchTree.prototype.display = function () {
        console.log("Pre Order Traversal");
        preOrderTraversal(this.root);
        console.log("In Order Traversal");
        inOrderTraversal(this.root);
        console.log("Post Order Traversal");
        postOrderTraversal(this.root);
        console.log("Level Order Traversal");
        levelOrderTraversal(this.root);
    };
    return BinarySearchTree;
}());
var BST = new BinarySearchTree();
var nums = [10, 15, 6, 11, 20, 3, 8, 0];
for (var i = 0; i < nums.length; i++) {
    BST.insert(nums[i]);
}
BST.display();
