#include <iostream>
#include <torch/torch.h>

int main(int argc, char** argv) {
    std::cout << "Hello, from Hello!\n";
    // PyTorch test: create a tensor and print it
    try {
        torch::Tensor tensor = torch::rand({2, 3});
        std::cout << "Random Tensor from PyTorch:\n" << tensor << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error loading the PyTorch library: " << e.what() << std::endl;
        return -1;
    }

    std::cout << "PyTorch test completed successfully." << std::endl;
    return 0;
}
