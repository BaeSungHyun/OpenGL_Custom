#ifndef VERTEX_H
#define VERTEX_H

#include <initializer_list>
#include <vector>

// Single Vertex 
template <typename T>
struct Vertex {
    T pos[3] {}; // default initialize to 0
    T rgba[4] {}; // default initialize to 0
    T texture[2] {};
    T normals[3] {};

    Vertex() = default;

    Vertex(std::initializer_list<T> init) {
        range_initialize(init.begin(), init.end());
    };

    // for vector push_back 
    Vertex& operator=(const Vertex& other) { // copy assignemnt
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < 3; i++) pos[i] = other.pos[i];
        for (int i = 0; i < 4; i++) rgba[i] = other.rgba[i];
        for (int i = 0; i < 3; i++) normals[i] = other.normals[i];
        for (int i = 0; i < 2; i++) texture[i] = other.texture[i];

        return *this; // return reference to the current object
    }

private:
    template<typename InputIterator>
    void range_initialize(InputIterator first, InputIterator last) {
        try {
            int index{0};
            for (; first != last; first++) {
                if (index < 3) pos[index++] = *first; // 0, 1, 2
                else if (index < 7) rgba[index++ - 3] = *first; // 3, 4, 5, 6
                else if (index < 9) texture[index++ - 7] = *first; // 7, 8
                else if (index < 12) normals[index++ - 9] = *first; // 9, 10, 11
            }
        } catch (const std::exception& e) {
            std::cout << "Caught an exception : " << e.what() << std::endl;
        }
    }
};

// Multiple Vertices
template <typename T>
struct Vertices {
public:
    // elements on the heap memory; vector on stack memory
    std::vector<Vertex<T>> vecVertex;

    Vertices(){
    };

    Vertices(std::initializer_list<Vertex<T>> init) {   
        range_initialize(init.begin(), init.end());
    };

    ~Vertices() {
    };

    void addVertices(const Vertices& input) {
        for (auto iterator = input.vecVertex.cbegin(); iterator != input.vecVertex.cend(); iterator++)
            vecVertex.push_back(*iterator);
    }

    void addVertex(const Vertex<T>& input) {
        vecVertex.push_back(input);
    }

private:
    template<typename InputIterator>
    void range_initialize(InputIterator first, InputIterator last) {
        try {
            for (; first != last; first++) {
                vecVertex.push_back(*first);
            }
        } catch (const std::exception& e) {
            std::cout << "Caught an exception : " << e.what() << std::endl;
        }
    }
};

#endif