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

  display(): void {
    console.log("Pre Order Traversal");
    preOrderTraversal(this.root);

    console.log("In Order Traversal");
    inOrderTraversal(this.root);

    console.log("Post Order Traversal");
    postOrderTraversal(this.root);

    console.log("Level Order Traversal");
    levelOrderTraversal(this.root);
  }
}

const BST = new BinarySearchTree();

const nums = [10, 15, 6, 11, 20, 3, 8, 0];

for (let i = 0; i < nums.length; i++) {
  BST.insert(nums[i]);
}

BST.display();
