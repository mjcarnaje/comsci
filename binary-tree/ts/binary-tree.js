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
    BinarySearchTree.prototype.includes = function (value) {
        var currentNode = this.root;
        while (currentNode) {
            if (value === currentNode.value) {
                return true;
            }
            if (value < currentNode.value) {
                currentNode = currentNode.left;
            }
            else {
                currentNode = currentNode.right;
            }
        }
        return false;
    };
    BinarySearchTree.prototype.removeTop = function (node) {
        var leftNode = node.left;
        var rightNode = node.right;
        if (!leftNode && !rightNode) {
            return null;
        }
        if (!leftNode) {
            return rightNode;
        }
        if (!rightNode) {
            return leftNode;
        }
        if (!rightNode.left) {
            rightNode.left = leftNode;
            return rightNode;
        }
        var leftMost = rightNode.left;
        var leftMostParent = rightNode;
        while (leftMost.left) {
            leftMostParent = leftMost;
            leftMost = leftMost.left;
        }
        leftMostParent.left = leftMost.right;
        leftMost.left = leftNode;
        leftMost.right = rightNode;
        return leftMost;
    };
    BinarySearchTree.prototype.remove = function (value) {
        if (!this.root) {
            return;
        }
        var parentNode = null;
        var currentNode = this.root;
        // Find the node to remove
        while (currentNode) {
            if (value === currentNode.value) {
                break;
            }
            parentNode = currentNode;
            if (value < currentNode.value) {
                currentNode = currentNode.left;
            }
            else {
                currentNode = currentNode.right;
            }
        }
        if (!currentNode) {
            return;
        }
        if (!parentNode) {
            this.root = this.removeTop(currentNode);
        }
        else {
            if (parentNode.value > currentNode.value) {
                parentNode.left = this.removeTop(currentNode);
            }
            else {
                parentNode.right = this.removeTop(currentNode);
            }
        }
        this.nodeCount--;
        return;
    };
    BinarySearchTree.prototype.display = function () {
        console.log("====================================");
        console.log("Pre Order Traversal");
        preOrderTraversal(this.root);
        console.log("In Order Traversal");
        inOrderTraversal(this.root);
        console.log("Post Order Traversal");
        postOrderTraversal(this.root);
        console.log("Level Order Traversal");
        levelOrderTraversal(this.root);
        console.log("====================================");
    };
    return BinarySearchTree;
}());
var BST = new BinarySearchTree();
var nums = [3, 2, 5, 4, 6];
for (var i = 0; i < nums.length; i++) {
    BST.insert(nums[i]);
}
BST.display();
BST.remove(5);
BST.display();
