#include "Transform.h"

Transform::Transform(std::vector<std::pair<std::string, std::string>> transforms) {
    this->transforms = transforms;
}

Transform::Transform() {
    
}

std::vector<std::pair<std::string, std::string>> Transform::getTransforms() const{
    return transforms;
}

void Transform::print() const{
    std::cout << "Transform:\n"; 
    for (int i = 0; i < transforms.size(); i++){
        std::cout << transforms[i].first << ": " << transforms[i].second << "\n";
    }
}