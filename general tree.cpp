#include <iostream>
#include <functional>
#include <vector>

class TreeNode {
public:
    using Function = std::function<int(int)>;

private:
    std::vector<TreeNode*> children;
    std::vector<Function> functions;

public:
    void addFunction(Function func) {
        functions.push_back(std::move(func));
    }

    void removeFunction(size_t index) {
        if (index < functions.size()) {
            functions.erase(functions.begin() + index);
        }
    }

    void addChild(TreeNode* child) {
        children.push_back(child);
    }

    int execute(int arg) {
        int result = arg;

        for (const auto& function : functions) {
            result = function(result);
        }

        for (TreeNode* child : children) {
            result = child->execute(result);
        }

        return result;
    }
};

// functions
int addOne(int n) {
    return n + 1;
}

int multiplyByTwo(int n) {
    return n * 2;
}

int squarTree(int n) {
    return n * n;
}



int main() {
    // Create the tree
    TreeNode root;
    TreeNode child1;
    TreeNode child2;

    root.addFunction(addOne);
    child1.addFunction(multiplyByTwo);
    child2.addFunction(squarTree);

    root.addChild(&child1);
    root.addChild(&child2);

    // Execute the tree
    int argument = 5;
    int result = root.execute(argument);

    std::cout << "Result: " << result << std::endl;

    // Remove a function from the tree
    root.removeFunction(0);

    // Execute the tree after removing a function
    result = root.execute(argument);

    std::cout << "Result after removing a function: " << result << std::endl;

    return 0;
}
