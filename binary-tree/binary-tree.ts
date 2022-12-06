class TreeNode<T> {
  value: T;
  left: TreeNode<T> | null;
  right: TreeNode<T> | null;

  constructor(value: T) {
    this.value = value;
    this.left = null;
    this.right = null;
  }
}

//** HELPER FUNCTIONS **/

function visit<T>(node: TreeNode<T>): void {
  console.log(node.value);
}

function levelOrderTraversal<T>(root: TreeNode<T> | null): void {
  if (!root) {
    return;
  }

  const queue: TreeNode<T>[] = [];

  queue.push(root);

  while (queue.length) {
    const node = queue.shift();

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

function preOrderTraversal<T>(root: TreeNode<T> | null): void {
  if (!root) {
    return;
  }

  visit(root);

  preOrderTraversal(root.left);

  preOrderTraversal(root.right);
}

function postOrderTraversal<T>(root: TreeNode<T> | null): void {
  if (!root) {
    return;
  }

  postOrderTraversal(root.left);

  postOrderTraversal(root.right);

  visit(root);
}

function inOrderTraversal<T>(root: TreeNode<T> | null): void {
  if (!root) {
    return;
  }

  inOrderTraversal(root.left);

  visit(root);

  inOrderTraversal(root.right);
}

//** ================= **/

class BinarySearchTree<T> {
  public root: TreeNode<T> | null;
  public nodeCount: number;

  constructor() {
    this.root = null;
    this.nodeCount = 0;
  }

  visit(node: TreeNode<T>): void {
    console.log(node.value);
  }

  insert(value: T): void {
    const newNode = new TreeNode<T>(value);

    if (!this.root) {
      this.root = newNode;
    } else {
      let parentNode: TreeNode<T> | null = null;
      let currentNode: TreeNode<T> | null = this.root;

      // Find the parent node
      while (currentNode) {
        parentNode = currentNode;
        if (value < currentNode.value) {
          currentNode = currentNode.left;
        } else {
          currentNode = currentNode.right;
        }
      }

      if (!parentNode) {
        console.error("Parent node is null");
        return;
      }

      if (value < parentNode.value) {
        parentNode.left = newNode;
      } else {
        parentNode.right = newNode;
      }
    }

    this.nodeCount++;
  }

  includes(value: T): boolean {
    let currentNode: TreeNode<T> | null = this.root;

    while (currentNode) {
      if (value === currentNode.value) {
        return true;
      }

      if (value < currentNode.value) {
        currentNode = currentNode.left;
      } else {
        currentNode = currentNode.right;
      }
    }

    return false;
  }

  removeTop(node: TreeNode<T>): TreeNode<T> | null {
    const leftNode = node.left;
    const rightNode = node.right;

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

    let leftMost = rightNode.left;
    let leftMostParent = rightNode;

    while (leftMost.left) {
      leftMostParent = leftMost;
      leftMost = leftMost.left;
    }

    leftMostParent.left = leftMost.right;
    leftMost.left = leftNode;
    leftMost.right = rightNode;

    return leftMost;
  }

  remove(value: T): void {
    if (!this.root) {
      return;
    }

    let parentNode: TreeNode<T> | null = null;
    let currentNode: TreeNode<T> | null = this.root;

    // Find the node to remove
    while (currentNode) {
      if (value === currentNode.value) {
        break;
      }

      parentNode = currentNode;

      if (value < currentNode.value) {
        currentNode = currentNode.left;
      } else {
        currentNode = currentNode.right;
      }
    }

    if (!currentNode) {
      return;
    }

    if (!parentNode) {
      this.root = this.removeTop(currentNode);
    } else {
      if (parentNode.value > currentNode.value) {
        parentNode.left = this.removeTop(currentNode);
      } else {
        parentNode.right = this.removeTop(currentNode);
      }
    }

    this.nodeCount--;

    return;
  }

  display(): void {
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
  }
}

const BST = new BinarySearchTree();

const nums = [3, 2, 5, 4, 6];

for (let i = 0; i < nums.length; i++) {
  BST.insert(nums[i]);
}

BST.display();

BST.remove(5);

BST.display();
